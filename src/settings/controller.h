#pragma once
#include <WString.h>
#include <string>
#include <ArduinoJson.h>
#include <EEPROM.h>
#include <Stream.h>
#include "api.h"
#include "data_sort.h"
#include "user_interface/ui.h"

#include "../user_interface/departure_page.h"


// A central class that handles the exchange of data to minimize the entanglement of three classes
// Settings sends data to controller. Controller handels the data and sends it along. Knows about API, Sorting and departure.
class Controller
{
    private:
    static lv_fs_drv_t drive;
    Departure* departure_ptr = nullptr;
    public:
    Controller();
    
    String sort_function(String gogogaga);
    std::string set_stations();

    void save_settings(char* selected_station_option, char* selected_transport_option, uint32_t buff_size);
    void load_settings(char* selected_station_option, char* selected_transport_option, uint32_t buff_size);
};