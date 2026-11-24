#include "journey_page.h"

Journey_Page::Journey_Page()
{

}

Journey_Page::~Journey_Page()
{

}

void Journey_Page::create()
{
    Journey_Page::journey_tile = lv_tileview_add_tile(Ui::tileview, 3, 0, LV_DIR_HOR);
    Journey_Page::journey_label = lv_label_create(Journey_Page::journey_tile);
    lv_label_set_text(Journey_Page::journey_label, "Journey Selection");
    lv_obj_set_style_text_font(Journey_Page::journey_label, &lv_font_montserrat_28, 0);
    lv_obj_center(Journey_Page::journey_label);
    apply_tile_colors(Journey_Page::journey_tile ,journey_label, /*dark=*/false);

    this->create_orgin_dropdown(Journey_Page::journey_tile);
    create_destination_dropdown(Journey_Page::journey_tile);
    create_confirm_btn(Journey_Page::journey_tile);
    
}

void Journey_Page::get_selected()
{
    // Create buffers
    char* origin_buffer = new char[buff_size];
    char* destination_buffer = new char[buff_size];
    
    // Set buffers to current settings
    lv_dropdown_get_selected_str(Journey_Page::origin_dropdown, origin_buffer, buff_size);
    lv_dropdown_get_selected_str(Journey_Page::destination_dropdown, destination_buffer, buff_size);

    // Get length of station name
    int station_len = 0;
    for (station_len = 0; station_len < buff_size; station_len++)
    {
        if (origin_buffer[station_len] == '\0')
            break;
    }

    // Get length of transport name
    int destination_len = 0;
    for (destination_len = 0; destination_len < buff_size; destination_len++)
    {
        if (destination_buffer[destination_len] == '\0')
            break;
    }

    // Set settings
    Journey_Page::selected_origin_option = String(origin_buffer, station_len);
    Journey_Page::selected_destination_option = String(destination_buffer, destination_len);
    Journey_Page::selected_station_id = station_id_table[selected_destination_option].begin()->first;

    delete[] origin_buffer;
    delete[] destination_buffer;
}

void Journey_Page::set_origin_dropdown()
{
    lv_dropdown_set_options(Journey_Page::origin_dropdown, station_names.c_str());
}

void Journey_Page::set_destination_dropdown()
{
    lv_dropdown_set_options(Journey_Page::destination_dropdown, station_names.c_str());
}

// Creates a dropdown option for the stations to chose between.
void Journey_Page::create_orgin_dropdown(lv_obj_t* parent)
{
    //create a dropdown with station options
    Journey_Page::origin_dropdown = lv_dropdown_create(parent);
    lv_obj_set_size(Journey_Page::origin_dropdown, 350, 60);
    lv_obj_align_to(Journey_Page::origin_dropdown, Journey_Page::journey_label, LV_ALIGN_CENTER, -120, 60);
    lv_obj_set_size(Journey_Page::origin_dropdown, 350, 60);
    set_origin_dropdown();

}

void Journey_Page::create_destination_dropdown(lv_obj_t* parent)
{
    //create a dropdown with transport options
    Journey_Page::destination_dropdown = lv_dropdown_create(parent);
    lv_obj_align_to(Journey_Page::destination_dropdown, Journey_Page::origin_dropdown, LV_ALIGN_CENTER, -115, 60);
    lv_obj_set_size(Journey_Page::destination_dropdown, 350, 60);
    set_destination_dropdown();

    //Changes the displayed selected option in the dropdown.
    // lv_obj_add_event_cb(Journey_Page::transport_dropdown, on_transport_value_change, LV_EVENT_VALUE_CHANGED, this);
}

void Journey_Page::create_confirm_btn(lv_obj_t* parent)
{
    Journey_Page::journey_confirm_btn = lv_btn_create(parent);
    lv_obj_t* btn_label;
    btn_label = lv_label_create(journey_confirm_btn);
    lv_label_set_text(btn_label, "Select");
    lv_obj_center(btn_label);
    lv_obj_align_to(Journey_Page::journey_confirm_btn, Journey_Page::destination_dropdown, LV_ALIGN_CENTER, -50, 60);
    lv_obj_set_size(Journey_Page::journey_confirm_btn, 150, 50);
    lv_obj_add_flag(Journey_Page::journey_confirm_btn, LV_OBJ_FLAG_CLICKABLE);
}
