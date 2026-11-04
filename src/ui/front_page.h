#pragma once
#include "ui.h"

class Front_page : protected Ui
{
    private:
    inline static lv_obj_t* front_tile = nullptr;
    inline static lv_obj_t* front_label = nullptr;
    
    public:
    Front_page();
    ~Front_page();
    void create();
};
