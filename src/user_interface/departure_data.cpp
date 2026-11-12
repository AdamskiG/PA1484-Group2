#include "departure_data.h"

// Copy constructor
Departure_Data::Departure_Data(Departure_Data &other)
{
    copy(other);
}

// Constructs departure data based on a given ArduinoJson JsonObject
// Assumes json follows the structure of Trafiklab Realtime API's departure data
Departure_Data::Departure_Data(JsonObject departure_data)
{
    
    JsonObject route = departure_data["route"];

    std::string departure_time_full = route["transport_mode"];
    departure_time = departure_time_full.substr(12,4);

    std::string transport_mode = route["transport_mode"];
    vehicle_type = transport_mode;

    JsonObject destination = route["destination"];
    destination = destination["name"];
}

// Equals operator
Departure_Data &Departure_Data::operator=(Departure_Data &other)
{
    copy(other);
}

// Copy all variables of other to this
Departure_Data &Departure_Data::copy(Departure_Data &other)
{
    departure_time = other.departure_time;
    vehicle_type = other.vehicle_type;
    vehicle_name = other.vehicle_name;
    destination = other.destination;
}

// Constructs departure data list based on a character string
// Assumes json follows the structure of Trafiklab Realtime API's departure data
void Departure_Data_Holder::load_from_json(String json_c_str, std::string area_name, std::string in_vehicle_filter)
{
    clear();

    station = area_name;

    // Convert char string to "doc" JsonDocument object
    JsonDocument doc;
    deserializeJson(doc, json_c_str);

    JsonArray departures = doc["departures"];

    // Creates departure data vector by iterating through the json's departures
    for (JsonObject departure : departures)
    {
        Departure_Data* departure_data = new Departure_Data(departure);

        // Discards the departure data if the vehicle type doesn't match
        if (departure_data->vehicle_type == in_vehicle_filter)
        {
            data.push_back(departure_data);
        }
        else
        {
            delete departure_data;
        }
    }
}

// Erases all information in the departure data holder
void Departure_Data_Holder::clear()
{
    station.clear();
    vehicle_filter.clear();

    // Remove the data at each pointer in the departure data list
    for (Departure_Data* departure_data : data)
        delete departure_data;
    data.clear();
}
