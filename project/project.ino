#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
// #include <ArduinoJson.h>
#include <TFT_eSPI.h>
#include <time.h>
#include <LilyGo_AMOLED.h>
#include <LV_Helper.h>
#include <lvgl.h>

// #include <user_interface/settings_page.h>
// #include <user_interface/front_page.h>
#include <settings/controller.h>

#include "secrets.h"
#include "key.h"

LilyGo_Class amoled;

// Function: Creates UI
static void create_ui()
{
  static Controller* main_control;
  main_control = new Controller(KEY, KEY_RES);
  main_control->init();
}

// // Function: Updates UI
// static void update_ui()
// {
//   settings_p.update();
// }

// Function: Connects to WIFI
static void connect_wifi()
{
  Serial.printf("Connecting to WiFi SSID: %s\n", WIFI_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  const uint32_t start = millis();
  while (WiFi.status() != WL_CONNECTED && (millis() - start) < 15000) {
    delay(250);
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("WiFi connected.");
  } else {
    Serial.println("WiFi could not connect (timeout).");
  }
}

// functionality added to create ui function, this function probably won't be needed
// unclear if wifi name should also be included
// std::string status_string = "CONNECTED";
// void check_wifi()
// {
//   if(WiFi.status() == WL_CONNECTED)
//     if(status_string != "CONNECTED")
//       status_string = "CONNECTED";

//   if(WiFi.status() == WL_CONNECTION_LOST)
//     if(status_string != "CONNECTION LOST")
//       status_string = "CONNECTION LOST";
// }

// Must have function: Setup is run once on startup
Controller* main_control = nullptr;
void setup()
{
  Serial.begin(115200);
  delay(200);

  if (!amoled.begin()) {
    Serial.println("Failed to init LilyGO AMOLED.");
    while (true) delay(1000);
  }

  beginLvglHelper(amoled);   // init LVGL for this board

  connect_wifi();
  create_ui();
}

// Must have function: Loop runs continously on device after setup
void loop()
{
  lv_timer_handler();
  delay(5);

  // // might work, should update the parts of the ui that need it, i.e data
  // unsigned long current_time = millis();
  // int interval_time_UI = 5000; // update UI every 5 seconds
  // int time_last_updated_UI = 0;

  // if(current_time - time_last_updated_UI >= interval_time_UI)
  // {
  //   // update_ui();
  //   time_last_updated_UI = current_time;
  // }
}