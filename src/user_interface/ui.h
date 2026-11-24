#pragma once
#include <map>
#include <WString.h>
#include "lvgl.h"
#include <Arduino.h>
#include <map>

class Ui 
{
    protected:
    static constexpr uint32_t buff_size = 64;
    inline static String station_names = "";
    inline static lv_obj_t* tileview = nullptr;
    inline static std::map<String, std::map<String, String>> station_id_table = std::map<String, std::map<String, String>>();
    static void set_all_station_options();
    
    public:
    Ui();
    virtual ~Ui();
    virtual void create(); // Creates different Tiles
    void apply_tile_colors(lv_obj_t* tile, lv_obj_t* label, bool dark); //Apply colors to tile and text
    static void set_station_id_table(std::map<String, std::map<String, String>> sorted_data);
};