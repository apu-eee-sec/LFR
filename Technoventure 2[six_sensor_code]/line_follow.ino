void line_follow() {
  while (1) { //infinite loop
a:    reading();
    if (sum == 0) {
      if (flag != 's') turn();
      else if (pos > -3 && pos < 3) uturn_or_not();
    }
    else if (sum == 1 || sum == 2) {  //only for straight line
      if (cross != 's') cross_or_L();
      if (sensor == 0b001100) {
        if (pos != 0) s_bari();
        motor(10 * spl, 10 * spr);
      }
      else stay_straight();

    }

    else if (sum == 3 || sum == 4 || sum == 5) {
      if (s[5] == 1 && s[0] == 0 && s[2] + s[3] > 0) {
        flag = 'l';
        while (s[5] == 1 && s[0] == 0) reading();
        if (s[0] == 0) {
          delay(node_delay);
          reading();
          if (sum != 0) if (side == 'l') cross = 'l';
        }
      }

      else if (s[5] == 0 && s[0] == 1 && s[2] + s[3] > 0) {
        flag = 'r';
        while (s[5] == 0 && s[0] == 1) reading();
        if (s[5] == 0) {
          delay(node_delay);
          reading();
          if (sum != 0) if (side == 'r') cross = 'r';
        }
      }
      m1 = millis();
    }

    else if (sum == 6) {
      flag = side;
      m2 = millis();
      while (s[5] == 1 || s[0] == 1) {
        reading();
        if (millis() - m2 > stop_timer) {
          motor(0, 0);
          while (sum == 6) reading();
          goto a;
        }
      }
      delay(node_delay);
      reading();
      if (sum != 0) cross = side;
      m1 = millis();
    }
    if (millis() - m1 > 500) flag = 's';
  }
}
