#include "journey_page.h"

Journey_Page::Journey_Page()
{

}

Journey_Page::~Journey_Page()
{

}

void Journey_Page::create()
{
<<<<<<< Updated upstream
    Journey_Page::journey_tile = lv_tileview_add_tile(Ui::tileview, 3, 0, LV_DIR_HOR);
    Journey_Page::journey_label = lv_label_create(Journey_Page::journey_tile);
    lv_label_set_text(Journey_Page::journey_label, "Journey Selection");
    lv_obj_set_style_text_font(Journey_Page::journey_label, &lv_font_montserrat_28, 0);
    lv_obj_set_align(Journey_Page::journey_label, LV_ALIGN_TOP_MID);
    apply_tile_colors(Journey_Page::journey_tile, journey_label, /*dark=*/false);
=======
    Journey_Page::front_tile = lv_tileview_add_tile(Ui::tileview, 3, 0, LV_DIR_HOR);
    Journey_Page::front_label = lv_label_create(Journey_Page::front_tile);
    lv_label_set_text(Journey_Page::front_label, "Journey Selection");
    lv_obj_set_style_text_font(Journey_Page::front_label, &font_scandi_28, 0);
    lv_obj_center(Journey_Page::front_label);
    apply_tile_colors(Journey_Page::front_tile , front_label, /*dark=*/false);
>>>>>>> Stashed changes

    this->create_orgin_dropdown(Journey_Page::journey_tile);
    create_destination_dropdown(Journey_Page::journey_tile);
    create_time_dropdown(Journey_Page::journey_tile);
    create_confirm_btn(Journey_Page::journey_tile);
    
}

void Journey_Page::set_origin_dropdown()
{
    lv_dropdown_set_options(Journey_Page::origin_dropdown, station_names.c_str());
}

void Journey_Page::set_destination_dropdown()
{
    lv_dropdown_set_options(Journey_Page::destination_dropdown, station_names.c_str());
}

void Journey_Page::set_time_dropdown()
{
    std::stringstream hour_string;
    for(int i = 0; i < 24; i++){
        if(i < 10)
        {
            hour_string << std::setw(2) << std::setfill('0') << i << "\n";
        }
        else{
            hour_string << i << "\n";
        }
    }

    std::string hours = hour_string.str();
    hours.pop_back();
    lv_dropdown_set_options(Journey_Page::hour_dropdown, hours.c_str());

    std::stringstream minutes_string;
    for(int i = 0; i < 60; i++){
        if(i < 10)
        {
            minutes_string << std::setw(2) << std::setfill('0') << i << "\n";
        }
        else{
            minutes_string << i << "\n";
        }
    }
    std::string minutes = minutes_string.str();
    minutes.pop_back();
    lv_dropdown_set_options(Journey_Page::minutes_dropdown, minutes.c_str());
}

// Creates a dropdown option for the stations to chose between.
void Journey_Page::create_orgin_dropdown(lv_obj_t* parent)
{
    //create a dropdown with station options
    Journey_Page::origin_dropdown = lv_dropdown_create(parent);
    lv_obj_t* origin_label = lv_label_create(parent);
    lv_obj_set_size(Journey_Page::origin_dropdown, 350, 60);
    lv_obj_align_to(origin_label, Journey_Page::journey_label, LV_ALIGN_CENTER, -150, 40);
    lv_obj_align_to(Journey_Page::origin_dropdown, origin_label, LV_ALIGN_CENTER, 150, 50);
    lv_label_set_text(origin_label, "From:");
    set_origin_dropdown();
}

void Journey_Page::create_destination_dropdown(lv_obj_t* parent)
{
    //create a dropdown with transport options
    Journey_Page::destination_dropdown = lv_dropdown_create(parent);
    lv_obj_t* destination_label = lv_label_create(parent);
    lv_obj_align_to(destination_label, Journey_Page::origin_dropdown, LV_ALIGN_CENTER, -150, 40);
    lv_label_set_text(destination_label, "To:");
    lv_obj_align_to(Journey_Page::destination_dropdown, destination_label, LV_ALIGN_CENTER, 45, 40);
    lv_obj_set_size(Journey_Page::destination_dropdown, 350, 60);
    set_destination_dropdown();
}

void Journey_Page::create_time_dropdown(lv_obj_t* parent)
{
    Journey_Page::hour_dropdown = lv_dropdown_create(parent);
    Journey_Page::minutes_dropdown = lv_dropdown_create(parent);
    lv_obj_t* time_label = lv_label_create(parent);
    lv_obj_t* time_dot = lv_label_create(parent);
    lv_obj_set_size(Journey_Page::hour_dropdown, 100, 60);
    lv_obj_set_size(Journey_Page::minutes_dropdown, 100, 60);
    lv_obj_align_to(time_label, Journey_Page::destination_dropdown, LV_ALIGN_CENTER, -40, 40);
    lv_obj_align_to(Journey_Page::hour_dropdown, time_label, LV_ALIGN_CENTER, -30, 50);
    lv_obj_align_to(time_dot, Journey_Page::hour_dropdown, LV_ALIGN_RIGHT_MID, 60, 0);
    lv_obj_align_to(Journey_Page::minutes_dropdown, time_dot, LV_ALIGN_LEFT_MID, 20, 0);
    lv_label_set_text(time_label, "Arrival Time:");
    lv_label_set_text(time_dot, " : ");
    set_time_dropdown();
}

void Journey_Page::create_confirm_btn(lv_obj_t* parent)
{
    Journey_Page::journey_confirm_btn = lv_btn_create(parent);
    lv_obj_t* btn_label;
    btn_label = lv_label_create(journey_confirm_btn);
    lv_label_set_text(btn_label, "Select");
    lv_obj_center(btn_label);
    lv_obj_align_to(Journey_Page::journey_confirm_btn, Journey_Page::hour_dropdown, LV_ALIGN_CENTER, 40, 60);
    lv_obj_set_size(Journey_Page::journey_confirm_btn, 150, 50);
    lv_obj_add_flag(Journey_Page::journey_confirm_btn, LV_OBJ_FLAG_CLICKABLE);
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
    Journey_Page::selected_origin_id = station_id_table[selected_origin_option].begin()->first;
    Journey_Page::selected_destination_id = station_id_table[selected_destination_option].begin()->first;

    delete[] origin_buffer;
    delete[] destination_buffer;
}

String Journey_Page::get_time()
{
    char* hour_buffer = new char[buff_size];
    char* minutes_buffer = new char[buff_size];
    lv_dropdown_get_selected_str(Journey_Page::hour_dropdown, hour_buffer, buff_size);
    lv_dropdown_get_selected_str(Journey_Page::destination_dropdown, minutes_buffer, buff_size);
    String hours = String(hour_buffer);
    String minutes = String(minutes_buffer);
    this->time = hours + ":" + minutes;
    return this->time;
}

String Journey_Page::get_origin_station()
{
    return selected_origin_id;
}

String Journey_Page::get_destination_station()
{
    return selected_destination_id;
}
