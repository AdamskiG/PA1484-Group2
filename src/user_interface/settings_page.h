#pragma once
#include "ui.h"
#include "settings/controller.h"
#include "settings/api.h"
#include <HTTPClient.h>
#include <WiFi.h>
#include <unordered_map>
#include <string>

class Settings : public Ui
{
private:
    inline static Controller* controller;

    inline static lv_obj_t* settings_tile = nullptr;
    inline static lv_obj_t* settings_label = nullptr;
    inline static lv_obj_t* settings_dropdown = nullptr;
    inline static lv_obj_t* transport_dropdown = nullptr;
    inline static lv_obj_t* confirm_btn = nullptr;
    inline static lv_obj_t* save_btn = nullptr;
    inline static lv_obj_t* load_btn = nullptr;
    inline static lv_obj_t* WiFi_status_label = nullptr;

    //Storing all the stations and their ID together with their transportation types
 
    std::map<String, std::map<String, String>> station_id_table;

    
    //Here the current selected options are stored as an array of characters.
    static constexpr uint32_t buff_size = 64;
    static String selected_station_option;
    static String selected_transport_option;

    void station_options(lv_obj_t* parent,std::map<String, std::map<String, String>> station_id_table);
    void transport_options(lv_obj_t *parent, std::map<String, std::map<String, String>> station_id_table);
    // static void on_confirm_btn_clicked(lv_event_t *event);
    void on_save_btn_clicked(lv_event_t *event);
    void on_load_btn_clicked(lv_event_t *event);
    
    static void on_dropdown_value_change(lv_event_t* event);
    static void on_dropdown_value_change_transport(lv_event_t *event);

    void set_station_dropdown(std::map<String, std::map<String, String>> station_id_table);
    void set_transport_dropdown(std::map<String, std::map<String, String>> station_id_table);

    String station_names = "";
    String transport_names = "";
    String station_id = "";
    std::string wifi_status;

public:
    Settings();
    ~Settings();
    void create();
    void update();
    void set_station_id_table(std::map<String, std::map<String, String>> sorted_data);
    lv_obj_t* get_confirmed_button();
    static void get_selected();
    static const String get_station();
    static const String get_transport();
    static const String get_station_id();
};

