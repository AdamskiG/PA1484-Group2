#pragma once
#include "ui.h"
#include "settings/controller.h"
#include <HTTPClient.h>

class Settings : protected Ui
{
private:
    inline static lv_obj_t* settings_tile = nullptr;
    inline static lv_obj_t* settings_label = nullptr;
    inline static lv_obj_t* settings_dropdown = nullptr;
    inline static lv_obj_t* confirm_btn = nullptr;

    static constexpr uint32_t buff_size = 64;
    inline static char selected_option[buff_size]{};
    
    void station_options(lv_obj_t* parent);
    static void on_confirm_btn_clicked(lv_event_t* event);
    static void on_dropdown_value_change(lv_event_t* event);
    static void get_selected();

public:
    Settings();
    ~Settings();
    void create();
};

