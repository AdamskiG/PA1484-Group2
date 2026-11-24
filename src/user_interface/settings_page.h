#pragma once

#include "ui.h"
#include "settings/api.h"
#include <HTTPClient.h>
#include <WiFi.h>
#include <map>
#include <string>

class Settings : public Ui
{
private:
    inline static lv_obj_t* settings_tile = nullptr;
    inline static lv_obj_t* settings_label = nullptr;

    inline static lv_obj_t* station_dropdown = nullptr;
    inline static lv_obj_t* transport_dropdown = nullptr;

    inline static lv_obj_t* confirm_btn = nullptr;
    inline static lv_obj_t* save_btn = nullptr;
    inline static lv_obj_t* load_btn = nullptr;

    inline static lv_obj_t* wifi_status_label = nullptr;

    //Storing all the stations and their ID together with their transportation types
 
    //std::map<String, std::map<String, String>> station_id_table;
    
    //Here the current selected options are stored as an array of characters.
    static constexpr uint32_t buff_size = 64;
    String selected_station_option;
    String selected_station_id;
    String selected_transport_option;

    void station_options(lv_obj_t* parent);
    void transport_options(lv_obj_t *parent);
    void buttons_create(lv_obj_t *parent);
    // void on_save_btn_clicked(lv_event_t *event);
    // void on_load_btn_clicked(lv_event_t *event);
    
    static void on_station_value_change(lv_event_t* event);
    static void on_transport_value_change(lv_event_t *event);

    void set_station_dropdown();
    void set_transport_dropdown();

    //String station_names = "";
    String transport_names = "";
    std::string wifi_status;

    void set_station_dropdown_option(const String& new_station);
    bool set_transport_dropdown_option(const String& new_transport);

    void set_station_text(const String& saved_station);
    void set_transport_text(const String& saved_transport);

public:
    Settings();
    ~Settings();
    void create();
    void update_WiFi_status();
    //void set_station_id_table(std::map<String, std::map<String, String>> sorted_data);

    // Button getters
    lv_obj_t* get_confirmed_button();
    lv_obj_t* get_save_button();
    lv_obj_t* get_load_button();

    // Data getters
    void get_selected();
    const String get_station();
    const String get_station_id();
    const String get_transport();

    // Data setters
    void set_station(const String& new_station);
    void set_transport(const String& new_transport);
};

