#include "controller.h"

Controller::Controller()
{
    
}

std::string Controller::set_stations()
{
    return std::string();
}

void Controller::save_settings(String& selected_station_option, String& selected_transport_option)
{
    // Create JsonDocument with data
    JsonDocument data;
    data["station"] = selected_station_option;
    data["vehicle"] = selected_transport_option;

    // Create uint8_t (unsigned char) array to store the deserialized JSON
    uint8_t json_c_str[256];
    serializeJson(data, json_c_str);

    // Write JSON to memory
    for (size_t i = 0; i < 256; i++)
    {
        EEPROM.write(i,json_c_str[i]);
    }
}

void Controller::load_settings(String& selected_station_option, String& selected_transport_option)
{
    // Read stored data to uint8_t (unsigned char) array
    char json_c_str[256];
    for (size_t i = 0; i < 256; i++)
    {
        json_c_str[i] = EEPROM.read(i);
    }

    // Store JSON data in JsonDocument
    JsonDocument data;
    deserializeJson(data, json_c_str, 256);

    serializeJson(data["station"], selected_station_option);
    serializeJson(data["vehicle"], selected_transport_option);
}
