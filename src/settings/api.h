#pragma once

#include <string>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <map>

// A class to handle API call request and recieves data.
class Api
{
    private:
    String searchterm{};
    static constexpr uint32_t buff_size = 64;

    const String base_url = "https://realtime-api.trafiklab.se";
    const String stations_url = "https://api.resrobot.se/v2.1/location.nearbystops?originCoordLat=56.2845&originCoordLong=15.5575&r=14500&maxNo=1000&format=json&accessId=";
    String key_departure;
    String key_lookup;

    String fetch_data_string(String fetch_url);

    public:
    Api(const String& key_departure, const String& key_lookup);
    String fetch_departures(String id);
    String fetch_all_stations();

};
