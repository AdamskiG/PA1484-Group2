#pragma once
#include "ui.h"
#include "departure_data.h"

class Departure : protected Ui
{
    private:
    inline static lv_obj_t* departure_page = nullptr;

    public:
    void create();
    static void set_station(char* selected_station);
};