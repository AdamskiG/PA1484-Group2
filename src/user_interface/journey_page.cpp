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
}

// void Journey_Page::set_journey_dropdown()
// {
//     for(auto data : station_id_table)
//     {
//         station_names += data.first + "\n";
//     }
//     station_names.trim();
//     lv_dropdown_set_options(Settings::station_dropdown, station_names.c_str());
// }

void Journey_Page::set_destination_dropdown()
{

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
