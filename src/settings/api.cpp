#include "api.h"
#include "../project/key.h"
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

void Api::get_area_code(String selected_option)
{
    // Create a secure HTTP Client but set it to insecure
    WiFiClientSecure* client = new WiFiClientSecure;
    Api::url_stopcode_lookup = url_stopcode_lookup + selected_option + "/?key=" + KEY;
    client->setInsecure();
    {
        HTTPClient https;
        if (https.begin(*client, url_stopcode_lookup))
        {
            int https_code = https.GET();

            if (https_code == HTTP_CODE_OK) 
            {
                String response = https.getString();
                
            } 
            else 
            {
            Serial.printf("HTTP GET failed, error code: %d (%s)\n", https_code, https.errorToString(https_code).c_str());
            }

        https.end();
    }

    delete client;
            }
        }


String Api::get_all_stations()
{
    HTTPClient http;
    // http.begin(url);
    int httpResponseCode = http.GET();

    if(httpResponseCode == HTTP_CODE_OK){
        String stations_data = http.getString();
        http.end();
        return stations_data;
    }

    http.end();
    return String();
}