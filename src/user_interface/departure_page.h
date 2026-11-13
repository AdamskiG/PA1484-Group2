#pragma once
#include <cctype>
#include "ui.h"
#include "departure_data.h"

class Departure : protected Ui
{
    private:
    inline static lv_obj_t* departure_tile = nullptr;
    inline static lv_obj_t* departure_table = nullptr;
    inline static lv_obj_t* departure_label = nullptr;


    public:
    Departure();
    ~Departure();
    void create();
    static void show_departure(Departure_Data_Holder data);
};