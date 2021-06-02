void HX711_read() {
  
  if (scale.is_ready()) {
      long reading = scale.read() * 495;
      long readings = scale.read();
      float grams = (float)reading / 100000.0;
      grams = grams - 165.84;
      Serial.print("HX711 reading: ");
      
      if (grams < 0) {
        grams = 0;
     }
//      Serial.print(readings);
      Serial.print(grams);
      Serial.println("g");
      lcd.setCursor(5, 1);
      lcd.print(String(grams,2) + "  ");
    
    } else {
      Serial.println("HX711 not found.");
  }
  delay(2000);
//  lcd.clear();

}
