#pragma once
#include "ui.h"

class Front_Page : protected Ui
{
    private:
    inline static lv_obj_t* front_tile = nullptr;
    inline static lv_obj_t* front_label = nullptr;
    
    public:
    Front_Page();
    ~Front_Page();
    void create();
};
