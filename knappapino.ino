//Please use the "Adafruit Trinket 8MHz" board setting and 
//select "USBTinyISP" programmer on your Arduino IDE 
//for Trinket to use 8pino.



#include <Adafruit_NeoPixel.h>
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
#include <avr/power.h>
#endif

#define PIN 1


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(59, PIN);

uint8_t  mode   = 0, // Current animation effect
         offset = 0; // Position of spinny eyes
uint32_t color  = 0xFF0000; // Start red
uint32_t prevTime;

//bounce switch
const int switchPin = 2 ;

void setup() {
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  pixels.begin();
  pixels.setBrightness(85); // 1/3 brightness
//  prevTime = millis();

 pinMode(switchPin, INPUT);
}

void loop() {
  uint8_t  i;
//  uint32_t t;

  int buttonState = digitalRead(switchPin);
  if (buttonState == HIGH) {
    color >>= 8;                 // Next color R->G->B
    if (!color) color = 0xFF0000; // Reset to red
  }
  

   for (int i = 0; i <59; i++) {
      pixels.setPixelColor(i, color);
   }
   
   pixels.show();
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

void rainbowByStep(float rStep){

  int j = (int)rStep %256;
  for (int i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, Wheel((i + j) & 255));
  }
  pixels.show();
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

