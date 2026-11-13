#include "data_sort.h"

String Data_Sort::clean_name(String station_name)
{
    String cleaned_str;
    for(const char letter : station_name)
    {
        if(letter != '(')
        {
            cleaned_str += letter;
        }
    }
    return cleaned_str;
}

String Data_Sort::decipher_transport(int products)
{
    String type;
    if((2 & products) != 0 || (4 & products) != 0 || (16 & products) != 0)
    {
        type += "Train\n";
    }

    if((8 & products) != 0 || (128 & products) != 0)
    {
        type += "Bus\n";
    }
    
    if((256 & products) != 0)
    {
        type += "Boat\n";
    }
    type.trim();
    return type;
}

std::map<String, std::map<String, String>> Data_Sort::get_all_stations(String json_file)
{
    JsonDocument doc;
    deserializeJson(doc, json_file);
    JsonArray array = doc["stopLocationOrCoordLocation"].as<JsonArray>();
    for(JsonVariant item : array)
    {
        JsonObject stop_location = item["StopLocation"];

        String name = clean_name(stop_location["name"].as<String>());
        String id = stop_location["extId"].as<String>();
        String transport_options = decipher_transport(stop_location["products"].as<int>());
        this->station_id_table[name][id] = transport_options;
    }
    return this->station_id_table;
}

Departure_Data_Holder get_departure_times(String json_file, String station_name, String transport_type)
{
    Departure_Data_Holder departures;
    departures.load_from_json(json_file, station_name, transport_type);
    return departures;
}