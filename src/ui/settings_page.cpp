#include "settings_page.h"
#include "../settings/controller.h"
#include <fstream>

Settings::Settings()
{

}

Settings::~Settings()
{

}

void Settings::create()
{
    // Adds the settings tileview
    Settings::settings_tile = lv_tileview_add_tile(ui::tileview, 2, 0, LV_DIR_HOR);

    // Create a label for the settings UI
    Settings::settings_label = lv_label_create(Settings::settings_tile);
    lv_label_set_text(Settings::settings_label, "Settings page, change stations here");
    lv_obj_set_style_text_font(Settings::settings_label, &lv_font_montserrat_28, 0);
    lv_obj_set_align(Settings::settings_label, LV_ALIGN_TOP_MID);
    apply_tile_colors(Settings::settings_tile, Settings::settings_label, /*dark=*/false);
    station_options(Settings::settings_tile);
}

    // Creates a dropdown option 
void Settings::station_options(lv_obj_t* parent)
{
    //create a dropdown with station options
    Settings::settings_dropdown = lv_dropdown_create(parent);
    lv_obj_set_align(Settings::settings_dropdown, LV_ALIGN_CENTER);
    lv_obj_set_size(Settings::settings_dropdown, 350, 60);
    lv_dropdown_set_options(Settings::settings_dropdown, "Campus Gräsvik\nKarlskrona Centralstation\nKvarngatan");
    lv_obj_add_event_cb(Settings::settings_dropdown, on_dropdown_value_change,)
    
    //Creates a clickable confirmed button to change departure station
    Settings::confirm_btn = lv_btn_create(parent);
    lv_obj_t * btn_label;
    btn_label = lv_label_create(confirm_btn);
    lv_label_set_text(btn_label, "Select");
    lv_obj_center(btn_label);
    // lv_label_set_text(confirm_btn, "Välj Station");
    lv_obj_align_to(Settings::confirm_btn, Settings::settings_dropdown, LV_ALIGN_CENTER, -50, 60);
    lv_obj_set_size(Settings::confirm_btn, 150, 50);
    lv_obj_add_flag(Settings::confirm_btn, LV_OBJ_FLAG_CLICKABLE);
    // lv_obj_add_event_cb(settings::confirm_btn, on_confirm_btn_clicked, LV_EVENT_CLICKED, NULL);
    // lv_dropdown_get_selected()
}

void Settings::on_confirm_btn_clicked(lv_event_t* event) 
{
    LV_UNUSED(event);
    get_selected();
    std::ofstream file("last_selected.txt", std::ios::in);
    file << Settings::selected_option;
    file.close();
    
}

void Settings::on_dropdown_value_change(lv_event_t* event)
{
    lv_dropdown_set_
}

void Settings::get_selected()
{
    lv_dropdown_get_selected_str(Settings::settings_dropdown, Settings::selected_option, buff_size); 
}