#include "api.h"
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

bool api::call_request(String selected_option)
{
    WiFiClientSecure client;
    HTTPClient https;
    api::url_stopcode_lookup = url_stopcode_lookup + selected_option; 
    https.begin(client, url_stopcode_lookup);
    
}

String api::get_all_stations()
{
    HTTPClient http;
    String url = this->url_stopcode_lookup + this->get_all_stops;
    http.begin(url);

    String stations_data = http.getString();

    return stations_data;
}