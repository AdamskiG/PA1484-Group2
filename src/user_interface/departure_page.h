#pragma once
#include "ui.h"

class Departure : protected Ui
{
    private:
    inline static lv_obj_t* departure_tile = nullptr;
    inline static lv_obj_t* departure_label = nullptr;

    public:
    Departure();
    ~Departure();
    void create();
    static void set_station(char* selected_station);
};