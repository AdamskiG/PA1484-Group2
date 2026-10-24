#include "settings.h"

settings::settings()
{
}

settings::~settings()
{

}

void settings::create()
{
    // Adds the settings tileview
    this->settings_tile = lv_tileview_add_tile(this->tileview, 2, 0, LV_DIR_HOR);

    // Create a label for the settings UI
    this->settings_label = lv_label_create(this->settings_tile);
    lv_label_set_text(this->settings_label, "Settings page, change stations here");
    lv_obj_set_style_text_font(this->settings_label, &lv_font_montserrat_28, 0);
    lv_obj_set_align(this->settings_label, LV_ALIGN_TOP_MID);
    apply_tile_colors(this->settings_tile, settings_label, /*dark=*/false);
    station_options(this->settings_tile);
}

void settings::station_options(lv_obj_t* parent)
{
    //create a dropdown with station options
    this->settings_dropdown = lv_dropdown_create(parent);
    lv_obj_set_align(this->settings_dropdown, LV_ALIGN_CENTER);
    lv_obj_set_size(this->settings_dropdown, 300, 60);
    lv_dropdown_set_options(this->settings_dropdown, "Campus Gräsvik\nKarlskrona Centralstation\nKvarngatan");
    
    //Creates a clickable confirmed button to change departure station
    lv_obj_t* confirm_btn = lv_btn_create(parent);
    // lv_label_set_text(confirm_btn, "Välj Station");
    lv_obj_align_to(confirm_btn, this->settings_dropdown, LV_ALIGN_CENTER, -50, 60);
    lv_obj_set_size(confirm_btn, 150, 50);
    lv_obj_add_flag(confirm_btn, LV_OBJ_FLAG_CLICKABLE);
    // lv_obj_add_event_cb(confirm_btn, on_confirm_btn_clicked, LV_EVENT_CLICKED, NULL);
    // lv_dropdown_get_selected()
}

// void settings::on_confirm_btn_clicked(lv_event_t* event) 
// {
//     LV_UNUSED(event);
//     get_selected();
// }

void settings::get_selected()
{
    lv_dropdown_get_selected_str(this->settings_dropdown, this->selected_option, buff_size); 
}