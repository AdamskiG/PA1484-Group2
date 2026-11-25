#include "api.h"

Api::Api(const String& KEY, const String& KEY_RES) 
    : key_departure(KEY), key_lookup(KEY_RES)
{

}

String Api::fetch_data_string(String fetch_url)
{
    // Create a secure HTTP Client but set it to insecure
    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient https;
    String response = "";

    // The begin connects the device to the url
    if (https.begin(client, fetch_url))
    {
        // https.GET() sends a code verifying that the connection is okay
        int https_code = https.GET();

        // Returns 200 if okay and 404 if not okay. The HTTP_CODE_OK = 200
        if (https_code == HTTP_CODE_OK) 
        {
            // getString() makes the call and get the information
            response = https.getString();
        }
        else
        {
        // Serial.printf should work with the "monitor" function in platform.io
        Serial.printf("HTTP GET failed, error code: 404");
        } 
        https.end();//Closes the connection
    }
    else
    {
        Serial.printf("HTTPS begin failed");
    }
    return response;
}

String Api::fetch_departures(String id)
{
    String fetch_url = base_url + "/v1/departures/" + id + "/?key=" + key_departure;
    String response = fetch_data_string(fetch_url);
    return response;
}

String Api::fetch_journey(String origin_id, String destination_id)
{
    String fetch_url = journey_url + origin_id + "&destId=" + destination_id + "&passlist=true&showPassingPoints=true&accessId=" + key_departure;
    String response = fetch_data_string(fetch_url);
    return response;
}

String Api::fetch_all_stations()
{
    String fetch_url = stations_url + key_lookup;
    String response = fetch_data_string(fetch_url);
    return response;
}
