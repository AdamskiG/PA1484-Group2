#include "api.h"
#include "../project/key.h"
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

bool Api::call_request(String selected_option)
{
    // Create a secure HTTP Client but set it to insecure
    WiFiClientSecure* client = new WiFiClientSecure;
    Api::url_stopcode_lookup = url_stopcode_lookup + "?key=" + KEY;
    client->setInsecure();
    {
        HTTPClient https;
        if (https.begin(*client, url_stopcode_lookup))
        {

        }
    }
}

String Api::get_all_stations()
{
    HTTPClient http;
    http.begin(url);
    int httpResponseCode = http.GET();

    if(httpResponseCode == HTTP_CODE_OK){
        String stations_data = http.getString();
        http.end();
        return stations_data;
    }

    http.end();
    return String();
}