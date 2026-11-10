#pragma once

#include <WString.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

// A class to handle API call request and recieves data.
class Api
{
    private:
    String searchterm{};
    static constexpr uint32_t buff_size = 64;

    const String base_url = "https://realtime-api.trafiklab.se";
    const String get_all_stops = "https://realtime-api.trafiklab.se/v1/stops/name/{karlskrona}?key={2b58406690a34045a9d6fb5f4292715c}";

    const String api_key;

    public:
    Api(const String& in_api_key);

    static void get_area_code(String selected_option);
    // String get_all_stations();
};
