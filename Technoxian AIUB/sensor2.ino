bool isNotInverted = true;
uint32_t m3 = 0;
bool times = true;
void sensor_read() {
  decimal = 0;
  sum = 0;
    for (int i = 0; i < 8; i++) {
      (analogRead(i) > mid[i]) ? sensor_value[i] = 1 : sensor_value[i] = 0;
      decimal += sensor_value[i] * base[i];
      sum += sensor_value[i];
    }
    if(sum>3){
      MAX_SPEED = 150; MIN_SPEED = -150; SET_SPEED = 150;
    }
    else{
      MAX_SPEED = 255; MIN_SPEED = -255; SET_SPEED = 255;
    }
}

void invert_mech() {
  if (sum > 5 && sensor_value[7] + sensor_value[6] + sensor_value[5] >= 2  && sensor_value[3] + sensor_value[4] <= 1 && sensor_value[2] + sensor_value[1] + sensor_value[0] >= 2) {
    //    flag = 's'; cross = 's';
    if (times) {
      m3 = millis();
      times = false;
      motor(40,40);
    }
    else if ((millis() - m3) >= 50) {
      times = true;
      (isNotInverted) ? isNotInverted = false : isNotInverted = true;
      decimal = 0;
      sum = 0;
      for (int i = 0; i < 8; i++) {
        (sensor_value[i] == 1) ? sensor_value[i] = 0 : sensor_value[i] = 1;
        decimal += sensor_value[i] * base[i];
        sum += sensor_value[i];
      }
    }
  }
}
