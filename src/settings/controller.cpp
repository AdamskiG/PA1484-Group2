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
    front_p.create();
    Serial.printf("Front page created");
    settings_p.set_station_id_table(sort.get_all_stations(api.fetch_all_stations()));
    Serial.printf("Dropdown data Fetched and stored");
    settings_p.create();
    Serial.printf("Settings page created");
    departure_p.create();
    Serial.printf("Departure page created");
    lv_obj_add_event_cb(settings_p.get_confirmed_button(), on_confirm_btn_clicked, LV_EVENT_CLICKED, this);
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
    String selected_station;
    String selected_transport;

    Controller* self = static_cast<Controller*>(lv_event_get_user_data(event));

    self->load_settings(selected_station, selected_transport);

    self->settings_p.set_station_text(selected_station);
    self->settings_p.set_transport_text(selected_transport);
}

void Controller::on_load_btn_clicked(lv_event_t *event)
{
    Controller* self = static_cast<Controller*>(lv_event_get_user_data(event));

    String selected_station = self->settings_p.get_station();
    String selected_transport = self->settings_p.get_transport();

    self->save_settings(selected_station, selected_transport);
}

void Controller::save_settings(String selected_station_option, String selected_transport_option)
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

void Controller::load_settings(String selected_station_option, String selected_transport_option)
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

void Controller::update_UI()
{
    this->settings_p.update();
}
