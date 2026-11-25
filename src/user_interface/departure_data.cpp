#include "departure_data.h"

// Copy constructor
Departure_Data::Departure_Data(Departure_Data &other)
{
    copy(other);
}

// Constructs departure data based on a given ArduinoJson JsonObject
// Assumes json follows the structure of Trafiklab Realtime API's departure data
Departure_Data::Departure_Data(JsonVariant& departure_data)
{
    String departure_time_full = departure_data["scheduled"];
    this->departure_time = departure_time_full.substring(11, 16);
    this->platform = departure_data["realtime_platform"]["designation"].as<String>();
    JsonObject route = departure_data["route"];

    String transport_mode = route["transport_mode"];
    this->vehicle_type = transport_mode;

    this->vehicle_number = route["designation"].as<String>();

    JsonObject destination = route["destination"];
    this->destination_name = destination["name"].as<String>();
}

// Equals operator
Departure_Data &Departure_Data::operator=(Departure_Data &other)
{
    return copy(other);
}

// Copy all variables of other to this
Departure_Data &Departure_Data::copy(Departure_Data &other)
{
    departure_time = other.departure_time;
    vehicle_type = other.vehicle_type;
    vehicle_number = other.vehicle_number;
    destination_name = other.destination_name;
    platform = other.platform;
    return *this;
}

// Constructs departure data list based on a character string
// Assumes json follows the structure of Trafiklab Realtime API's departure data
void Departure_Data_Holder::load_from_json(const String& json_c_str, String area_name, String in_vehicle_filter)
{
    clear();

    station = area_name;
    vehicle_filter = in_vehicle_filter;
    in_vehicle_filter.toUpperCase();
    in_vehicle_filter.trim();
    

    // Convert char string to "doc" JsonDocument object
    JsonDocument doc;
    deserializeJson(doc, json_c_str);

    JsonArray departures = doc["departures"];

    // Creates departure data vector by iterating through the json's departures
    for (JsonVariant departure : departures)
    {
        Departure_Data* departure_data = new Departure_Data(departure);
        data.push_back(departure_data);

        // Discards the departure data if the vehicle type doesn't match
        /*!!!!!!!! OBS !!!!! Detta är där felet ligger just nu då det finns osynliga bokstäver
        Så det är därför jämförelsen inte funkar
        */
        // if (departure_data->vehicle_type == in_vehicle_filter)
        // {
        //     data.push_back(departure_data);
        // }
    //     else
    //     {
    //         delete departure_data;
    //     }
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

Journey_Data::Journey_Data(Journey_Data &other)
{
    copy(other);
}

Journey_Data::Journey_Data(JsonVariant& journey_data)
{
    String departure = journey_data["Origin"]["time"];
    this->departure_time = departure.substring(0,4);
    String arrival = journey_data["Destination"]["time"];
    this->arrival_time = arrival.substring(0,4);
    this->vehicle_number = journey_data["Leglist"]["Leg"]["Product"]["line"].as<String>();
}

Journey_Data &Journey_Data::operator=(Journey_Data &other)
{
    return copy(other);
}

Journey_Data &Journey_Data::copy(Journey_Data &other)
{
    departure_time = other.departure_time;
    arrival_time = other.arrival_time;
    vehicle_number = other.vehicle_number;

    return *this;
}

void Journey_Data_Holder::load_from_json(const String &json, String area_name, String in_vehicle_filter)
{
    JsonDocument doc;
    deserializeJson(doc, json);
    JsonArray journey = doc["Trip"];

    for(JsonVariant journey_info : journey)
    {
        Journey_Data* journey_stats = new Journey_Data(journey_info);
        data.push_back(journey_stats);
    }
}
