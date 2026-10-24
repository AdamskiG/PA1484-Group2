#pragma once
#include "ui.h"

class front_page : public ui
{
    private:
    static lv_obj_t* front_tile;
    static lv_obj_t* front_label;
    public:
    front_page();
    ~front_page();
    void create();
};
