#include "settings_page.h"

Settings::Settings()
{

}

Settings::~Settings()
{

}

void Settings::create()
{
    // Adds the settings tileview
    Settings::settings_tile = lv_tileview_add_tile(Ui::tileview, 2, 0, LV_DIR_HOR);

    // Create a label for the settings UI
    Settings::settings_label = lv_label_create(Settings::settings_tile);
    lv_label_set_text(Settings::settings_label, "Settings page, change stations here");
    lv_obj_set_style_text_font(Settings::settings_label, &lv_font_montserrat_28, 0);
    lv_obj_set_align(Settings::settings_label, LV_ALIGN_TOP_MID);
    apply_tile_colors(Settings::settings_tile, Settings::settings_label, /*dark=*/false);

    station_options(Settings::settings_tile);
    transport_options(Settings::settings_tile);
    buttons_create(Settings::settings_tile);

    // Create a label that shows WiFi status
    if (WiFi.status() == WL_CONNECTED) 
    {
        this->wifi_status = " Connected";
    }
    else 
    {
        this->wifi_status = " Disconnected";
    }
    std::string wifi_status_string = "WiFi status:" + this->wifi_status;
    Settings::wifi_status_label = lv_label_create(Settings::settings_tile);
    lv_label_set_text(Settings::wifi_status_label, wifi_status_string.c_str());
    lv_obj_set_style_text_font(Settings::wifi_status_label, &lv_font_montserrat_28, 0);
    lv_obj_set_align(Settings::wifi_status_label, LV_ALIGN_BOTTOM_LEFT);
}

void Settings::update_WiFi_status()
{
    if (WiFi.status() == WL_CONNECTED && this->wifi_status != " Connected") 
    {
        this->wifi_status = " Connected";
    }
    else if(WiFi.status() != WL_CONNECTED && this->wifi_status != " Disconnected")
    {
        this->wifi_status = " Disconnected";
    }
    std::string wifi_status_string = "WiFi status:" + this->wifi_status;
    lv_label_set_text(Settings::wifi_status_label, wifi_status_string.c_str());
}


// Creates a dropdown option for the stations to chose between.
void Settings::station_options(lv_obj_t* parent)
{
    //create a dropdown with station options
    Settings::station_dropdown = lv_dropdown_create(parent);
    lv_obj_align_to( Settings::station_dropdown, Settings::settings_label, LV_ALIGN_CENTER, -120, 60);
    lv_obj_set_size(Settings::station_dropdown, 350, 60);
    set_station_dropdown();

    lv_obj_add_event_cb(Settings::station_dropdown, Settings::on_station_value_change, LV_EVENT_VALUE_CHANGED, this);
}


/*
Creates a dropdown option for the modes of transportation to chose between based
on the chosen station.
*/
void Settings::transport_options(lv_obj_t* parent)
{
    //create a dropdown with transport options
    Settings::transport_dropdown = lv_dropdown_create(parent);
    lv_obj_align_to( Settings::transport_dropdown, Settings::station_dropdown, LV_ALIGN_CENTER, -110, 60);
    lv_obj_set_size(Settings::transport_dropdown, 350, 60);
    set_transport_dropdown();

    //Changes the displayed selected option in the dropdown.
    lv_obj_add_event_cb(Settings::transport_dropdown, on_transport_value_change, LV_EVENT_VALUE_CHANGED, this);
}

void Settings::buttons_create(lv_obj_t *parent)
{
    //Creates a clickable confirmed button to change departure station
    Settings::confirm_btn = lv_btn_create(parent);
    lv_obj_t* btn_label;
    btn_label = lv_label_create(confirm_btn);
    lv_label_set_text(btn_label, "Select");
    lv_obj_center(btn_label);
    lv_obj_align_to(Settings::confirm_btn, Settings::transport_dropdown, LV_ALIGN_CENTER, -50, 60);
    lv_obj_set_size(Settings::confirm_btn, 150, 50);
    lv_obj_add_flag(Settings::confirm_btn, LV_OBJ_FLAG_CLICKABLE);

    Settings::save_btn = lv_btn_create(parent);
    lv_obj_t* save_btn_label;
    save_btn_label = lv_label_create(save_btn);
    lv_label_set_text(save_btn_label, "Save Settings");
    lv_obj_center(save_btn_label);
    lv_obj_align_to(Settings::save_btn, Settings::confirm_btn, LV_ALIGN_CENTER, 0, 60);
    lv_obj_set_size(Settings::save_btn, 150, 50);
    lv_obj_add_flag(Settings::save_btn, LV_OBJ_FLAG_CLICKABLE);

    Settings::load_btn = lv_btn_create(parent);
    lv_obj_t* load_btn_label;
    load_btn_label = lv_label_create(load_btn);
    lv_label_set_text(load_btn_label, "Load Settings");
    lv_obj_center(load_btn_label);
    lv_obj_align_to(Settings::load_btn, Settings::confirm_btn, LV_ALIGN_CENTER, 0, 120);
    lv_obj_set_size(Settings::load_btn, 150, 50);
    lv_obj_add_flag(Settings::load_btn, LV_OBJ_FLAG_CLICKABLE);
}

void Settings::on_station_value_change(lv_event_t* event)
{
    Settings* self = static_cast<Settings*>(lv_event_get_user_data(event));

    lv_dropdown_set_text(Settings::station_dropdown, NULL);
    self->set_transport_dropdown();
}

void Settings::on_transport_value_change(lv_event_t* event)
{
    lv_dropdown_set_text(Settings::transport_dropdown, NULL);
}

void Settings::set_station_dropdown()
{
    lv_dropdown_set_options(Settings::station_dropdown, station_names.c_str());
}

void Settings::set_transport_dropdown()
{
    get_selected();
    transport_names = station_id_table[selected_station_option].begin()->second;
    lv_dropdown_set_options(Settings::transport_dropdown, transport_names.c_str());
}

lv_obj_t* Settings::get_confirmed_button()
{
    return Settings::confirm_btn;
}

lv_obj_t* Settings::get_save_button()
{
    return Settings::save_btn;
}

lv_obj_t* Settings::get_load_button()
{
    return Settings::load_btn;
}

void Settings::set_station_dropdown_option(const String &new_station)
{
    int32_t option_index = lv_dropdown_get_option_index(Settings::station_dropdown, new_station.c_str());
    
    if (option_index == -1)
    {
        Serial.printf("Error: Option not found in station dropdown\n");
        return;
    }

    lv_dropdown_set_selected(Settings::station_dropdown, option_index);
}

bool Settings::set_transport_dropdown_option(const String &new_transport)
{
    int32_t option_index = lv_dropdown_get_option_index(Settings::transport_dropdown, new_transport.c_str());
    
    if (option_index == -1)
    {
        Serial.printf("Error: Option not found in transport dropdown\n");
        return false;
    }

    lv_dropdown_set_selected(Settings::transport_dropdown, option_index);
    return true;
}

void Settings::set_station_text(const String &saved_station)
{
    lv_dropdown_set_text(Settings::station_dropdown, saved_station.c_str());
}

void Settings::set_transport_text(const String& saved_transport)
{
    lv_dropdown_set_text(Settings::transport_dropdown, saved_transport.c_str());
}

void Settings::get_selected()
{
    // Create buffers
    char* station_buffer = new char[buff_size];
    char* transport_buffer = new char[buff_size];
    
    // Set buffers to current settings
    lv_dropdown_get_selected_str(Settings::station_dropdown, station_buffer, buff_size);
    lv_dropdown_get_selected_str(Settings::transport_dropdown, transport_buffer, buff_size);

    // Get length of station name
    int station_len = 0;
    for (station_len = 0; station_len < buff_size; station_len++)
    {
        if (station_buffer[station_len] == '\0')
            break;
    }

    // Get length of transport name
    int transport_len = 0;
    for (transport_len = 0; transport_len < buff_size; transport_len++)
    {
        if (transport_buffer[transport_len] == '\0')
            break;
    }

    // Set settings
    Settings::selected_station_option = String(station_buffer, station_len);
    Settings::selected_transport_option = String(transport_buffer, transport_len);
    Settings::selected_station_id = station_id_table[selected_station_option].begin()->first;

    delete[] station_buffer;
    delete[] transport_buffer;
}

const String Settings::get_station()
{
    get_selected();
    return selected_station_option;
}

const String Settings::get_transport()
{
    get_selected();
    return selected_transport_option;
}

void Settings::set_station(const String &new_station)
{
    set_station_dropdown_option(new_station);
    selected_station_option = new_station;
    set_transport_dropdown();
}

void Settings::set_transport(const String &new_transport)
{
    if (set_transport_dropdown_option(new_transport))
        selected_transport_option = new_transport;
}

const String Settings::get_station_id()
{
    return selected_station_id;
}
