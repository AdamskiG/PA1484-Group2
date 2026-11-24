#pragma once
#include "ui.h"

class Journey_Page : public Ui
{
    private:
    inline static lv_obj_t* journey_tile = nullptr;
    inline static lv_obj_t* journey_label = nullptr;
    inline static lv_obj_t* origin_dropdown = nullptr;
    inline static lv_obj_t* destination_dropdown = nullptr;
    inline static lv_obj_t* journey_confirm_btn = nullptr;

    String selected_origin_option;
    String selected_station_id;
    String selected_destination_option;

    void get_selected();
    void set_origin_dropdown();
    void set_destination_dropdown();
    void create_orgin_dropdown(lv_obj_t* parent);
    void create_destination_dropdown(lv_obj_t* parent);
    void create_confirm_btn(lv_obj_t* parent);

    public:
    Journey_Page();
    ~Journey_Page();
    void create();


};
