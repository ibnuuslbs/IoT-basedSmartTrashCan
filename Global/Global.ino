#include "HX711.h"
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servo1;
int fullTrash = 0;
 
// Circuit wiring
const int LOADCELL_DOUT_PIN = 12;
const int LOADCELL_SCK_PIN = 13;
int limitSwitch = 23;
int trigPin = 27;
int echoPin = 26;
long distance;
long duration;
unsigned long interval=3000; // the time we need to wait
unsigned long previousMillis=0; // millis() returns an unsigned long.
 
HX711 scale;
 
void setup() {
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  servo1.attach(25); 
  pinMode(limitSwitch, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Jehian Airell S.");
  lcd.setCursor(0,1);
  lcd.print("   5215163429   ");
  delay(2000);
  lcd.clear();
}
 
void loop() {
 fullTrash = digitalRead(limitSwitch);
 
 if (fullTrash == HIGH) {
  lcd.clear();
  lcd_print();
  HX711_read();
  ultrasonic_read();
  servo_act(); 
 }

 else if (fullTrash == LOW) {
  lcd.setCursor(0, 0);
  lcd.print(" Tempat  Sampah ");
  lcd.setCursor(0, 1);
  lcd.print("     Penuh      ");
  servo1.write(0);
 }
}
