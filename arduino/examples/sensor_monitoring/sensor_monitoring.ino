#include <ArduinoHttpClient.h>
#include <ESP8266WiFi.h>

#include "PousPousApi.h"

char ssid[] = "my_wifi_ssid";
char pass[] = "my_wifi_password";
char device[] = "my_device";

WiFiClient wifi;
HttpClient client = HttpClient(wifi, "cataclop.fr", 9006);

PousPousApi api = PousPousApi(client, device);

void setup() 
{
}

void loop()
{
    api.createEvent("sensor_read", (float)analogRead(A0));
    delay(5000);
}
