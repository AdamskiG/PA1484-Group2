#include "departure_page.h"

void Departure::create()
{
    Departure::departure_tile = lv_tileview_add_tile(Ui::tileview, 1, 0, LV_DIR_HOR);
    Departure::departure_table = lv_table_create(Departure::departure_tile);
    Departure::departure_label = lv_label_create(Departure::departure_tile);
    lv_label_set_text(Departure::departure_label, "Settings page, change stations here");
    lv_obj_set_style_text_font(Departure::departure_label, &lv_font_montserrat_28, 0);
    lv_obj_set_align(Departure::departure_label, LV_ALIGN_TOP_MID);
    apply_tile_colors(Departure::departure_tile, Departure::departure_label, /*dark=*/false);
}

void Departure::show_departure(Departure_Data_Holder data)
{
    int colums = 1;
    lv_table_set_cell_value(Daparture::departure_table, 0, 0, "Departure Time");
    
    for(Departure_Data* data : data.data)
    {
    lv_table_set_cell_value(Departure::departure_table, 0, colums, data->departure_time.c_str());
    colums++;
    }
}