#include <Adafruit_NeoPixel.h>

#define OUTPUT_PIN 0
#define LED_COUNT 12
#define XMC_LED 15
#define INPUT_PIN 1

Adafruit_NeoPixel ring(LED_COUNT, OUTPUT_PIN, NEO_GRB + NEO_KHZ800);

unsigned long pixelPrevious = 0;        // Previous Pixel Millis
unsigned long patternPrevious = 0;      // Previous Pattern Millis
int           patternCurrent = 0;       // Current Pattern Number
int           patternInterval = 5000;   // Pattern Interval (ms)
bool          patternComplete = false;

int           pixelInterval = 50;       // Pixel Interval Teater(ms)
int           IntervalWheel = 500;      // Pixel Interval Wheel(ms)
int           pixelQueue = 0;           // Pattern Pixel Queue
int           pixelCycle = 0;           // Pattern Pixel Cycle
uint16_t      pixelNumber = LED_COUNT;  // Total Number of Pixels

void setup() {
  ring.begin();        // Initialize the LED ring
  ring.show();         // Turn off all LEDs initially
  ring.setBrightness(20);
  pinMode(XMC_LED, OUTPUT);
  //pinMode should be changed from INPUT_PULLUP to INPUT if connected to Poller 
  pinMode(INPUT_PIN, INPUT_PULLUP);
}

void loop() {
    // Check if INPUT_PIN is HIGH
  if (digitalRead(INPUT_PIN) == HIGH) {
    unsigned long currentMillis = millis();                     //  Update current time
    if( patternComplete || (currentMillis - patternPrevious) >= patternInterval) {  //  Check for expired time
      patternComplete = false;
      patternPrevious = currentMillis;
      patternCurrent++;                                         //  Advance to next pattern
      if(patternCurrent >= 3)
        patternCurrent = 2;
    }

    if(currentMillis - pixelPrevious >= pixelInterval) {        //  Check for expired time
      pixelPrevious = currentMillis;                            //  Run current frame
      switch (patternCurrent) {
        case 2:
          colorWipe(ring.Color(100, 100, 100), 500); // White
          break;

        case 1:
          theaterChase(ring.Color(100, 100, 100), 50); // White
          break;

        default:
          theaterChase(ring.Color(100, 100, 100), 50); // White
          break;
      }
  
  
    digitalWrite(XMC_LED, HIGH); 

  }}
}


// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  static uint32_t loop_count = 0;
  static uint16_t current_pixel = 0;

  pixelInterval = wait;                   //  Update delay time

  ring.clear();

  for(int c=current_pixel; c < pixelNumber; c += 3) {
    ring.setPixelColor(c, color);
  }
  ring.show();

  current_pixel++;
  if (current_pixel >= 3) {
    current_pixel = 0;
    loop_count++;
  }

  if (loop_count >= 6) {
    current_pixel = 0;
    loop_count = 0;
    patternComplete = true;
    ring.clear();

  }
}

void colorWipe(uint32_t color, int wait) {
  ring.fill(ring.Color(0, 0, 100), 0, 12) ; 
  static uint16_t current_pixel = 0;
  pixelInterval = wait;                        //  Update delay time
  ring.setPixelColor(current_pixel++, color); //  Set pixel's color (in RAM)
  ring.show();                                //  Update strip to match
  if(current_pixel >= pixelNumber) {           //  Loop the pattern from the first LED
    current_pixel = 0;
    patternComplete = true;
    ring.clear();

  }
}

