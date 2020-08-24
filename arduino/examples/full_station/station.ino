#include <NTPClient.h>
#include <ArduinoHttpClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>
#include "PousPousApi.h"
#include "secrets.h"

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
char device[] = DEVICE;

char server_name[] = SERVER_NAME;
const int server_port = SERVER_PORT;

WiFiClient wifi;

HttpClient client = HttpClient(wifi, server_name, server_port);

const long utc_offset = 3600*2;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utc_offset);

PousPousApi api = PousPousApi(client, device);

unsigned long setting_update_epoch = 0;

struct watering_t
{
    int motor_pin = D5;
    int sensor_pin = D2;

    // mode d'arrosage:
    //   0 pour arrosage régulier
    //   1 pour prendre en compte le détecteur d'eau
    int mode = 1;

    // HIGH: eau non détectée, LOW: eau détectée
    int level_sensor_val = HIGH;

    // la date du dernier arrosage
    unsigned long last_epoch = 0;

    // durée minimum entre 2 arrosages en heure
    int interval = 12;

    // durée d'arrosage en secondes
    int duration = 10;

    // date du dernier envoi de l'humidité à l'api
    unsigned long last_sensor_save = 0;

} watering;

struct lights_t
{
    int relay_pin = D7;

    int last_status = LOW;

    int start_hour = 7;
    int end_hour = 2;

} lights;

void setup()
{
    pinMode(lights.relay_pin, OUTPUT);
    pinMode(watering.motor_pin, OUTPUT);
    pinMode(watering.sensor_pin, INPUT);

    digitalWrite(watering.motor_pin, LOW);
    digitalWrite(lights.relay_pin, LOW);
    
    Serial.begin(115200);

    WiFi.begin(ssid, pass);

    Serial.print("Connecting to WiFi");

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println();

    Serial.print("Connected to WiFi, IP address: ");
    Serial.println(WiFi.localIP());

    timeClient.begin();

    api.createDevice();

    getSettings();
}

void handleWatering()
{
    watering.level_sensor_val = digitalRead(watering.sensor_pin);

    bool shouldWater = false;

    // détermine si on devrait arroser suivant le mode
    if (watering.mode == 0)
    {
        if (timeClient.getHours() % watering.interval == 0)
        {
            shouldWater = true;
        }
    }
    else if (watering.mode == 1)
    {
        if (watering.level_sensor_val == HIGH)
        {
            shouldWater = true;
        }
    }

    if (shouldWater)
    {
        // vérifie qu'on a pas arrosé les heures précédentes
        if (timeClient.getEpochTime() > watering.last_epoch + watering.interval * 3600)
        {
            watering.last_epoch = timeClient.getEpochTime();

            api.createEvent("watering", 1);
            digitalWrite(watering.motor_pin, HIGH);
            delay(1000 * watering.duration);
            digitalWrite(watering.motor_pin, LOW);
            api.createEvent("watering", 0);
        }
    }

    digitalWrite(watering.motor_pin, LOW);
}

void handleLights()
{
    int status;
    if (timeClient.getHours() < lights.start_hour && timeClient.getHours() >= lights.end_hour)
    {
        status = LOW;
    }
    else
    {
        status = HIGH;
    }

    if (lights.last_status != status)
    {
        api.createEvent("lights", (float)status);
    }
    digitalWrite(lights.relay_pin, status);

    lights.last_status = status;
}

void getSettings()
{
    float val;
    if (api.getSetting("watering.mode", val)) watering.mode = val;
    if (api.getSetting("watering.interval", val)) watering.interval = val;
    if (api.getSetting("watering.duration", val)) watering.duration = val;
    if (api.getSetting("lights.start_hour", val)) lights.start_hour = val;
    if (api.getSetting("lights.end_hour", val)) lights.end_hour = val;
}

void loop()
{
    timeClient.update();

    // de temps en temps on récupère les nouveaux paramètres
    if (timeClient.getMinutes() % 10 == 0 && timeClient.getEpochTime() > setting_update_epoch + 60 * 5)
    {
        getSettings();
        setting_update_epoch = timeClient.getEpochTime();
    }

    // on log le niveau d'humidité 
    if (timeClient.getEpochTime() > watering.last_sensor_save + 120)
    {
        watering.last_sensor_save = timeClient.getEpochTime();
        api.createEvent("humidity_1", (float)analogRead(A0));
    }

    handleLights();

    handleWatering();

    delay(1000);
}
