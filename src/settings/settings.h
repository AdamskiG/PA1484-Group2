#pragma once
#include "UI.h"
#include <HTTPClient.h>

class settings : public ui
{
private:
    static lv_obj_t* settings_tile;
    static lv_obj_t* settings_label;
    static constexpr uint32_t buff_size = 64;
    char* selected_option{};
    lv_obj_t* settings_dropdown{};

    void station_options(lv_obj_t* parent);
    void on_confirm_btn_clicked(lv_event_t* event);

public:
    settings();
    ~settings();
    void get_selected();
    void create();
};

