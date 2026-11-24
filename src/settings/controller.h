#pragma once

#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1

#include <WString.h>
#include <string>
#include <ArduinoJson.h>
#include <EEPROM.h>

#include "api.h"
#include "user_interface/ui.h"
#include "user_interface/front_page.h"
#include "user_interface/settings_page.h"
#include "user_interface/departure_page.h"
#include "user_interface/journey_page.h"
#include "data_sort.h"

#define SAVE_BUF 256


// A central class that handles the exchange of data to minimize the entanglement of three classes
// Settings sends data to controller. Controller handels the data and sends it along. Knows about API, Sorting and departure.
class Controller
{
    private:
    const String key_departure;
    const String key_lookup;

    Journey_Page* journey_p;
    Settings* settings_p;
    Departure* departure_p;
    Front_Page* front_p;

    Api* api;
    Data_Sort* sort;

    // Button events
    static void on_confirm_btn_clicked(lv_event_t* event);
    static void on_save_btn_clicked(lv_event_t* event);
    static void on_load_btn_clicked(lv_event_t* event);

    // Save/Load
    bool save_settings_page();
    bool load_settings_page();

    bool save_settings(const String& selected_station_option, const String& selected_transport_option);
    bool load_settings(String& selected_station_option, String& selected_transport_option);

    void confirm_settings();

    public:
    Controller(const String& key_departure, const String& key_lookup);
    ~Controller();
    void init();

    void update_WiFi_status(); // function for updating the wifi status
    void update_departure_page(); // function for updating the departure page
};