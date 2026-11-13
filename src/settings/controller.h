#pragma once

#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1

#include <WString.h>
#include <string>
#include <ArduinoJson.h>
#include <EEPROM.h>
#include <Stream.h>

#include "api.h"
#include "user_interface/ui.h"
#include "user_interface/front_page.h"
#include "user_interface/settings_page.h"
#include "user_interface/departure_page.h"
#include "data_sort.h"


// A central class that handles the exchange of data to minimize the entanglement of three classes
// Settings sends data to controller. Controller handels the data and sends it along. Knows about API, Sorting and departure.
class Controller
{
    private:
    Departure* departure_ptr = nullptr;
    const String key_departure;
    const String key_lookup;
    static Settings settings_p;
    static Front_Page front_p;
    Api api;
    static Data_Sort sort;

    static void on_confirm_btn_clicked(lv_event_t* event);
    void get_departure_data();
    public:
    Controller(const String& key_departure, const String& key_lookup);
    ~Controller();
    void init();
    
    std::string set_stations();

    void save_settings(String& selected_station_option, String& selected_transport_option);
    void load_settings(String& selected_station_option, String& selected_transport_option);
};