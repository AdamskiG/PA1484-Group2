#include "controller.h"

Controller::Controller(const String& KEY, const String& KEY_RES)
{
    journey_p = new Journey_Page();
    settings_p = new Settings();
    departure_p = new Departure();
    front_p = new Front_Page();

    api = new Api(KEY, KEY_RES);
    sort = new Data_Sort();
}

Controller::~Controller()
{
    delete journey_p;
    delete settings_p;
    delete departure_p;
    delete front_p;

    delete api;
    delete sort;
}

void Controller::init()
{
    // Allocate memory for save
    EEPROM.begin(SAVE_BUF);

    // Initialize Front Page
    front_p->create();
    Serial.printf("Front page created\n");

    // Initialize Settings Page
    String stations_string = api->fetch_all_stations();
    Serial.printf("Station/Transport Data Fetched\n");
    std::map<String, std::map<String, String>> station_map = sort->get_all_stations(stations_string);

    settings_p->set_station_id_table(station_map);
    Serial.printf("Station/Transport Data stored\n");
    settings_p->create();
    Serial.printf("Settings page created\n");

    // Initialize Departures Page
    departure_p->create();
    Serial.printf("Departure page created\n");

    // Initialize Journey Page
    journey_p->create();
    Serial.printf("Journey Page created\n");

    // Connect Settings Page button press events to Controller
    lv_obj_add_event_cb(settings_p->get_confirmed_button(), on_confirm_btn_clicked, LV_EVENT_CLICKED, this);
    Serial.printf("confirm_btn functionality implemented\n");
    lv_obj_add_event_cb(settings_p->get_save_button(), on_save_btn_clicked, LV_EVENT_CLICKED, this);
    
    lv_obj_add_event_cb(settings_p->get_load_button(), on_load_btn_clicked, LV_EVENT_CLICKED, this);

    // Attempt to load settings from stored data
    if (!load_settings_page())
    {
        // If failed, save the current settings as default data
        save_settings_page();
    }
}


void Controller::on_confirm_btn_clicked(lv_event_t* event)
{
    Controller* self = static_cast<Controller*>(lv_event_get_user_data(event));
    self->update_departure_page();
}

void Controller::on_save_btn_clicked(lv_event_t *event)
{
    Controller* self = static_cast<Controller*>(lv_event_get_user_data(event));
    self->save_settings_page();
}

void Controller::on_load_btn_clicked(lv_event_t *event)
{
    Controller* self = static_cast<Controller*>(lv_event_get_user_data(event));
    self->load_settings_page();
}

bool Controller::save_settings_page()
{
    String selected_station = settings_p->get_station();
    Serial.print("Station Len:");
    Serial.print(selected_station.length());
    Serial.print("\n");
    String selected_transport = settings_p->get_transport();
    Serial.print("Transport Len:");
    Serial.print(selected_station.length());
    Serial.print("\n");

    return save_settings(selected_station, selected_transport);
}

bool Controller::load_settings_page()
{
    String selected_station;
    String selected_transport;
    
    if (!load_settings(selected_station, selected_transport))
    {
        return false;
    }

    Controller::settings_p->set_station(selected_station);
    Controller::settings_p->set_transport(selected_transport);

    return true;
}

bool Controller::save_settings(const String &selected_station_option, const String &selected_transport_option)
{
    // Create JsonDocument with data
    JsonDocument data;
    data["station"] = selected_station_option;
    data["vehicle"] = selected_transport_option;

    // Create uint8_t (unsigned char) array to store the deserialized JSON
    int json_length = data.as<String>().length();
    uint8_t json_c_str[SAVE_BUF];
    int bytesWritten = serializeJson(data, json_c_str);

    if (bytesWritten <= 0)
        return false;

    for (int i = 0; i < json_length; i++)
    {
        EEPROM.put(sizeof(uint8_t) * i, json_c_str[i]);
    }
    EEPROM.commit();

    return true;
}

bool Controller::load_settings(String& selected_station_option, String& selected_transport_option)
{
    // Read stored data to uint8_t (unsigned char) array
    uint8_t json_c_str[SAVE_BUF];

    for (int i = 0; i < SAVE_BUF; i++)
    {
        EEPROM.get(sizeof(uint8_t) * i, json_c_str[i]);
    }

    // Store JSON data in JsonDocument
    JsonDocument data;
    DeserializationError error = deserializeJson(data, json_c_str, SAVE_BUF);

    if (error != DeserializationError::Ok)
    {
        Serial.print(String("Error: could not load settings, error code: ") + error.c_str() + "\n");
        return false;
    }

    String data_station = data["station"];
    String data_vehicle = data["vehicle"];

    selected_station_option = data_station;
    selected_transport_option = data_vehicle;

    return true;
}

void Controller::update_departure_page()
{
    settings_p->get_selected();

    String station_id = settings_p->get_station_id();

    String selected_station = settings_p->get_station();
    String selected_transport = settings_p->get_transport();

    String depature_json_str = api->fetch_departures(station_id);
    Departure_Data_Holder data = sort->get_departure_times(depature_json_str, selected_station, selected_transport);

    departure_p->show_departure(data);
}

void Controller::update_WiFi_status()
{
    Controller::settings_p->update_WiFi_status();
}

