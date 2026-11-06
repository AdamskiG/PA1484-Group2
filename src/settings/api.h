#pragma once
#include "WString.h"

// A class to handle API call request and recieves data.
class Api
{
    private:
    String searchterm{};
    static constexpr uint32_t buff_size = 64;
    inline static String url_stopcode_lookup = "https://realtime-api.trafiklab.se/v1/stops";

    public:
    static void get_area_code(String selected_option);
    // String get_all_stations();
};
