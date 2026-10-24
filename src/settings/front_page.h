#pragma once
#include "ui.h"

class front_page : public ui
{
    private:
    inline static lv_obj_t* front_tile = nullptr;
    inline static lv_obj_t* front_label = nullptr;

    public:
    front_page();
    ~front_page();
    void create();
};
