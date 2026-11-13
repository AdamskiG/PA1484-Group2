#pragma once
#include <ArduinoJson.h>
#include <algorithm>
#include <string>
#include <map>
#include <cctype>

#include "user_interface/departure_data.h"

// A class to sort the incoming data
class Data_Sort
{
    private:
    std::map<String, std::map<String, String>> station_id_table;

    String clean_name(String station_name);
    String decipher_transport(int products);
    std::string capitalize(std::string transport_type);

    public:
    std::map<String, std::map<String, String>> get_all_stations(String json_file);
    Departure_Data_Holder get_departure_times(String json_file, String station_name, String transport_type);
};