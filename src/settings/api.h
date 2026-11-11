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
    const String stations_url = "https://api.resrobot.se/v2.1/location.nearbystops?originCoordLat=56.25743&originCoordLong=15.61855&r=25000&maxNo=1000&format=json&accessId=";
    const String api_key;
    String station_options;

    const String fetch_string(String fetch_url);
    String clean_string(String station_name);

    public:
    Api(const String& in_api_key);

    String get_area_code(String selected_option);
    String get_all_stations();
};
