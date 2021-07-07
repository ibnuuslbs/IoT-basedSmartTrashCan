void HX711_read() {
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

}
