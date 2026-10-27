#pragma once
#include <HTTPClient.h>
#include <Wifi.h>
#include "secrets.h"

class api
{
    private:
    static constexpr uint32_t buff_size = 64;
    inline static const char* url_stopcode_lookup = "https://realtime-api.trafiklab.se";
    public:
    static void connect_wifi();
    bool call_request();
};
