#include "HX711.h"
 
// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 12;
const int LOADCELL_SCK_PIN = 13;
 
HX711 scale;
 
void setup() {
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
}
 
void loop() {
 
  if (scale.is_ready()) {
    long reading = scale.read() * - 909;
    float grams = (float)reading / 100000.0;
    grams = grams + 1490.3 + 50;
    Serial.print("HX711 reading: ");
    Serial.print(grams);
    Serial.println(" g");
  } 
  else {
    Serial.println("HX711 not found.");
  }
 
  delay(1000);
  
}
