#include "HX711.h"
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include "UbidotsEsp32Mqtt.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servo1;
int fullTrash = 0;

const char *UBIDOTS_TOKEN = "BBFF-y750mo6aH9nmgaslWPvrbQnEzgGJIn";  // Put here your Ubidots TOKEN
const char *WIFI_SSID = "Mi Phone";      // Put here your Wi-Fi SSID
const char *WIFI_PASS = "1arext1arex";      // Put here your Wi-Fi password
const char *DEVICE_LABEL = "iot-based-smart-trash-can-device1";   // Put here your Device label to which data  will be published
const char *VARIABLE_LABEL = "variable-0.8905185595793461"; // Put here your Variable label to which data  will be published



Ubidots ubidots(UBIDOTS_TOKEN);
 
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
const int PUBLISH_FREQUENCY = 15000; // Update rate in milliseconds
unsigned long timer;

 
HX711 scale;

/****************************************
 * Auxiliar Functions
 ****************************************/

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}
 
void setup() {
  
  Serial.begin(57600);
  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  ubidots.setCallback(callback);
  ubidots.setup();
  ubidots.reconnect();

  timer = millis();
  
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
    lcd_print();
//    HX711_read();
    int massa = 0;
    long reading = scale.read() * 484.47;
    long readings = scale.read();
    float grams = (float)reading / 100000.0;
    grams = grams - 483.48;
    Serial.print("HX711 reading: ");
      
    if (grams < 0) {
      grams = 0;
    }
  
    Serial.print(grams);
    Serial.println("g");
    lcd.setCursor(0, 1);
    massa = int(grams);
    lcd.print("    " + String(massa) + " gram    ");
    ultrasonic_read();
    servo_act(); 
  }
  
    if ((fullTrash == LOW) || ((((scale.read() * 484.47) / 100000.0) - 483.48) >= 5000.00)) {
    fullTrashNotifLCD();
    servo1.write(0);
 
 }
  
  publish_ubidots();
}
