#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
// #include <ArduinoJson.h>
#include <TFT_eSPI.h>
#include <time.h>
#include <LilyGo_AMOLED.h>
#include <LV_Helper.h>
#include <lvgl.h>

#include <user_interface/settings_page.h>
#include <user_interface/front_page.h>

#include "secrets.h"
#include "key.h"

LilyGo_Class amoled;


// static lv_obj_t* tileview;
// static lv_obj_t* t1;
// static lv_obj_t* t2;
// static lv_obj_t* t1_label;
// static lv_obj_t* t2_label;
// static bool t2_dark = false;  // start tile #2 in light mode

// Function: Tile #2 Color change
// static void apply_tile_colors(lv_obj_t* tile, lv_obj_t* label, bool dark)
// {
//   // Background
//   lv_obj_set_style_bg_opa(tile, LV_OPA_COVER, 0);
//   lv_obj_set_style_bg_color(tile, dark ? lv_color_black() : lv_color_white(), 0);

//   // Text
//   lv_obj_set_style_text_color(label, dark ? lv_color_white() : lv_color_black(), 0);
// }

// static void on_tile2_clicked(lv_event_t* e)
// {
//   LV_UNUSED(e);
//   t2_dark = !t2_dark;
//   apply_tile_colors(t2, t2_label, t2_dark);
// }

// Function: Creates UI
static void create_ui()
{
  static Settings settings_p;
  static Front_Page front_p;
  front_p.create();
  settings_p.create();
}

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
void setup()
{
  Serial.begin(115200);
  delay(200);

  if (!amoled.begin()) {
    Serial.println("Failed to init LilyGO AMOLED.");
    while (true) delay(1000);
  }

  beginLvglHelper(amoled);   // init LVGL for this board

  create_ui();
  connect_wifi();
}

// Must have function: Loop runs continously on device after setup
void loop()
{
  lv_timer_handler();
  delay(5);
}