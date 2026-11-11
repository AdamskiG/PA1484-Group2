#pragma once
#include "ui.h"
#include "settings/controller.h"
#include "settings/api.h"
#include <HTTPClient.h>
#include <WiFi.h>
#include <unordered_map>
#include <string>

class Settings : protected Ui
{
private:
    inline static Controller controller{};

    inline static lv_obj_t* settings_tile = nullptr;
    inline static lv_obj_t* settings_label = nullptr;
    inline static lv_obj_t* settings_dropdown = nullptr;
    inline static lv_obj_t* transport_dropdown = nullptr;
    inline static lv_obj_t* confirm_btn = nullptr;
    inline static lv_obj_t* save_btn = nullptr;
    inline static lv_obj_t* load_btn = nullptr;
    inline static lv_obj_t* WiFi_status_label = nullptr;



    //Storing all the stations and their ID together with their transportation types
    struct station_info
    {
        int station_id;
        std::string transport_types;
    };
    std::unordered_map<std::string, station_info> station_id_table;

    
    //Here the current selected options are stored as an array of characters.
    static constexpr uint32_t buff_size = 64;
    inline static char selected_station_option[buff_size]{};
    inline static char selected_transport_option[buff_size]{};

    void station_options(lv_obj_t* parent);
    void transport_options(lv_obj_t *parent);
    static void on_confirm_btn_clicked(lv_event_t *event);
    static void on_save_btn_clicked(lv_event_t *event);
    static void on_load_btn_clicked(lv_event_t *event);
    static void on_dropdown_value_change(lv_event_t* event);
    static void on_dropdown_value_change_transport(lv_event_t *event);
    static void get_selected(lv_event_t *event);

    std::string station_names = "";
    std::string transport_names = "";

public:
    Settings();
    ~Settings();
    void create();
    const char* create_station_dropdown_string();
    const char* create_transport_dropdown_string();
    static const char* get_station();
    static const char* get_transport();
};

