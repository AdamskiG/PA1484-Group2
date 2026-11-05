#pragma once
#include "WString.h"
#include "secrets.h"

// A class to handle API call request and recieves data.
class api
{
    private:
    static constexpr uint32_t buff_size = 64;
    inline static String url_stopcode_lookup = "https://realtime-api.trafiklab.se";
    inline static String get_all_stops = "https://realtime-api.trafiklab.se/v1/stops/name/{Karlskrona}?key={" + KEY + "}";

    public:
    static bool call_request(String selected_option);
    String get_all_stations();
};
