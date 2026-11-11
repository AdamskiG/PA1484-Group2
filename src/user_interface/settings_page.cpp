#include "settings_page.h"
#include "../settings/controller.h"

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

    // Create a label that shows WiFi status
    // MIGHT work based on the same solution used in project.ino.
    if (WiFi.status() == WL_CONNECTED) 
    {
        this->wifi_status = "CONNECTED";
    }
    else 
    {
        this->wifi_status = "DISCONNECTED";
    }
    std::string wifi_status_string = "WiFi status:" + this->wifi_status;
    Settings::WiFi_status_label = lv_label_create(Settings::settings_tile);
    lv_label_set_text(Settings::WiFi_status_label, wifi_status_string.c_str());
    lv_obj_set_style_text_font(Settings::WiFi_status_label, &lv_font_montserrat_28, 0);
    lv_obj_set_align(Settings::WiFi_status_label, LV_ALIGN_BOTTOM_LEFT);
}

void Settings::update()
{
    if (WiFi.status() == WL_CONNECTED && this->wifi_status != "CONNECTED") 
    {
        this->wifi_status = "CONNECTED";
    }
    else if(WiFi.status() != WL_CONNECTED && this->wifi_status != "DISCONNECTED")
    {
        this->wifi_status = "DISCONNECTED";
    }
    std::string wifi_status_string = "WiFi status:" + this->wifi_status;
    lv_label_set_text(Settings::WiFi_status_label, wifi_status_string.c_str());
}


// Creates a dropdown option for the stations to chose between.
void Settings::station_options(lv_obj_t* parent)
{
    //create a dropdown with station options
    Settings::settings_dropdown = lv_dropdown_create(parent);
    lv_obj_set_align(Settings::settings_dropdown, LV_ALIGN_CENTER);
    lv_obj_set_size(Settings::settings_dropdown, 350, 60);
    lv_dropdown_set_options(Settings::settings_dropdown, this->create_station_dropdown_string());

    //Changes the displayed selected option in the dropdown.
    lv_obj_add_event_cb(Settings::settings_dropdown, on_dropdown_value_change, LV_EVENT_VALUE_CHANGED, NULL);

    
    //This should be unused if the selected station triggers the event on change properly.
    //lv_obj_add_event_cb(Settings::confirm_btn, on_confirm_btn_clicked, LV_EVENT_CLICKED, NULL);


    lv_obj_add_event_cb(Settings::settings_dropdown, get_selected, LV_EVENT_VALUE_CHANGED, NULL);
    // lv_dropdown_get_selected()
}



/*
Creates a dropdown option for the modes of transportation to chose between based
on the chosen station.
*/
void Settings::transport_options(lv_obj_t* parent)
{
    //create a dropdown with transport options
    Settings::transport_dropdown = lv_dropdown_create(parent);
    lv_obj_set_align(Settings::transport_dropdown, LV_ALIGN_CENTER);
    lv_obj_set_size(Settings::transport_dropdown, 350, 60);
    lv_dropdown_set_options(Settings::transport_dropdown, create_transport_dropdown_string());

    //Changes the displayed selected option in the dropdown.
    lv_obj_add_event_cb(Settings::transport_dropdown, on_dropdown_value_change_transport, LV_EVENT_VALUE_CHANGED, NULL);

    
    //Creates a clickable confirmed button to change departure station
    Settings::confirm_btn = lv_btn_create(parent);
    lv_obj_t * btn_label;
    btn_label = lv_label_create(confirm_btn);
    lv_label_set_text(btn_label, "Select");
    lv_obj_center(btn_label);
    lv_obj_align_to(Settings::confirm_btn, Settings::transport_dropdown, LV_ALIGN_CENTER, -50, 60);
    lv_obj_set_size(Settings::confirm_btn, 150, 50);
    lv_obj_add_flag(Settings::confirm_btn, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(Settings::confirm_btn, on_confirm_btn_clicked, LV_EVENT_CLICKED, NULL);
    // lv_dropdown_get_selected()
}



void Settings::on_confirm_btn_clicked(lv_event_t* event) 
{
    LV_UNUSED(event);
    lv_dropdown_get_selected_str(Settings::transport_dropdown, Settings::selected_transport_option, buff_size); 
}

void Settings::on_save_btn_clicked(lv_event_t *event)
{
    controller->save_settings(selected_station_option, selected_transport_option, buff_size);
}

void Settings::on_load_btn_clicked(lv_event_t *event)
{
    controller->load_settings(selected_station_option, selected_transport_option, buff_size);
}

void Settings::on_dropdown_value_change(lv_event_t* event)
{
    lv_dropdown_set_text(Settings::settings_dropdown, NULL);
}

void Settings::on_dropdown_value_change_transport(lv_event_t* event)
{
    lv_dropdown_set_text(Settings::transport_dropdown, NULL);
}


void Settings::get_selected(lv_event_t* event)
{
    lv_dropdown_get_selected_str(Settings::settings_dropdown, Settings::selected_station_option, buff_size); 
}


const char* Settings::create_station_dropdown_string()
{
    // loop through all station names and add them to a string
    for(auto& name_and_info: station_id_table)
    {
        this->station_names += name_and_info.first + "\n";
    }
    // convert string to a constant char pointer and return
    return station_names.c_str();
}


const char* Settings::create_transport_dropdown_string()
{
        
    this->transport_names = station_id_table.at(selected_station_option).transport_types;

    // convert string to a constant char pointer and return
    return transport_names.c_str();
}

const char *Settings::get_station()
{
    return selected_station_option;
}

const char *Settings::get_transport()
{
    return selected_transport_option;
}
