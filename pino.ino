//Please use the "Adafruit Trinket 8MHz" board setting and
//select "USBTinyISP" programmer on your Arduino IDE
//for Trinket to use 8pino.
//unplug and plug back in before uploading 

//reported glitch on linux with usb3

#include <Adafruit_NeoPixel.h>
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
#include <avr/power.h>
#endif

#define NEOP_PIN 1
#define SWITCH_PIN 2  //bounce switch
#define PIXEL_CNT 60 //60//59 // 30 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXEL_CNT, NEOP_PIN);

//COLOR
float rainbowStep = 0;

void setup() {
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  pixels.begin();
  pixels.setBrightness(85); // 1/3 brightness

  pinMode(SWITCH_PIN, INPUT);

  //startup animation
//   colorTravel(pixels.Color(240, 0, 240), 30); // purple
  colorWipe(pixels.Color(240, 0, 240), 15); // purple
  colorWipe(pixels.Color(0, 0, 0), 15); // dark 

}

void loop() {


  int buttonState = digitalRead(SWITCH_PIN);
  if (buttonState == HIGH) {
    rainbowStep += 30;  //jump 

  } else {
    rainbowStep += 0.05; //small increment
  }

  if (rainbowStep > 255 ) {
    rainbowStep = (int(rainbowStep))%255 ;
  }

  rainbowByStep(rainbowStep);

}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel((i + j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}

void rainbowByStep(float rStep) {

  int j = (int)rStep % 256;
  for (int i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, Wheel((i + j) & 255));
  }
  pixels.show();
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, c);
    pixels.show();
    delay(wait);
    
  }
}

// Fill the dots one after the other with a color
void colorTravel(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, c);
    pixels.show();
    delay(wait);
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    pixels.show();
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  else {
    WheelPos -= 170;
    return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

