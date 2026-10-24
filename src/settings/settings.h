#pragma once
#include "ui.h"
#include <HTTPClient.h>

class settings : public ui
{
private:
    inline static lv_obj_t* settings_tile = nullptr;
    inline static lv_obj_t* settings_label = nullptr;
    static constexpr uint32_t buff_size = 64;
    inline static lv_obj_t* settings_dropdown = nullptr;
    void station_options(lv_obj_t* parent);
    // void on_confirm_btn_clicked(lv_event_t* event);

protected:
    inline static char selected_option[buff_size]{};

public:
    settings();
    ~settings();
    void get_selected();
    void create();
};

