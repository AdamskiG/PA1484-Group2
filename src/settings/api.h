#pragma once

#include <WString.h>
#include <string>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <map>
#include "data_sort.h"

// A class to handle API call request and recieves data.
class Api
{
    private:
    String searchterm{};
    static constexpr uint32_t buff_size = 64;

    const String base_url = "https://realtime-api.trafiklab.se";
    const String stations_url = "https://api.resrobot.se/v2.1/location.nearbystops?originCoordLat=56.25743&originCoordLong=15.61855&r=25000&maxNo=1000&format=json&accessId=";
    const String api_key;
    std::map<std::string, std::map<int, std::string>> station_id_table;

    String fetch_string(String fetch_url);

    public:
    Api(const String& in_api_key);
    String get_departure(String id, const char transport_type);
    std::map<std::string, std::map<int, std::string>> get_all_stations();
};
