#pragma once
#include "lvgl.h"

class ui 
{
    public:
    ui();
    virtual ~ui();
    virtual void create(); // Creates different Tiles
    void apply_tile_colors(lv_obj_t* tile, lv_obj_t* label, bool dark); //Apply colors to tile and text

    protected:
    inline static lv_obj_t* tileview = nullptr;
};