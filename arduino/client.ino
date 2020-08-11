#include <ESP8266WiFi.h>

WiFiClient client;

IPAddress server(192,168,0,21);
char servername[]="192.168.0.21";

// nommer la station
char device[]="pouspous";

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  Serial.println();

  // remplacer par les accès wifi
  WiFi.begin("mon_wifi", "mot_de_passe");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  if (client.connect(servername, 9006)) {
    Serial.println("connected");
    client.print("GET /api/devices?name=");
    client.print(device);
    client.println(" HTTP/1.0");
    client.println();
  } else {
    Serial.println("could not connect");
  }
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}