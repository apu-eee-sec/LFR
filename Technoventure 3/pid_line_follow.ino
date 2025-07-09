/*
 * Left-------Green light
 * Right------Red light
 * Cross,T----Yellow light
*/
void pid_line_follow() {
  while (1) {  //infinite loop
a:
    sensor_read();
    if (sum == 0) {
      if (flag != 's') {
        (flag == 'l') ? motor(-turnspeed, turnspeed) : motor(turnspeed, -turnspeed);
        while (sensor_value[3] == 0 && sensor_value[4] == 0) sensor_read();
        (flag == 'l') ? motor(bari_speed, -bari_speed) : motor(-bari_speed, bari_speed);
        delay(bari_time);
        flag = 's';
        cross = 's';
        // stopLight();
      } else if (flag == 's' || sensor_value[7] + sensor_value[6] + sensor_value[1] + sensor_value[0] == 0) {  //U turn
        m2 = millis();                                                                                         //U turn
        while (sum == 0) {                                                                                     //U turn
          sensor_read();                                                                                       //U turn
          if (millis() - m2 > u_turn_delay) {                                                                  //U turn
            motor(0, 0);
            delay(100);                                                                       //U turn
            (side == 'l') ? motor(-turnspeed, turnspeed) : motor(turnspeed, -turnspeed);      //U turn
            while (sensor_value[3] == 0 && sensor_value[4] == 0) sensor_read();               //U turn
            (side == 'l') ? motor(bari_speed, -bari_speed) : motor(-bari_speed, bari_speed);  //U turn
            delay(bari_time);                                                                 //U turn
            break;                                                                            //U turn
          }
        }
      }
    } else if (sum == 1 || sum == 2 || decimal == 0b11100000 || decimal == 0b01110000 || decimal == 0b00111000 || decimal == 0b00011100 || decimal == 0b00001110 || decimal == 0b00000111) {  //only for straight line
      if (cross != 's') {
        //        show_the_value();
        //        Serial.println("_______S END_______");
        turnCross();
        // stopLight();
      }
      pid();
    }
    //________________left,right,left-forward,right-forward turn____________
    else if (sum == 3 || sum == 4 || sum == 5 || sum == 6 || sum == 7) {
b:
      if (sensor_value[7] + sensor_value[6] > 0 && sensor_value[0] + sensor_value[1] > 0) {
        flag = side;
        y = millis();
        while (sum != 0 && (millis() - y) <= 80) {
          sensor_read();
          pid();
        }
      }

      else if (sensor_value[7] + sensor_value[6] > 0 && sensor_value[0] == 0 && sensor_value[3] + sensor_value[4] > 0) {  //_________90 degree left detection logic___________
        // green();
        flag = 'l';                                                                                             //_________90 degree left detected___________
        while (sensor_value[7] + sensor_value[6] + sensor_value[5] > 0 && sensor_value[0] == 0) sensor_read();  //_________90 degree left and forward detection logic___________
        if (sensor_value[0] == 0) {                                                                             //_________90 degree left and forward detection logic___________
          delay(node_delay / 2);                                                                                //_________90 degree left and forward detection logic___________
          sensor_read();
          //_________90 degree left and forward detection logic___________
          if (sum == 1 || sum == 2 || sum==3) {
            m2 = millis();
            while (millis() - m2 < node_delay / 2) pid();
          } else delay(node_delay / 2);
          sensor_read();  //_________90 degree left and forward detection logic___________
          if (sum != 0)
            if (side == 'l') cross = 'l';  //_________90 degree left and forward detected___________

        } else {
          flag = 's';
          cross = 's';
          goto b;
        }
      }

      else if (sensor_value[7] == 0 && sensor_value[0] + sensor_value[1] > 0 && sensor_value[3] + sensor_value[4] > 0) {  //_________90 degree right detection logic___________
        // red();
        flag = 'r';                                                                                             //_________90 degree right detected___________
        while (sensor_value[7] == 0 && sensor_value[0] + sensor_value[1] + sensor_value[2] > 0) sensor_read();  //_________90 degree right and forward detection logic___________
        if (sensor_value[7] == 0) {                                                                             //_________90 degree right and forward detection logic___________
          delay(node_delay / 2);                                                                                //_________90 degree left and forward detection logic___________
          sensor_read();
          //_________90 degree left and forward detection logic___________
          if (sum == 1 || sum == 2) {
            m2 = millis();
            while (millis() - m2 < node_delay / 2) pid();
          } else delay(node_delay / 2);
          sensor_read();  //_________90 degree right and forward detection logic___________
          if (sum != 0)
            if (side == 'r') cross = 'r';  //_________90 degree right and forward detected___________
        } else {
          flag = 's';
          cross = 's';
          goto b;
        }
      }
      m1 = millis();
    }

    //________________stop,T section,cross section____________
    else if (sum == 8) {
      flag = side;
      m2 = millis();
      while ((sensor_value[7]+ sensor_value[6]+sensor_value[5]>0 || sensor_value[0]+sensor_value[1]+sensor_value[2]>0) && sum>=7) {  //________________________stop point logic________________________
        sensor_read();                                                                                                              //________________________stop point logic________________________
        if (millis() - m2 > stop_timer) {                                                                                           //________________________stop point logic________________________
          motor(0, 0);                                                                                                              //________________________stop point logic________________________
                                                                                                                                    //          flag='s';cross='s';
          while (sum == 8) sensor_read();                                                                                           //________________________stop point logic________________________
          goto a;                                                                                                                   //________________________stop point logic________________________
        }
      }
      delay(node_delay);           //________________________T and cross section logic________________________
      sensor_read();               //________________________T and cross section logic________________________
      if (sum != 0) cross = side;  //________________________if sum =0 than T, else cross section detected________________________
      m1 = millis();
      // yellow();
    }
    if (millis() - m1 > 500) flag = 's';
  }
}
