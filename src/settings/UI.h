#pragma once
#include "lvgl.h"

class UI 
{
    public:
    UI();
    virtual ~UI();
    virtual void create() = 0;
    void apply_tile_colors(lv_obj_t* tile, lv_obj_t* label, bool dark);
};