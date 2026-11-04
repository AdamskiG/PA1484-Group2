#include "front_page.h"


Front_page::Front_page()
{

}

Front_page::~Front_page()
{

}

void Front_page::create()
{
    // Adds a tile in tileview and also adds a lable, the "class::" is used to
    // refer to static member variable. "This->" is used to refer Non-static
    Front_page::front_tile = lv_tileview_add_tile(ui::tileview, 0, 0, LV_DIR_HOR);
    Front_page::front_label = lv_label_create(Front_page::front_tile);
    lv_label_set_text(Front_page::front_label, "Public Transport Information\n and\n Interaction on ESP32\n Group 2 Version 1.1\n Napatpong Chokwatthananon\n Li Holma, Tim Säterby\n Adam Gunnarsson, Kimi Grubisic");
    lv_obj_set_style_text_font(Front_page::front_label, &lv_font_montserrat_28, 0);
    lv_obj_center(Front_page::front_label);
    apply_tile_colors(Front_page::front_tile , front_label, /*dark=*/false);
}