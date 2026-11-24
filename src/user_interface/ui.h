#pragma once
#include <map>
#include <WString.h>
#include "lvgl.h"
#include <Arduino.h>
#include <map>

class Ui 
{
    protected:
    String station_names = "";
    inline static lv_obj_t* tileview = nullptr;
    std::map<String, std::map<String, String>> station_id_table;
    
    public:
    Ui();
    virtual ~Ui();
    virtual void create(); // Creates different Tiles
    void apply_tile_colors(lv_obj_t* tile, lv_obj_t* label, bool dark); //Apply colors to tile and text
    void set_dropdown_to_all_stations(lv_obj_t* dropdown);
    void set_station_id_table(std::map<String, std::map<String, String>> sorted_data);
};