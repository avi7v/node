
#include <Arduino.h>
#include <arduino_homekit_server.h>
#include "wifi_info.h"

#define LOG_D(fmt, ...)   printf_P(PSTR(fmt "\n") , ##__VA_ARGS__);

void setup() {
	Serial.begin(115200);
	wifi_connect(); // in wifi_info.h
	my_homekit_setup();

}

void loop() {
	my_homekit_loop();
	delay(10);
   Serial.println("Restarting in 1 minutes");
    delay(180 * 60 * 1000); //delay 3 hours
  //delay(10000); //delay 10 sec TEST
  ESP.restart(); //reset
}
extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t cha_switch_on;
static uint32_t next_heap_millis = 0;
#define PIN_SWITCH 13 //D4
void cha_switch_on_setter(const homekit_value_t value) {
	bool on = value.bool_value;
	cha_switch_on.value.bool_value = on;	
	LOG_D("Switch: %s", on ? "ON" : "OFF");
	digitalWrite(PIN_SWITCH, on ? LOW : HIGH);
}

void my_homekit_setup() {
	pinMode(PIN_SWITCH, OUTPUT);
	digitalWrite(PIN_SWITCH, HIGH);

	cha_switch_on.setter = cha_switch_on_setter;
	arduino_homekit_setup(&config);
}

void my_homekit_loop() {
	arduino_homekit_loop();
	const uint32_t t = millis();
}
