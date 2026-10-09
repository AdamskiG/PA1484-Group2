#pragma once
#include "lvgl.h"
#include <HTTPClient.h>

class Settings 
{
public:
    Settings();
    static void draw_settings_ui(lv_obj_t* parent);
    static void station_options(lv_obj_t* parent);
private:
    static void on_confirm_btn_clicked(lv_event_t* event);
    static void apply_tile_colors(lv_obj_t* tile, lv_obj_t* label, bool dark);
};

