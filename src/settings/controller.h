#pragma once
#include <string>
#include "api.h"
#include "data_sort.h"
#include "user_interface/ui.h"

// A central class that handels the exchange of data to minimize the entanglement of three classes
// Settings sends data to controller. Controller handels the data and sends it along. Knows about API, Sorting and departure.
class Controller
{
    private:
    
    public:
    std::string set_stations();
    std::string create_station_dropdown_string(String data);
};