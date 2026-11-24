#pragma once
#include "ui.h"

class Journey_Page : public Ui
{
    private:
    inline static lv_obj_t* front_tile = nullptr;
    inline static lv_obj_t* front_label = nullptr;

    inline static lv_obj_t* orgin_dropdown = nullptr;
    
    public:
    Journey_Page();
    ~Journey_Page();
    void create();
    void create_orgin_dropdown(lv_obj_t* parent);
};
