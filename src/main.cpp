#include <FastLED.h>
#include <WiFi.h>
#include <WiFiUdp.h>

const char * ssid = "aschaffenburg-dev.freifunk.net";
// const char * password = "***********";

// How many leds in your strip?
#define NUM_LEDS 362
// #define NUM_LEDS_2 50

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 2
// #define CLOCK_PIN 13

// Define the array of leds
CRGB * leds;
// CRGB leds2[NUM_LEDS_2];

//create UDP instance
WiFiUDP udp;

// WiFiServer server(2002);

void setup() {
	Serial.begin(115200);
	// WiFi.mode(WIFI_STA);
	// WiFi.enableIpV6();
	// WiFi.begin(ssid);
	// while (WiFi.status() != WL_CONNECTED) {
  //   delay(500);
  //   Serial.print(".");
  // }
  // Serial.println("");
  // Serial.print("Connected to ");
  // Serial.println(ssid);
  // Serial.print("IP address: ");
  // Serial.println(WiFi.localIP());
	// Serial.println(WiFi.localIPv6());

	// udp.begin(2002);

	Serial.println(ESP.getFreeHeap());
	leds = (CRGB *) malloc(NUM_LEDS * sizeof(CRGB));

  FastLED.addLeds<WS2812, DATA_PIN, GBR>(leds, NUM_LEDS);
  // FastLED.addLeds<WS2812, DATA_PIN, GBR>(leds, 255, 45);
	FastLED.setBrightness(255);
	Serial.println(ESP.getFreeHeap());
}

// static uint8_t hue = 0;
// static uint8_t sin_ = 0;

static uint16_t hue = 0;
static uint16_t sin_ = 0;

// void setAll(bool on, uint32_t delay_) {
// 		sin_ += 1;
// 		hue += 10;
// 	// uint8_t hue = random8();
// 	for(int i = 0; i < NUM_LEDS; i++) {
// 		// double progress = (sin_ + NUM_LEDS - i - 1) % 10 / 10.0 * 2.0 * PI;
// 		// int val = (int)((sin(progress) + 1.0) * 0.5 * 255.0);
// 		int val = 255;
// 		// Serial.println(val);
//   	leds[i] = CRGB(on ? 255 : 0, 0, 0); //CHSV(i*10 + hue, 255, on ? val : 0);
// 		// leds[i] = CHSV(255, 255, 200);
// 	}

//   FastLED.show();

// 	delay(delay_);
// }
static uint16_t off = random16(0, NUM_LEDS);
static uint16_t off_delay = 0;
static uint16_t off_delay_off = 500;

void step() {
		sin_ += 1;
		hue += 2;
	for(int i = 0; i < NUM_LEDS; i++) {
		double progress = (sin_ + NUM_LEDS - i - 1) % 100 / 100.0 * 2.0 * PI;
		int val = (int)((sin(progress) + 1.0) * 0.5 * 254.0) + 1;
		bool is_on = i != off;
		if (is_on)
  		leds[i] = CHSV(i + hue, 255, is_on ? val : 0);
  	// leds[i] = CHSV(i + hue, 255, val);
	}
  	FastLED.show();
}

void loop() {
	// uint8_t buffer[50] = "SIZE";
	// udp.parsePacket();
	// IPAddress ip = udp.remoteIP();
	// uint16_t port = udp.remotePort();
	// if(udp.read(buffer, 50) > 0){
  //   Serial.print("Message: ");
  //   Serial.println((char *)buffer);
	// 	if (memcmp(buffer, "SIZE", 4) == 0) {
	// 		uint8_t buffer[50] = "SIZE 82 1";
	// 		udp.beginPacket(ip, port);
	// 		udp.write(buffer, 10);
	// 		udp.endPacket();
	// 		Serial.println("SIZE exec");
	// 	}
	// 	// if (memcmp(buffer, "PX", 2)) {


	// 	// 	leds[x] = val;
	// 	// }
  // }

	step();
	off_delay += 1;
	if (off_delay > off_delay_off) {
		off_delay = 0;
		off = random16(0, NUM_LEDS);
		off_delay_off = (uint16_t)random8() + 300;
		delay(150);
		sin_ -= 16 + random8() / 4;
		if (random16() > 10) {
			step();
			delay(100);
			step();
			delay(200);
			step();
		}
	}


	// for(int i = 0; i < NUM_LEDS; i++) {
	// 	leds[i] = CRGB(255, 255, 255);
	// }
  // 	FastLED.show();

  // 	FastLED.show();
	// 	delay(32);

	// for(uint8_t i = 0; i < NUM_LEDS; i++) {
	// 	leds[i] = CHSV(255, 255, 0);
	// }

		// delay(200);
		// delay(16);

	// setAll(true, 150);
	// setAll(false, 47);
	// setAll(true, 16);
	// setAll(false, 24);
	// setAll(true, 16);
	// setAll(false, 24);
	// setAll(true, 16);
	// setAll(false, 186);
}
