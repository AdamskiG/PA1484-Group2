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
static Controller* main_control;

static void create_ui()
{
  main_control = new Controller(KEY, KEY_RES);
  main_control->init();
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

  connect_wifi();
  create_ui();
}

const long interval_time_UI = 5000; // update wifi status every 5 seconds
unsigned long time_last_updated_WiFi_status = 0;

const long interval_time_departure_data = 60000; // fetch new departure data every 60 seconds
unsigned long time_last_fetched_data = 0;

// Must have function: Loop runs continously on device after setup
void loop()
{
  lv_timer_handler();
  delay(5);

  // might work, should update the parts of the ui that need it, i.e data
  unsigned long current_time = millis();

  if(current_time - time_last_updated_WiFi_status >= interval_time_UI)
  {
    main_control->update_WiFi_status();
    time_last_updated_WiFi_status = current_time;
  }

  if(current_time - time_last_fetched_data >= interval_time_departure_data)
  {
    main_control->update_departure_page();
    time_last_fetched_data = current_time;
    Serial.println("Updated departure data"); // for testing
  }
}