#include "controller.h"

String sort_function(String gogogaga)
{
    
}

Controller::Controller()
{
    
}

std::string Controller::set_stations()
{
    return std::string();
}

void Controller::save_settings(char* selected_station_option, char* selected_transport_option, uint32_t buff_size)
{
    // Create JsonDocument with data
    JsonDocument data;
    data["station"] = selected_station_option;
    data["vehicle"] = selected_transport_option;

    // Create uint8_t (unsigned char) array to store the deserialized JSON
    uint8_t json_c_str[buff_size * 3];
    deserializeJson(data, json_c_str);

    // Write JSON to memory
    for (size_t i = 0; i < buff_size * 3; i++)
    {
        EEPROM.write(i,json_c_str[i]);
    }
}

void Controller::load_settings(char* selected_station_option, char* selected_transport_option, uint32_t buff_size)
{
    // Read stored data to uint8_t (unsigned char) array
    char json_c_str[buff_size * 3];
    for (size_t i = 0; i < buff_size * 3; i++)
    {
        json_c_str[i] = EEPROM.read(i);
    }

    // Store JSON data in JsonDocument
    JsonDocument data;
    serializeJson(data, json_c_str, buff_size * 3);

    // Store JsonDocument's attributes as const char strings
    const char* station_c_str = data["station"];
    const char* vehicle_c_str = data["station"];

    // Update options to match strings
    selected_station_option = new char[buff_size * 3];
    selected_transport_option = new char[buff_size * 3];
    for (int i = 0; i < buff_size * 3; i++)
    {
        *(selected_station_option + i) = *(station_c_str + i);
        *(selected_transport_option + i) = *(vehicle_c_str + i);
    }
}
