void publish_ubidots() {

  float massa = ((scale.read() * 495) / 100000.0) - 165.84;
  if (massa < 0 ) {
    massa = 0;
  }
    
  if (!ubidots.connected())
  {
    ubidots.reconnect();
  }
  if (abs(millis() - timer) > PUBLISH_FREQUENCY) // triggers the routine every 5 seconds
  {
    ubidots.add(VARIABLE_LABEL, massa); // Insert your variable Labels and the value to be sent
    ubidots.publish(DEVICE_LABEL);
    timer = millis();
  }
  ubidots.loop();
}