#pragma once
#include "UI.h"
#include <HTTPClient.h>

class settings : public ui
{
private:
    static lv_obj_t* settings_tile;
    static lv_obj_t* settings_label;
    static constexpr uint32_t buff_size = 64;
<<<<<<< HEAD
    inline static lv_obj_t* settings_dropdown = nullptr;
    inline static char selected_option[buff_size]{};
=======
    char* selected_option{};
    lv_obj_t* settings_dropdown{};

>>>>>>> parent of 354952c (Tried out the ui heritage)
    void station_options(lv_obj_t* parent);
    void on_confirm_btn_clicked(lv_event_t* event);


public:
    settings();
    ~settings();
    void get_selected();
    void create();
};

