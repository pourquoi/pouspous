#include <ArduinoHttpClient.h>
#include <ESP8266WiFi.h>

#include "PousPousApi.h"

char ssid[] = "my_wifi_ssid";
char pass[] = "my_wifi_password";
char device[] = "my_device_name";

WiFiClient wifi;
HttpClient client = HttpClient(wifi, "cataclop.fr", 9006);

PousPousApi api = PousPousApi(client, device);

void setup() 
{
    WiFi.begin(ssid, pass);

    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("Connected to WiFi, IP address: ");

    api.createDevice();
}

void loop()
{
    api.createEvent("sensor_read", (float)analogRead(A0));
    delay(5000);
}
