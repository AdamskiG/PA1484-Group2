#pragma once
#define JSMN_HEADER

#include <iostream>
#include <unordered_map>
#include <vector>
#include "settings/json_parse.h"

enum Transport_Types
{
    TRAIN,
    BUS,
    FERRY,
    METRO
};

struct Departure_Data
{
    std::string departure_time;

    Transport_Types vehicle_type;
    std::string vehicle_name;

    std::string destination;

    Departure_Data(Json_Parser departure_parser);
    Departure_Data(Json_Data departure);
};

struct Departure_Data_Holder
{
    std::vector<Departure_Data> data;
    std::string station;

    Transport_Types vehicle_filter;

    void loadFromJson(Json_Data& json, std::string area_name, Transport_Types in_vehicle_filter);
    void clear();
};

