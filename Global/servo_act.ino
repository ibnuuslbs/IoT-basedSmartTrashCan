void servo_act() {
  unsigned long currentMillis = millis();
  if ((unsigned long)(currentMillis - previousMillis) >= interval) { 
    servo1.write(0);
    if((distance <= 10) && (fullTrash==HIGH)){
      servo1.write(180);
    }
      previousMillis = millis();
 }
}
