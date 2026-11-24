#pragma once
#include "ui.h"

class Journey_Page : public Ui
{
    private:
    inline static lv_obj_t* journey_tile = nullptr;
    inline static lv_obj_t* journey_label = nullptr;
    inline static lv_obj_t* origin_dropdown = nullptr;
    inline static lv_obj_t* destination_dropdown = nullptr;

    void set_origin_dropdown();
    void set_destination_dropdown();
    
    public:
    Journey_Page();
    ~Journey_Page();
    void create();
    void create_orgin_dropdown(lv_obj_t* parent);
    void create_destination_dropdown(lv_obj_t* parent);

};
