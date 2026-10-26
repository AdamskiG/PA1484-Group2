#include "api.h"

// Function: Connects to WIFI
void api::connect_wifi()
{
    Serial.printf("Connecting to WiFi SSID: %s\n", WIFI_SSID);
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    const uint32_t start = millis();
    while (WiFi.status() != WL_CONNECTED && (millis() - start) < 15000) 
    {
        delay(250);
    }
    Serial.println();
    
    if (WiFi.status() == WL_CONNECTED) 
    {
        Serial.print("WiFi connected.");
    }
    else 
    {
        Serial.println("WiFi could not connect (timeout).");
    }
}

bool api::call_request()
{
    
}