#include "api.h"

Api::Api(const String &in_api_key) : api_key(in_api_key)
{

}

const String Api::fetch_string(String fetch_url)
{
    // Create a secure HTTP Client but set it to insecure
    WiFiClientSecure* client = new WiFiClientSecure;
    client->setInsecure();

    // Brackets to ensure HttpClient terminates before WifiClient
    {
        HTTPClient https;

        // The begin connects the device to the url
        if (https.begin(*client, fetch_url))
        {
            // https.GET() sends a code verifying that the connection is okay
            int https_code = https.GET();

            // Returns 200 if okay and 404 if not okay. The HTTP_CODE_OK = 200
            if (https_code == HTTP_CODE_OK) 
            {
                // getString() makes the call and get the information
                String response = https.getString();
                https.end();
                return response;
            }
            else 
            {
            // Serial.printf should work with the "monitor" function in platform.io
            Serial.printf("HTTP GET failed, error code: 404");
            }
        https.end(); //Closes the connection
        }
    delete client;
    }
}

String Api::clean_string(String station_name)
{
    String* cleaned_str;
    for(char letter : station_name)
    {
        if(letter != *"(")
        {
            cleaned_str += letter;
        }
    }
    return *cleaned_str;
}

String Api::get_area_code(String selected_option)
{
    String fetch_url = base_url + "/name/" + selected_option + "/?key=" + api_key;

    String response = fetch_string(fetch_url);

    // JsonDocument found in ArduinoJson, Stores a JSON document in memory
    JsonDocument doc;
    deserializeJson(doc, response); // Json to text

    // Deserialize the JsonDocument as an array and iterate through it taking every id element (I think, haven't tested)
    for(JsonDocument item : doc.JsonDocument::as<JsonArray>())
    {
        const char* id = doc["id"];
        Serial.printf(id); // for debugging
    }

}


const std::vector<String>& Api::get_all_stations()
{
    String fetch_url = stations_url + api_key;

    String response = fetch_string(fetch_url);

    // JsonDocument found in ArduinoJson, Stores a JSON document in memory
    JsonDocument doc;
    deserializeJson(doc, response); // Json to text

    // Deserialize the JsonDocument as an array and iterate through it taking every id element 
    JsonArray array = doc["stopLocationOrCoordLocation"].as<JsonArray>();
    for(JsonVariant item : array)
    {
        JsonObject stop_location = item["StopLocation"];
        this->station_options.push_back(clean_string(stop_location["name"].as<String>()));
    }
    return this->station_options;
}
