#include "api.h"

Api::Api(const String &in_api_key) : api_key(in_api_key)
{
}

void Api::get_area_code(String selected_option)
{
    // Create a secure HTTP Client but set it to insecure
    WiFiClientSecure* client = new WiFiClientSecure;
    String fetch_url = "url_stopcode_lookup/name/selected_option/?key=api_key";
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

                // JsonDocument found in ArduinoJson, Stores a JSON document in memory: https://arduinojson.org/v7/api/jsondocument/ (SORRY KIMI <3)
                JsonDocument doc;
                deserializeJson(doc, response); // Json to text

                // Deserialize the JsonDocument as an array and iterate through it taking every id element (I think, haven't tested)
                for(JsonDocument item : doc.as<JsonArray>())
                {
                    const char* id = doc["id"];
                    Serial.printf(id); // for debugging
                }
                // get_departures(id);
            }
            else 
            {
            // Serial.printf should work with the "monitor" function in platform.io
            // with further research I found that you have to press the RST button for it to print back and forth
            Serial.printf("HTTP GET failed, error code: 404");
            }
        https.end(); //Closes the connection
    }
    delete client;
    }
}


// String Api::get_all_stations()

// {
//     // Create a secure HTTP Client but set it to insecure
//     WiFiClientSecure* client = new WiFiClientSecure;
//     Api::url_stopcode_lookup = url_stopcode_lookup + "/list/?key=" + KEY;
//     client->setInsecure();
//     {
//         HTTPClient https;
//         if (https.begin(*client, url_stopcode_lookup))
//         {
//             int https_code = https.GET();

//             if (https_code == HTTP_CODE_OK) 
//             {
//                 String response = https.getString();

//                 JsonDocument doc;

//                 deserializeJson(doc, response);

//                 for(JsonDocument item : doc.as<JsonArray>())
//                 const char* id = doc[0]["id"];
//             }
//             else 
//             {
//             Serial.printf("HTTP GET failed, error code: 404");
//             }
//         https.end();
//     }
//     delete client;
//     }
// }
