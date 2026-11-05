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