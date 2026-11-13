#include "controller.h"

Controller::Controller(const String& key_departure, const String& key_lookup)
    :api(key_departure, key_lookup)
{

}

Controller::~Controller()
{

}

void Controller::init()
{
    front_p.create();
    settings_p.set_station_id_table(sort.get_all_stations(api.fetch_all_stations()));
    settings_p.create();
    departure_p.create();
    lv_obj_add_event_cb(settings_p.get_confirmed_button(), on_confirm_btn_clicked, LV_EVENT_CLICKED, NULL);
}

std::string Controller::set_stations()
{

    return std::string();
}

void Controller::on_confirm_btn_clicked(lv_event_t* event)
{
    Controller* self = static_cast<Controller*>(lv_event_get_user_data(event));

    self->settings_p.get_selected();
    String station_id = settings_p.get_station_id();
    String selected_station = settings_p.get_station();
    String selected_transport = settings_p.get_transport();

    Departure_Data_Holder data_store = self->sort.get_departure_times(self->api.fetch_departures(station_id), selected_station, selected_transport);   
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
