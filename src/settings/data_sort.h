#pragma once
#include <ArduinoJson.h>
#include "controller.h"

// A class to sort the incoming data
class Data_Sort
{
    private:
    public:
    String sort_station(JsonDocument* doc);
};