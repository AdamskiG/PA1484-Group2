#pragma once
#include "WString.h"

// A class to handle API call request and recieves data.
class api
{
    private:
    static constexpr uint32_t buff_size = 64;
    inline static String url_stopcode_lookup = "https://realtime-api.trafiklab.se";

    public:
    static bool call_request(String selected_option);
};
