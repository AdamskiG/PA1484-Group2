#include "journey_page.h"

Journey_Page::Journey_Page()
{

}

Journey_Page::~Journey_Page()
{

}

void Journey_Page::create()
{
    Journey_Page::front_tile = lv_tileview_add_tile(Ui::tileview, 3, 0, LV_DIR_HOR);
    Journey_Page::front_label = lv_label_create(Journey_Page::front_tile);
    lv_label_set_text(Journey_Page::front_label, "Journey Selection");
    lv_obj_set_style_text_font(Journey_Page::front_label, &lv_font_montserrat_28, 0);
    lv_obj_center(Journey_Page::front_label);
    apply_tile_colors(Journey_Page::front_tile , front_label, /*dark=*/false);
}