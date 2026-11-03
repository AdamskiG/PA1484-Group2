#pragma once
#include <HTTPClient.h>
#include <Wifi.h>
// #include "secrets.h"

// A class to handle API call request and recieves data.
class api
{
    private:
    static constexpr uint32_t buff_size = 64;
    inline static const char* url_stopcode_lookup = "https://realtime-api.trafiklab.se";

    public:
    // static void connect_wifi();
    // static bool call_request(char* seleceted_option);
};
