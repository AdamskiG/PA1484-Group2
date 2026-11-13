#pragma once

#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1

#include <WString.h>
#include <string>
#include <ArduinoJson.h>
#include <EEPROM.h>
#include <Stream.h>

#include "api.h"
#include "data_sort.h"
#include "user_interface/ui.h"
#include "user_interface/departure_page.h"


// A central class that handles the exchange of data to minimize the entanglement of three classes
// Settings sends data to controller. Controller handels the data and sends it along. Knows about API, Sorting and departure.
class Controller
{
    private:
    Departure* departure_ptr = nullptr;

    public:
    Controller();
    
    std::string set_stations();

    void save_settings(String& selected_station_option, String& selected_transport_option);
    void load_settings(String& selected_station_option, String& selected_transport_option);
};