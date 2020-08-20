#include "PousPousApi.h"

PousPousApi::PousPousApi(HttpClient &aClient, const String &aDevice)
 : mClient(aClient), mDevice(aDevice)
{
}

void PousPousApi::createDevice()
{
#ifdef LOGGING
    Serial.println("Creating device");
#endif

    msg_post_device["name"] = mDevice;

    String json;
    serializeJson(msg_post_device, json);

    mClient.beginRequest();
    mClient.post("/api/devices");
    mClient.sendHeader("Content-Type", "application/json");
    mClient.sendHeader("Accept", "application/json");
    mClient.sendHeader("Content-Length", json.length());
    mClient.beginBody();
    mClient.print(json);
    mClient.endRequest();

    int statusCode = mClient.responseStatusCode();

#ifdef LOGGING
    Serial.print("Status code: ");
    Serial.println(statusCode);
#endif
}

void PousPousApi::createEvent(const String &type, float value)
{
#ifdef LOGGING
    Serial.print("Creating event: ");
    Serial.print(type);
    Serial.print(" = ");
    Serial.println(value);
#endif

    msg_post_event["device"] = mDevice;
    msg_post_event["type"] = type;
    msg_post_event["value"] = value;

    String json;
    serializeJson(msg_post_event, json);

    mClient.beginRequest();
    mClient.post("/api/events");
    mClient.sendHeader("Content-Type", "application/json");
    mClient.sendHeader("Accept", "application/json");
    mClient.sendHeader("Content-Length", json.length());
    mClient.beginBody();
    mClient.print(json);
    mClient.endRequest();

    int statusCode = mClient.responseStatusCode();

#ifdef LOGGING
    Serial.print("Status code: ");
    Serial.println(statusCode);
#endif
}

bool PousPousApi::getSetting(const String &name, float &value)
{
#ifdef LOGGING
    Serial.println(String("Getting setting " + name));
#endif

    String url = String("/api/device_settings?name=" + name);

    mClient.beginRequest();
    mClient.get(url);
    mClient.sendHeader("Accept", "application/json");
    mClient.sendHeader("X-Device", mDevice);
    mClient.endRequest();

    int statusCode = mClient.responseStatusCode();

#ifdef LOGGING
    Serial.print("Status code: ");
    Serial.println(statusCode);
#endif

    if (statusCode != 200)
    {
        return false;
    }

    String response = mClient.responseBody();

    const size_t capacity = 2048;
    DynamicJsonDocument doc(capacity);
    DeserializationError error = deserializeJson(doc, response);
    if (error)
    {
#ifdef LOGGING
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
#endif
        return false;
    }

    int l = doc.size();
    int i;
    for (i = 0; i < l; i++)
    {
        const char *setting = doc[i]["name"].as<char *>();
        value = doc[i]["value"].as<float>();
        return true;
    }

    return false;
}
