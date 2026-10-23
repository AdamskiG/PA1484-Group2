#pragma once
#include "lvgl.h"

class ui 
{
    public:
    ui();
    virtual ~ui();
    virtual void create(lv_obj_t* parent);
    void apply_tile_colors(lv_obj_t* tile, lv_obj_t* label, bool dark);

    protected:
    static lv_obj_t* tileview;
};