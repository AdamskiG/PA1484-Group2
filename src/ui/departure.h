#pragma once
#include "ui.h"

class Departure : protected ui
{
    private:
    inline static lv_obj_t* departure_page = nullptr;

    public:
    void create();
    static void set_station(char* selected_station);
};