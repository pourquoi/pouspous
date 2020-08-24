Arduino sketch configuration
---

In *preferences > card URL* paste https://arduino.esp8266.com/stable/package_esp8266com_index.json
In *tools > Card type* select *LOLIN(WEMOS) D1 R2 & mini*
In *tools > libraries* install *ArduinoJson* and *ArduinoHttpClient*

In the code change your wifi ssid / password and choose a name for the device (it will be your login on the app)

Circuit
---
Just connect an analog sensor to A0

That's it, upload the sketch to the D1 and login to http://cataclop.fr:9006.