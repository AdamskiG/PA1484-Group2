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
    String url = this->url_stopcode_lookup + this->get_all_stops;
    http.begin(url);

    String stations_data = http.getString();

    return stations_data;
}