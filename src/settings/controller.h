#pragma once
#include <WString.h>
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
    String sort_function(String gogogaga);
    std::string set_stations();
};