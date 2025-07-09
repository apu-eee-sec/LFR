/*
   Left-------Green light
   Right------Red light
   Cross,T----Yellow light
*/
void pid_line_follow() {
  while (button_read() == 0) {  //infinite loop
a:
    sensor_read();
    if (sum == 0) {
      if (flag != 's') {
        (flag == 'l') ? motor(-turnspeed, turnspeed) : motor(turnspeed, -turnspeed);
        while (sensor_value[3] == 0 && sensor_value[4] == 0) sensor_read();
        (flag == 'l') ? motor(bari_speed, -bari_speed) : motor(-bari_speed, bari_speed);
        delay(bari_time);
        flag = 's';
        cross = 's';                                                                                           //when you are done turning robot, make the flag to its normal state so that robot wont turn on its own when it finds no line without detecting 90degree logic
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
    }
    else if (sum == 1 || decimal == 0b11100000 || decimal == 0b01110000 || decimal == 0b00111000 || decimal == 0b00011100 || decimal == 0b00001110 || decimal == 0b00000111 || decimal == 0b11000000 || decimal == 0b01100000 || decimal == 0b00110000 || decimal == 0b00011000 || decimal == 0b00001100 || decimal == 0b00000110 || decimal == 0b00000011) {
      if (cross != 's') {
        //        show_the_value();
        //        Serial.println("_______S END_______");
        (cross == 'l') ? motor(-turnspeed, turnspeed) : motor(turnspeed, -turnspeed);
        while (sensor_value[7] + sensor_value[6] + sensor_value[5] + sensor_value[4] + sensor_value[3] + sensor_value[2] + sensor_value[1] > 0) sensor_read();
        while (sensor_value[3] == 0 && sensor_value[4] == 0) sensor_read();
        (cross == 'l') ? motor(bari_speed, -bari_speed) : motor(-bari_speed, bari_speed);
        delay(bari_time);
        cross = 's';
        flag = 's';
      }
      pid();
    }

    //________________left,right,left-forward,right-forward turn____________
    else if (sum == 3 || sum == 4 || sum == 5 || sum == 6 || sum == 7) {
      //______For Y_____
      if (sensor_value[7] + sensor_value[6] > 0 && sensor_value[0] + sensor_value[1] > 0) {
        flag = side;
        while (sensor_value[7] + sensor_value[6] > 0 || sensor_value[0] + sensor_value[1] > 0) {
          sensor_read();
          pid();
        }
        delay(5);
        sensor_read();
        if (sum != 0) {
          cross = 's';
          flag = 's';
        }
      }

      else if (sensor_value[7] + sensor_value[6] > 0 && sensor_value[0] == 0 && sensor_value[3] + sensor_value[4] > 0) {  //_________90 degree left detection logic___________
        flag = 'l';                                                                                                                         //_________90 degree left detected___________
        while (sensor_value[7] + sensor_value[6] > 0 && sensor_value[0] == 0) {
          sensor_read();
          // pid();
        }                            //_________90 degree left and forward detection logic___________
        if (sensor_value[0] == 0) {  //_________90 degree left and forward detection logic___________
          delay(node_delay);         //_________90 degree left and forward detection logic___________
          sensor_read();             //_________90 degree left and forward detection logic___________
          if (sum != 0)
            if (side == 'l') {
              cross = 's';
              flag = 's';  //_________90 degree left and forward detected___________
            }
        } else {
          //          cross = 's';
          flag = 'r';
          delay(2);
          while (sensor_value[0] + sensor_value[1] > 0) {
            pid();
            sensor_read();
          }
          goto a;
        }
      }

      else if (sensor_value[7] == 0 && sensor_value[0] + sensor_value[1] > 0 && sensor_value[3] + sensor_value[4] > 0) {  //_________90 degree right detection logic___________
        flag = 'r';                                                                                                                         //_________90 degree right detected___________
        while (sensor_value[7] == 0 && sensor_value[0] + sensor_value[1] > 0) {
          sensor_read();  //_________90 degree right and forward detection logic___________
          // pid();
        }
        if (sensor_value[7] == 0) {  //_________90 degree right and forward detection logic___________
          delay(node_delay);         //_________90 degree right and forward detection logic___________
          sensor_read();             //_________90 degree right and forward detection logic___________
          if (sum != 0)
            if (side == 'r') {
              flag = 's';
              cross = 's';  //_________90 degree right and forward detected___________
            }
        } else {
          flag = 'l';
          delay(2);
          while (sensor_value[7] + sensor_value[6] > 0) {
            pid();
            sensor_read();
          }
          goto a;
        }
      }
      m1 = millis();
    }

    //________________stop,T section,cross section____________
    else if (sum == 8) {
      flag = side;
      m2 = millis();
      while (sensor_value[7] + sensor_value[6] > 0 || sensor_value[0] + sensor_value[1] > 0) {  //________________________stop point logic________________________
        sensor_read();
        pid();                             //________________________stop point logic________________________
        if (millis() - m2 > stop_timer) {  //________________________stop point logic________________________
          motor(0, 0);                     //________________________stop point logic________________________
          //          flag='s';cross='s';
          while (sum == 8) sensor_read();  //________________________stop point logic________________________
          goto a;                          //________________________stop point logic________________________
        }
      }
      delay(node_delay);  //________________________T and cross section logic________________________
      sensor_read();      //________________________T and cross section logic________________________
      if (sum != 0) {
        flag = 's';
        cross = 's';  //________________________if sum =0 than T, else cross section detected________________________
      }
      m1 = millis();
    }
    if (millis() - m1 > 500) flag = 's';
  }
}
