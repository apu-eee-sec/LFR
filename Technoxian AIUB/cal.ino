void cal() {
  for (int i = 0; i < 8; i++) {
    maximum[i] = 0;
    minimum[i] = 1023;
  }
  motor(-150, 150);
  for (int i = 0; i < 1500; i++) {
    for (int i = 0; i < 8; i++) {
      sensor_value[i] = analogRead(i);
      maximum[i] = max(maximum[i], sensor_value[i]);
      minimum[i] = min(minimum[i], sensor_value[i]);
    }
  }
  motor(0, 0);
  for (int i = 0; i < 8; i++) {
    mid[i] = (maximum[i] + minimum[i]) / 2;
    EEPROM.write(i, mid[i] / 4); delay(10);
    EEPROM.write(i + 8, maximum[i] / 4); delay(10);
    EEPROM.write(i + 16, minimum[i] / 4); delay (10);
  }
}
