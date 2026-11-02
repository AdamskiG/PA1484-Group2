#include "settings.h"
#include "departure.h"
#include "../settings/api.h"

settings::settings()
{

}

settings::~settings()
{

}

void settings::create()
{
    // Adds the settings tileview
    settings::settings_tile = lv_tileview_add_tile(ui::tileview, 2, 0, LV_DIR_HOR);

    // Create a label for the settings UI
    settings::settings_label = lv_label_create(settings::settings_tile);
    lv_label_set_text(settings::settings_label, "Settings page, change stations here");
    lv_obj_set_style_text_font(settings::settings_label, &lv_font_montserrat_28, 0);
    lv_obj_set_align(settings::settings_label, LV_ALIGN_TOP_MID);
    apply_tile_colors(settings::settings_tile, settings::settings_label, /*dark=*/false);
    station_options(settings::settings_tile);
}

    // Creates a dropdown option 
void settings::station_options(lv_obj_t* parent)
{
    //create a dropdown with station options
    settings::settings_dropdown = lv_dropdown_create(parent);
    lv_obj_set_align(settings::settings_dropdown, LV_ALIGN_CENTER);
    lv_obj_set_size(settings::settings_dropdown, 350, 60);
    lv_dropdown_set_options(settings::settings_dropdown, "Campus Gräsvik\nKarlskrona Centralstation\nKvarngatan");
    
    //Creates a clickable confirmed button to change departure station
    settings::confirm_btn = lv_btn_create(parent);
    lv_obj_t * btn_label;
    btn_label = lv_label_create(confirm_btn);
    lv_label_set_text(btn_label, "Select");
    lv_obj_center(btn_label);
    // lv_label_set_text(confirm_btn, "Välj Station");
    lv_obj_align_to(settings::confirm_btn, settings::settings_dropdown, LV_ALIGN_CENTER, -50, 60);
    lv_obj_set_size(settings::confirm_btn, 150, 50);
    lv_obj_add_flag(settings::confirm_btn, LV_OBJ_FLAG_CLICKABLE);
    // lv_obj_add_event_cb(settings::confirm_btn, on_confirm_btn_clicked, LV_EVENT_CLICKED, NULL);
    // lv_dropdown_get_selected()
}

void settings::on_confirm_btn_clicked(lv_event_t* event) 
{
    LV_UNUSED(event);
    get_selected();
    // api::call_request(settings::selected_option);
    // departure::set_station(settings::selected_option);
    

}

void settings::get_selected()
{
    lv_dropdown_get_selected_str(settings::settings_dropdown, settings::selected_option, buff_size); 
}