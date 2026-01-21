#include <Adafruit_NeoPixel.h>

#define OUTPUT_PIN 0
#define LED_COUNT 12
#define XMC_LED 15
#define INPUT_PIN 1

Adafruit_NeoPixel ring(LED_COUNT, OUTPUT_PIN, NEO_GRB + NEO_KHZ800);

unsigned long pixelPrevious = 0;        // Previous Pixel Millis
bool          patternComplete = false;

int           pixelInterval = 50;       // Pixel Interval Teater(ms)
uint16_t      pixelNumber = LED_COUNT;  // Total Number of Pixels
//bool          executedCase1 = false;  // Flag to track if case 1 has been execute


void setup() {
  ring.begin();        // Initialize the LED ring
  ring.show();         // Turn off all LEDs initially
  pinMode(XMC_LED, OUTPUT);
  //pinMode should be changed from INPUT_PULLUP to INPUT if connected to Poller 
  pinMode(INPUT_PIN, INPUT);
}


void loop() {
  // Check if INPUT_PIN is HIGH
  if (digitalRead(INPUT_PIN) == HIGH) {
    unsigned long currentMillis = millis(); // Update current time

      
      // Non-blocking interval for Pulse
      if (currentMillis - pixelPrevious >= pixelInterval) {
        pixelPrevious = currentMillis; // Update previous frame time
        Pulse(ring.Color(0, 100, 0), 10); // Green
      }
    }
  else{
      ring.fill(ring.Color(20, 20, 20), 0, 12);
      ring.show();
      digitalWrite(XMC_LED, HIGH);

  }
}

// Gradual pulsing effect (green)
void Pulse(uint32_t color, int wait) {
  for (int c = 1; c < 100; c += 1) {
    ring.fill(ring.Color(0, c, 0), 0, 12);
    ring.show();
    delay(wait);
  }
  for (int c = 100; c > 1; c -= 1) {
    ring.fill(ring.Color(0, c, 0), 0, 12);
    ring.show();
    delay(wait);
  }
}
