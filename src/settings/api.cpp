#include "api.h"

void api::connect_wifi()
{
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    WiFi.localIP();
}

bool api::call_request()
{
    
}