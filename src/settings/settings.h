#pragma once
#include "UI.h"
#include <HTTPClient.h>

class settings : public ui
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
    settings();
    ~settings();
    void get_selected();
    void create();
};

