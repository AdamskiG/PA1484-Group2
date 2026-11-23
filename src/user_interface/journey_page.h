#pragma once
#include "ui.h"

class Journey_Page : public Ui
{
    private:
    inline static lv_obj_t* front_tile = nullptr;
    inline static lv_obj_t* front_label = nullptr;
    
    public:
    Journey_Page();
    ~Journey_Page();
    void create();
};
