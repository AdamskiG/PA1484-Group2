#include "controller.h"

Controller::Controller(const String& KEY, const String& KEY_RES)
    :api(KEY, KEY_RES)
{

}

Controller::~Controller()
{

}

void Controller::init()
{
    EEPROM.begin(256);

    // Initialize Front Page
    front_p.create();
    Serial.printf("Front page created\n");

    // Initialize Settings Page
    String stations_string = api.fetch_all_stations();
    Serial.printf("Station/Transport Data Fetched\n");
    std::map<String, std::map<String, String>> station_map = sort.get_all_stations(stations_string);
    settings_p.set_station_id_table(station_map);
    Serial.printf("Station/Transport Data stored\n");
    settings_p.create();
    Serial.printf("Settings page created\n");

    // Initialize Departures Page
    departure_p.create();
    Serial.printf("Departure page created\n");

    // Connect Settings Page button press events to Controller
    lv_obj_add_event_cb(settings_p.get_confirmed_button(), on_confirm_btn_clicked, LV_EVENT_CLICKED, this);
    Serial.printf("confirm_btn functionality implemented\n");
    lv_obj_add_event_cb(settings_p.get_save_button(), on_save_btn_clicked, LV_EVENT_CLICKED, this);
    
    lv_obj_add_event_cb(settings_p.get_load_button(), on_load_btn_clicked, LV_EVENT_CLICKED, this);
}


void Controller::on_confirm_btn_clicked(lv_event_t* event)
{
    Controller* self = static_cast<Controller*>(lv_event_get_user_data(event));
    self->settings_p.get_selected();

    String station_id = self->settings_p.get_station_id();

    String selected_station = self->settings_p.get_station();
    String selected_transport = self->settings_p.get_transport();

    Departure_Data_Holder data = self->sort.get_departure_times(self->api.fetch_departures(station_id), selected_station, selected_transport);

    self->departure_p.show_departure(data);

}

void Controller::on_save_btn_clicked(lv_event_t *event)
{
    Controller* self = static_cast<Controller*>(lv_event_get_user_data(event));

    String selected_station = self->settings_p.get_station();
    String selected_transport = self->settings_p.get_transport();

    self->save_settings(selected_station, selected_transport);
}

void Controller::on_load_btn_clicked(lv_event_t *event)
{
    String selected_station;
    String selected_transport;

    Controller* self = static_cast<Controller*>(lv_event_get_user_data(event));

    self->load_settings(selected_station, selected_transport);

    self->settings_p.set_station(selected_station);
    self->settings_p.set_transport(selected_transport);
}

void Controller::save_settings(const String& selected_station_option, const String& selected_transport_option)
{
    // Create JsonDocument with data
    JsonDocument data;
    data["station"] = selected_station_option;
    data["vehicle"] = selected_transport_option;

    // Create uint8_t (unsigned char) array to store the deserialized JSON
    int json_length = data.as<String>().length();
    uint8_t json_c_str[256];
    serializeJson(data, json_c_str);

    for (int i = 0; i < json_length; i++)
    {
        EEPROM.put(sizeof(uint8_t) * i, json_c_str[i]);
    }
}

void Controller::load_settings(String& selected_station_option, String& selected_transport_option)
{
    // Read stored data to uint8_t (unsigned char) array
    uint8_t json_c_str[256];

    for (int i = 0; i < 256; i++)
    {
        EEPROM.get(sizeof(uint8_t) * i, json_c_str[i]);
    }

    // Store JSON data in JsonDocument
    JsonDocument data;
    deserializeJson(data, json_c_str, 256);

    String data_station = data["station"];
    String data_vehicle = data["vehicle"];

    selected_station_option = data_station;
    selected_transport_option = data_vehicle;
}

void Controller::update_WiFi_status()
{
    this->settings_p.update_WiFi_status();
}
