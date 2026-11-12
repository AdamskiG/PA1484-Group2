#pragma once
#include <ArduinoJson.h>
#include <algorithm>
#include <string>

// A class to sort the incoming data
class Data_Sort
{
    private:
    public:
    static int clean_id(String id_string);
    static std::string clean_name(String station_name);
    static std::string decipher_transport(int products);
};