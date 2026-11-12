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

    char to_char(std::string data);

    public:
    Departure();
    ~Departure();
    void create();
    static void show_departure(std::vector<Departure_Data*> data);
};