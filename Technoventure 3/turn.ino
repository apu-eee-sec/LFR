void turnCross() {
  (cross == 'l') ? motor(-turnspeed, turnspeed) : motor(turnspeed, -turnspeed);
  while (sensor_value[7] + sensor_value[6] + sensor_value[5] + sensor_value[4] + sensor_value[3] + sensor_value[2] + sensor_value[1] > 0) sensor_read();
  while (sensor_value[3] == 0 && sensor_value[4] == 0) sensor_read();
  (cross == 'l') ? motor(bari_speed, -bari_speed) : motor(-bari_speed, bari_speed);
  delay(bari_time);
  cross = 's';
  flag = 's';
}
// void delay2(){

// }