/*
   Sensor for Weather station with
   ESP8266
   Sensors: Rain
*/
#include <cy_serdebug.h>
#include <cy_serial.h>

#include "cy_wifi.h"
#include "cy_ota.h"

#include "gizwits.h"

#define gc_pin_rain 5     // INT1

//#include "toolwifi.h"

#include <Metro.h>

#include "toolint.h"
//#include "weather.h"
#include "cy_weather.h"

const char *gc_hostname = "gizrain";

Metro go_metro = Metro(60000);

void setup() {

  cy_serial::start(__FILE__);

  //---------------------------------

  set_rgb(255, 255, 255);

  delay(1000);

  wifi_init(gc_hostname);

  delay (1000);

  init_ota(gv_clientname);

  set_rgb(0, 0, 0);

  delay(1000);

  Int_setup();

  get_rain();

}

void loop() {

  check_wifi_conn();

  check_ota();

  if (go_metro.check() == 1) {
    DebugPrintln("Metro");
    get_rain();
  }

  delay(500);

}

void get_rain() {
  gf_no_int = true;

  int lv_rain_cnt = gf_rain_cnt;
  gf_rain_cnt = 0;
  gf_no_int = false;

  float lv_rain_val = lv_rain_cnt;
  lv_rain_val = lv_rain_val * 0.2; // 0.632;
  DebugPrintln(lv_rain_val);

  send_val(8, lv_rain_val);
  send_val24(10, 8);
}
