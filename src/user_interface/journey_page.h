#pragma once
#include "ui.h"
#include <Wstring.h>
#include <iomanip>
#include <sstream>
#include <String>

class Journey_Page : public Ui
{
    private:
    inline static lv_obj_t* journey_tile = nullptr;
    inline static lv_obj_t* journey_label = nullptr;
    inline static lv_obj_t* origin_dropdown = nullptr;
    inline static lv_obj_t* destination_dropdown = nullptr;
    inline static lv_obj_t* journey_confirm_btn = nullptr;
    inline static lv_obj_t* hour_dropdown = nullptr;
    inline static lv_obj_t* minutes_dropdown = nullptr;
    
    String selected_origin_option;
    String selected_origin_id;
    String selected_destination_option;
    String selected_destination_id;
    String time;

    void set_origin_dropdown();
    void set_destination_dropdown();
    void set_time_dropdown();

    void create_orgin_dropdown(lv_obj_t* parent);
    void create_destination_dropdown(lv_obj_t* parent);
    void create_time_dropdown(lv_obj_t* parent);
    void create_confirm_btn(lv_obj_t* parent);

    public:
    Journey_Page();
    ~Journey_Page();
    void create();

    void get_selected();
    String get_time();
    String get_origin_station();
    String get_destination_station();

};
