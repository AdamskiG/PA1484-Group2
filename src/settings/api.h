#pragma once
#include <HTTPClient.h>
#include <Wifi.h>

// A class to handle API call request and recieves data.
class api
{
    private:
    static constexpr uint32_t buff_size = 64;
    inline static const std::string url_stopcode_lookup = "https://realtime-api.trafiklab.se";

    public:
    static bool call_request(std::string selected_option);
};
