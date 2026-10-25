#pragma once
#include <HTTPClient.h>
#include <Wifi.h>
#include "secrets.h"

class api
{
    private:
    static constexpr uint32_t buff_size = 64;

    public:
    static void connect_wifi();
    bool call_request();
};
