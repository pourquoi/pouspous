#include <NTPClient.h>
#include <ArduinoHttpClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>
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

size_t msg_post_device_size;
const int msg_post_device_capacity = JSON_OBJECT_SIZE(1) + 60;
StaticJsonDocument<msg_post_device_capacity> msg_post_device;

size_t msg_post_event_size;
const int msg_post_event_capacity = JSON_OBJECT_SIZE(3) + 60;
StaticJsonDocument<msg_post_event_capacity> msg_post_event;

unsigned long setting_update_epoch = 0;

struct watering_t
{
    int motor_pin = D5;
    int sensor_pin = D4;

    // mode d'arrosage:
    //   0 pour arrosage régulier
    //   1 pour prendre en compte le détecteur d'eau
    int mode = 1;

    // HIGH: eau non détectée, LOW: eau détectée
    int level_sensor_val = HIGH;

    // la date du dernier arrosage
    unsigned long last_epoch = 0;

    // durée d'arrosage en secondes
    int duration = 10;

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

    digitalWrite(watering.motor_pin, HIGH);
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

    apiPostDevice();
    apiGetSettings();
}

void apiPostDevice()
{
    Serial.println("Creating device");

    msg_post_device["name"] = device;

    String json;
    serializeJson(msg_post_device, json);

    Serial.println(json);

    client.beginRequest();
    client.post("/api/devices");
    client.sendHeader("Content-Type", "application/json");
    client.sendHeader("Accept", "application/json");
    client.sendHeader("Content-Length", json.length());
    client.beginBody();
    client.print(json);
    client.endRequest();

    int statusCode = client.responseStatusCode();

    Serial.print("Status code: ");
    Serial.println(statusCode);
}

void apiPostEvent(const char *type, float value)
{
    Serial.print("Creating event: ");
    Serial.print(type);
    Serial.print(" = ");
    Serial.println(value);

    if (!client.connect(server_name, server_port))
    {
        Serial.println("Could not connect");
        return;
    }

    msg_post_event["device"] = device;
    msg_post_event["type"] = type;
    msg_post_event["value"] = value;

    String json;
    serializeJson(msg_post_event, json);

    client.beginRequest();
    client.post("/api/events");
    client.sendHeader("Content-Type", "application/json");
    client.sendHeader("Accept", "application/json");
    client.sendHeader("Content-Length", json.length());
    client.beginBody();
    client.print(json);
    client.endRequest();

    int statusCode = client.responseStatusCode();

    Serial.print("Status code: ");
    Serial.println(statusCode);
}

void apiGetSettings()
{
    Serial.println("Getting settings");

    if (!client.connect(server_name, server_port))
    {
        Serial.println("Could not connect");
        return;
    }

    client.beginRequest();
    client.get("/api/device_settings");
    client.sendHeader("Accept", "application/json");
    client.sendHeader("X-Device", device);
    client.endRequest();

    int statusCode = client.responseStatusCode();

    Serial.print("Status code: ");
    Serial.println(statusCode);

    if (statusCode != 200)
    {
        return;
    }

    String response = client.responseBody();

    Serial.println(response.length());

    const size_t capacity = 2048;
    DynamicJsonDocument doc(capacity);

    Serial.println(doc.capacity());

    // Parse JSON object
    DeserializationError error = deserializeJson(doc, response);
    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
        return;
    }

    int l = doc.size();
    int i;
    for (i = 0; i < l; i++)
    {
        const char *setting = doc[i]["name"].as<char *>();
        float value = doc[i]["value"].as<float>();

        if (setting == "watering.duration")
        {
            watering.duration = value;
        }
        else if (setting == "watering.mode")
        {
            watering.mode = (int)value;
        }
        else if (setting == "lights.start_hour")
        {
            lights.start_hour = (int)value;
        }
        else if (setting == "lights.end_hour")
        {
            lights.end_hour = (int)value;
        }
    }
}

void handleWatering()
{
    watering.level_sensor_val = digitalRead(watering.sensor_pin);

    bool shouldWater = false;
    bool didWater = false;

    // détermine si on devrait arroser suivant le mode
    if (watering.mode == 0)
    {
        if (timeClient.getHours() % 4 == 0)
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
        // vérifie qu'on a pas arrosé les 3 heures précédentes
        if (timeClient.getEpochTime() > watering.last_epoch + 3 * 3600)
        {
            didWater = true;
            watering.last_epoch = timeClient.getEpochTime();

            apiPostEvent("watering", 1);

            digitalWrite(watering.motor_pin, LOW);

            Serial.println("Do watering");
            delay(1000 * watering.duration);
            
            digitalWrite(watering.motor_pin, HIGH);
            apiPostEvent("watering", 0);

            Serial.println("Stop watering");
        }
    }

    digitalWrite(watering.motor_pin, HIGH);
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
        apiPostEvent("lights", (float)status);
    }
    digitalWrite(lights.relay_pin, status);

    lights.last_status = status;
}

void loop()
{
    timeClient.update();
    //Serial.println(timeClient.getFormattedTime());

    if (timeClient.getMinutes() % 10 == 0 && timeClient.getEpochTime() > setting_update_epoch + 60 * 5)
    {
        apiGetSettings();
        setting_update_epoch = timeClient.getEpochTime();
    }

    handleLights();

    handleWatering();

    delay(1000);

    
}
