#include "ui.h"

ui::ui()
{
    if(!tileview)
    {
        ui::tileview = lv_tileview_create(lv_scr_act());
        lv_obj_set_size(this->tileview, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
        lv_obj_set_scrollbar_mode(this->tileview, LV_SCROLLBAR_MODE_OFF);
    }
}

ui::~ui()
{

}

void ui::create()
{
  
}

void ui::apply_tile_colors(lv_obj_t* tile, lv_obj_t* label, bool dark)
{
  // Colours to Background
    lv_obj_set_style_bg_opa(tile, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(tile, dark ? lv_color_black() : lv_color_white(), 0);

  // colours to Text
    lv_obj_set_style_text_color(label, dark ? lv_color_white() : lv_color_black(), 0);
}