#include <ArduinoHttpClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include "secrets.h"

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
char device[] = DEVICE;

char server_name[] = "192.168.0.21";
const int server_port = 9006;

WiFiClient wifi;

HttpClient client = HttpClient(wifi, server_name, server_port);

size_t msg_post_device_size;
const int msg_post_device_capacity = JSON_OBJECT_SIZE(1) + 60;
StaticJsonDocument<msg_post_device_capacity> msg_post_device;

size_t msg_post_event_size;
const int msg_post_event_capacity = JSON_OBJECT_SIZE(3) + 60;
StaticJsonDocument<msg_post_event_capacity> msg_post_event;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(115200);
    Serial.println();

    // remplacer par les accès wifi
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

    apiPostDevice();
}

void apiPostDevice()
{
    Serial.println("Creating device");
  
    msg_post_device["name"] = device;

    msg_post_device_size = msg_post_event.memoryUsage();

    String json;
    serializeJson(msg_post_device, json);

    Serial.println(json);

    client.beginRequest();
    client.post("/api/devices");
    client.sendHeader("Content-Type", "application/json");
    client.sendHeader("Content-Length", json.length());
    client.beginBody();
    client.print(json);
    client.endRequest();

    int statusCode = client.responseStatusCode();
    String response = client.responseBody();
  
    Serial.print("Status code: ");
    Serial.println(statusCode);
    Serial.print("Response: ");
    Serial.println(response);
}

void apiPostEvent(const char* type, float value)
{
    Serial.println("Creating event");
    
    if (!client.connect(server_name, server_port))
    {
        Serial.println("Could not connect");
        return;
    }

    msg_post_event["device"] = device;
    msg_post_event["type"] = type;
    msg_post_event["value"] = value;

    msg_post_event_size = msg_post_event.memoryUsage();

    String json;
    serializeJson(msg_post_event, json);

    Serial.println(json);

    client.beginRequest();
    client.post("/api/events");
    client.sendHeader("Content-Type", "application/json");
    client.sendHeader("Content-Length", json.length());
    client.beginBody();
    client.print(json);
    client.endRequest();
    
    int statusCode = client.responseStatusCode();
    String response = client.responseBody();
  
    Serial.print("Status code: ");
    Serial.println(statusCode);
    Serial.print("Response: ");
    Serial.println(response);
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);
    apiPostEvent("watering", 1.0);
    delay(1000);

    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
}
