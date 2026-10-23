#pragma once
#include "lvgl.h"
#include <HTTPClient.h>

class Settings 
{
public:
    Settings();
    ~Settings();
    static void draw_settings_ui(lv_obj_t* parent);
    void station_options(lv_obj_t* parent);
    static void apply_tile_colors(lv_obj_t* tile, lv_obj_t* label, bool dark);
    void get_selected();
private:
    void on_confirm_btn_clicked(lv_event_t* event);
    static constexpr uint32_t buff_size = 64;
    char* selected_option{};
    lv_obj_t* settings_dropdown{};
};

