#include "departure_page.h"

Departure::Departure()
{

}

Departure::~Departure()
{
    
}

void Departure::create()
{
    Departure::departure_tile = lv_tileview_add_tile(Ui::tileview, 1, 0, LV_DIR_HOR);
    Departure::departure_table = lv_table_create(Departure::departure_tile);
    Departure::departure_label = lv_label_create(Departure::departure_tile);
    lv_label_set_text(Departure::departure_label, "Departures");
    lv_obj_set_style_text_font(Departure::departure_label, &lv_font_montserrat_28, 0);
    lv_obj_set_align(Departure::departure_label, LV_ALIGN_TOP_MID);
    apply_tile_colors(Departure::departure_tile, Departure::departure_label, /*dark=*/false);
}

void Departure::show_departure(Departure_Data_Holder data)
{
    Departure::station_text += data.station;
    String departure_text = data.vehicle_filter + " Line Nr: ";
    lv_table_set_cell_value(Departure::departure_table, 0, 0, station_text.c_str());
    lv_table_set_cell_value(Departure::departure_table, 0, 1, departure_text.c_str());
    lv_table_set_cell_value(Departure::departure_table, 0, 2, "Mot: ");

    int colums = 1;
    for(Departure_Data* departure_data : data.data)
    {
        lv_table_set_cell_value(Departure::departure_table, colums, 0, departure_data->departure_time.c_str());
        lv_table_set_cell_value(Departure::departure_table, colums, 1, departure_data->vehicle_number.c_str());
        lv_table_set_cell_value(Departure::departure_table, colums, 2, departure_data->destination.c_str());
        colums++;
    }
}