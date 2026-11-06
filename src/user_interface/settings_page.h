#pragma once
#include "ui.h"
#include "settings/controller.h"
#include <HTTPClient.h>
#include <unordered_map>
#include <string>

class Settings : protected Ui
{
private:
    inline static lv_obj_t* settings_tile = nullptr;
    inline static lv_obj_t* settings_label = nullptr;
    inline static lv_obj_t* settings_dropdown = nullptr;
    inline static lv_obj_t* confirm_btn = nullptr;

    //Storing all the stations and their ID together with their transportation types
    std::unordered_map<std::string, int> station_id_table;

    static constexpr uint32_t buff_size = 64;
    inline static char selected_option[buff_size]{};
    
    void station_options(lv_obj_t* parent);
    static void on_confirm_btn_clicked(lv_event_t* event);
    static void on_dropdown_value_change(lv_event_t* event);
    static void get_selected();

    std::string station_names = "";

public:
    Settings();
    ~Settings();
    void create();
    const char* create_station_dropdown_string();
};

