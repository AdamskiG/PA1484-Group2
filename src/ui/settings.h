#pragma once
#include "ui.h"
#include "departure.h"
#include "../settings/api.h"
#include <HTTPClient.h>

class Settings : protected ui
{
private:
    inline static lv_obj_t* settings_tile = nullptr;
    inline static lv_obj_t* settings_label = nullptr;
    inline static lv_obj_t* settings_dropdown = nullptr;
    inline static lv_obj_t* confirm_btn = nullptr;

    static constexpr uint32_t buff_size = 64;
    inline static char selected_option[buff_size]{};
    
    void station_options(lv_obj_t* parent);
    void on_confirm_btn_clicked(lv_event_t* event);
    // void on_confirm_btn_clicked(lv_event_t* event);

public:
    Settings();
    ~Settings();
    void get_selected();
    void create();
};

