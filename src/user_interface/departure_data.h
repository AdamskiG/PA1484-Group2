#pragma once
#define ARDUINOJSON_ENABLE_ARDUINO_STRING true 

#include <iostream>
#include <unordered_map>
#include <vector>
#include <ArduinoJson.h>

// Holds data that needs to be shown for each departure
struct Departure_Data
{
    std::string departure_time;

    std::string vehicle_type;
    std::string vehicle_name;

    std::string destination;

    // Constructors
    Departure_Data(Departure_Data& other);
    Departure_Data(JsonObject departure);

    Departure_Data& operator=(Departure_Data& other);

    Departure_Data& copy(Departure_Data& other);
};

// Struct that holds all necessary departure data in a string.
// Is able to generate a departure data list when given a valid json as a char array
struct Departure_Data_Holder
{
    std::vector<Departure_Data*> data;
    std::string station;

    std::string vehicle_filter;

    // Functions to load and clear data
    void load_from_json(const char* json, std::string area_name, std::string in_vehicle_filter);
    void clear();
};

