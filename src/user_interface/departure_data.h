#pragma once

#include <iostream>
#include <vector>
#include <ArduinoJson.h>

// Holds data that needs to be shown for each departure
struct Departure_Data
{
    String departure_time;
    String vehicle_type;
    String vehicle_number;
    String platform;
    String destination_name;

    // Constructors
    Departure_Data(Departure_Data& other);
    Departure_Data(JsonVariant& departure);

    Departure_Data& operator=(Departure_Data& other);

    Departure_Data& copy(Departure_Data& other);
};

// Struct that holds all necessary departure data in a string
// Is able to generate a departure data list when given a valid json as a char array
struct Departure_Data_Holder
{
    std::vector<Departure_Data*> data;
    String station;

    String vehicle_filter;

    // Functions to load and clear data
    void load_from_json(const String& json, String area_name, String in_vehicle_filter);
    void clear();
};

struct Journey_Data
{
    String departure_time;
    String arrival_time;
    String vehicle_number;
    String destination_name;

    // Constructors
    Journey_Data(Journey_Data& other);
    Journey_Data(JsonVariant& journey_data);

    Journey_Data& operator=(Journey_Data& other);

    Journey_Data& copy(Journey_Data& other);
};

struct Journey_Data_Holder
{
    std::vector<Journey_Data*> data;
    String station;

    String vehicle_filter;

    // Functions to load and clear data
    void load_from_json(const String& json, String area_name, String in_vehicle_filter);
    void clear();
};