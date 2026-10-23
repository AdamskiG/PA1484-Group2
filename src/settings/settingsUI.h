#pragma once
#include "lvgl.h"
#include "UI.h"
#include <HTTPClient.h>

class Settings : public UI
{
public:
    Settings();
    ~Settings();
    void draw_settings_ui(lv_obj_t* parent);
    void get_selected();
    void create();
private:
    void station_options(lv_obj_t* parent);
    void on_confirm_btn_clicked(lv_event_t* event);
    static constexpr uint32_t buff_size = 64;
    char* selected_option{};
    lv_obj_t* settings_dropdown{};
};

