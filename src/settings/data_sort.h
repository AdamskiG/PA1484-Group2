#pragma once
#include <ArduinoJson.h>
#include <algorithm>
#include <string>
#include <map>
#include <cctype>

// A class to sort the incoming data
class Data_Sort
{
    private:
    std::map<std::string, std::map<String, std::string>> station_id_table;

    std::string clean_name(String station_name);
    std::string decipher_transport(int products);
    std::string capitalize(std::string transport_type);

    public:
    std::map<std::string, std::map<String, std::string>> get_all_stations(String json_file);
    std::string get_departure_times(String json_file, std::string transport_type);
};