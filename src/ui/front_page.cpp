#include "front_page.h"


front_page::front_page()
{

}

front_page::~front_page()
{

}

void front_page::create()
{
    // Adds a tile in tileview and also adds a lable, the "class::" is used to
    // refer to static member variable. "This->" is used to refer Non-static
    front_page::front_tile = lv_tileview_add_tile(ui::tileview, 0, 0, LV_DIR_HOR);
    front_page::front_label = lv_label_create(front_page::front_tile);
    lv_label_set_text(front_page::front_label, "Public Transport Information\n and\n Interaction on ESP32\n Group 2 Version 1.1\n Napatpong Chokwatthananon\n Li Holma, Tim Säterby\n Adam Gunnarsson, Kimi Grubisic");
    lv_obj_set_style_text_font(front_page::front_label, &lv_font_montserrat_28, 0);
    lv_obj_center(front_page::front_label);
    apply_tile_colors(front_page::front_tile , front_label, /*dark=*/false);
}