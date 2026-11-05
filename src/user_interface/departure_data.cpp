#include "departure_data.h"

Json_Data::Json_Data(char* inData, size_t inSize)
    : data(inData), size(inSize)
{
}

Json_Data::Json_Data(const char* inData, const size_t inSize)
    : data(inData), size(inSize)
{
}

Departure_Data::Departure_Data(Json_Data departure) : Departure_Data(Json_Parser(&departure))
{
}

Departure_Data::Departure_Data(Json_Parser departure_parser)
{
    Json_Parser route = departure_parser.at_key("route").at_index(0);

    departure_time = departure_parser.at_key("realtime").at_index(0).get_string();

    std::string transport_mode_string = route.at_key("transport_mode").at_index(0).get_string();
    if (transport_mode_string == "TRAIN")
        vehicle_type = TRAIN;
    else if (transport_mode_string == "BUS")
        vehicle_type = BUS;
    else if (transport_mode_string == "FERRY")
        vehicle_type = FERRY;
    else if (transport_mode_string == "METRO")
        vehicle_type = METRO;

    destination = route.at_key("destination").at_index(0).at_key("name").at_index(0).get_string();
}