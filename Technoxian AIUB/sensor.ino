
//uint32_t invertTime
//____________________Create sensor reading function____________________
//void sensor_read() {
//  sum = 0;
//  decimal = 0;
//  for (int i = 0; i < 8; i++) {
//    sensor_value[i] = analogRead(sensor_pin[i]);
//    (sensor_value[i] > mid[i]) ? sensor_value[i] = 1 : sensor_value[i] = 0;
//    sum = sum + sensor_value[i];
//    decimal += sensor_value[i] * base[i];
//  }
//  if (invertEnable)invertMech(); 
////  show_the_value();
//}
//void invertMech() {
//  if (isInvert == false && (sum >5 &&sum <8) && sensor_value[7] + sensor_value[6]+ sensor_value[5]> 1 && sensor_value[0] + sensor_value[1]+ sensor_value[2]> 1 && (sensor_value[3] == 0 || sensor_value[4] == 0 )) {
//    isInvert = true;
//    flag='s';cross='s';
//    //    MAX_SPEED = 220; MIN_SPEED = -220; SET_SPEED = 220;
//  }
//  else if (sum < 4 && sensor_value[7] + sensor_value[0] == 0 && sensor_value[3] + sensor_value[4] > 0 && isInvert == true) {
//    isInvert = false;
//    flag='s';cross='s';
////          MAX_SPEED = 250; MIN_SPEED = -250; SET_SPEED = 250;
//  }
//  if (isInvert) {
//    sum = 0;
//    decimal = 0;
//    for (int i = 0; i < 8; i++) {
//      (sensor_value[i] == 0) ? sensor_value[i] = 1 : sensor_value[i] = 0;
//      sum = sum + sensor_value[i];
//      decimal += sensor_value[i] * base[i];
//    }
//  }
//}
//____________________Create sensor showing function____________________
void show_the_value() {
  for (int i = 7; i >= 0 ; i--) {
    Serial.print(sensor_value[i]);
    Serial.print(" ");
  }
  Serial.print(" ");
  Serial.print(sum);
  Serial.print(" flag:");
  Serial.print(flag);
  Serial.print(" cross:");
  Serial.println(cross);
  //    delay(500);
}
void show_analog() {
  for (int i = 0; i < 8; i++) {
    sensor_value[i] = analogRead(sensor_pin[i]);
  }
  for (int i = 7; i >= 0 ; i--) {
    Serial.print(sensor_value[i]);
    Serial.print(" ");
  }
  Serial.println("");
  //    delay(500);
}
