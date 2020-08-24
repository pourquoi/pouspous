#ifndef PousPousApi_h
#define PousPousApi_h

#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

#define LOGGING

class PousPousApi
{
public:
    PousPousApi(HttpClient &aClient, const String &aDevice);

    void createDevice();

    void createEvent(const String &type, float value);

    bool getSetting(const String &name, float &value);

protected:
    HttpClient mClient;
    String mDevice;

    static const int msg_post_device_capacity = JSON_OBJECT_SIZE(1) + 60;
    StaticJsonDocument<msg_post_device_capacity> msg_post_device;

    static const int msg_post_event_capacity = JSON_OBJECT_SIZE(3) + 60;
    StaticJsonDocument<msg_post_event_capacity> msg_post_event;
};

#endif
