#define node_delay4advanc 20                   //to make perfact 90 degree turn             ----------------------------------------------
#define u_turn_delay4advanc 150                 //delay for u turn                          ----------------------------------------------
#define stop_timer4advanc 120                 // stop delay if find end point                  Adjust this value to get perfact result
#define spl 25.5                                 //left motor speed coeficient                ----------------------------------------------
#define spr 25.5                                  //right motor speed coeficient              ----------------------------------------------
int pos;
void adv_line_follow() {
  while (1) { //infinite loop
a:    sensor_read();
    if (sum == 0) {
      if (flag != 's') {
//        show_the_value();
//        Serial.print("_______");
//        Serial.print(flag);
//        Serial.println(" turn END_______");
        (flag == 'l') ? motor(-6 * spl, 6 * spr) : motor(6 * spl, -6 * spr);
        while (sensor_value[3] == 0 && sensor_value[4] == 0) sensor_read();
        (flag == 'l') ? motor(10 * spl, -10 * spr) : motor(-10 * spl, 10 * spr);
        delay(50);
        flag = 's'; cross = 's'; pos = 0;//when you are done turning robot, make the flag to its normal state so that robot wont turn on its own when it finds no line without detecting 90degree logic
      }
      else if (pos > -3 && pos < 3) {                                                                              //U turn
        m2 = millis();                                                                                   //U turn
        while (sum == 0) {                                                                               //U turn
          sensor_read();                                                                                 //U turn
          if (millis() - m2 > u_turn_delay4advanc) {                                                            //U turn
            motor(0, 0); delay(100);                                                                     //U turn
//            show_the_value();
//            Serial.println("_______U END_______");
            (side == 'l') ? motor(-6 * spl, 6 * spr) : motor(6 * spl, -6 * spr);         //U turn
            while (sensor_value[3] == 0 && sensor_value[4] == 0) sensor_read();                          //U turn
            (side == 'l') ? motor(10 * spl, -10 * spr) : motor(-10 * spl, 10 * spr);     //U turn
            delay(50);                                                                                   //U turn
            pos = 0; break;                                                                                      //U turn
          }
        }
      }
    }
    else if (sum == 1 || sum == 2 || decimal == 0b11100000 || decimal == 0b01110000 || decimal == 0b00111000 || decimal == 0b00011100 || decimal == 0b00001110 || decimal == 0b00000111) { //only for straight line
      if (cross != 's') {
//        show_the_value();
//        Serial.println("_______S END_______");
        (cross == 'l') ? motor(-6 * spl, 6 * spr) : motor(6 * spl, -6 * spr);
        while (sensor_value[7] + sensor_value[6] + sensor_value[5] + sensor_value[4] + sensor_value[3] + sensor_value[2] + sensor_value[1] > 0) sensor_read();
        while (sensor_value[3] == 0 && sensor_value[4] == 0) sensor_read();
        (cross == 'l') ? motor(10 * spl, -10 * spr) : motor(-10 * spl, 10 * spr);
        delay(50);
        cross = 's'; flag = 's'; pos = 0;
      }
      normal_line();
    }

    //________________left,right,left-forward,right-forward turn____________
    else if (sum == 3 || sum == 4 || sum == 5 || sum == 6 || sum == 7) {
      if (sensor_value[7] + sensor_value[6] > 0 && sensor_value[0] == 0 && sensor_value[3] + sensor_value[4] > 0) {             //_________90 degree left detection logic___________
        flag = 'l';                                                                                                             //_________90 degree left detected___________
        while (sensor_value[7] + sensor_value[6] > 0 && sensor_value[0] == 0) sensor_read();                                    //_________90 degree left and forward detection logic___________
        if (sensor_value[0] == 0) {                                                                                             //_________90 degree left and forward detection logic___________
          delay(node_delay4advanc);                                                                                                    //_________90 degree left and forward detection logic___________
          sensor_read();                                                                                                        //_________90 degree left and forward detection logic___________
          if (sum != 0) if (side == 'l') cross = 'l';                                                                           //_________90 degree left and forward detected___________
        }
      }

      else if (sensor_value[7] == 0 && sensor_value[0] + sensor_value[1] > 0 && sensor_value[3] + sensor_value[4] > 0) {        //_________90 degree right detection logic___________
        flag = 'r';                                                                                                             //_________90 degree right detected___________
        while (sensor_value[7] == 0 && sensor_value[0] + sensor_value[1] > 0) sensor_read();                                    //_________90 degree right and forward detection logic___________
        if (sensor_value[7] == 0) {                                                                                             //_________90 degree right and forward detection logic___________
          delay(node_delay4advanc);                                                                                                    //_________90 degree right and forward detection logic___________
          sensor_read();                                                                                                        //_________90 degree right and forward detection logic___________
          if (sum != 0) if (side == 'r') cross = 'r';                                                                           //_________90 degree right and forward detected___________
        }
      }
      m1 = millis();
    }

    //________________stop,T section,cross section____________
    else if (sum == 8) {
      flag = side;
      m2 = millis();
      while (sensor_value[7] + sensor_value[6] + sensor_value[5] > 0 || sensor_value[0] + sensor_value[1] + sensor_value[2] > 0) {    //________________________stop point logic________________________
        sensor_read();                                                                                                                //________________________stop point logic________________________
        if (millis() - m2 > stop_timer4advanc) {                                                                                             //________________________stop point logic________________________
          motor(0, 0);                                                                                                                //________________________stop point logic________________________
          while (sum == 8) sensor_read();                                                                                             //________________________stop point logic________________________
          goto a;                                                                                                                     //________________________stop point logic________________________
        }
      }
      delay(node_delay4advanc);                                                                                                              //________________________T and cross section logic________________________
      sensor_read();                                                                                                                  //________________________T and cross section logic________________________
      if (sum != 0) cross = side;                                                                                                     //________________________if sum =0 than T, else cross section detected________________________
      m1 = millis();
    }
    if (millis() - m1 > 500) flag = 's';
  }
}



void normal_line() {
  if (decimal == 0b00011000) {
    if (pos != 0) {
      (pos > 0) ? motor(-10 * spl, 10 * spr) : motor(10 * spl, -10 * spr);
      (pos > 0) ? delay(pos * 4) : delay(-pos * 4); pos = 0; //this logic is for those whose bot is wabbling during high speed run. this logic will forcefully return bot to its midpoint. don't give more than 30ms delay here!
    }
    motor(10 * spl, 10 * spr);
  }
  //right side portion
  else if (decimal == 0b00001000) motor(10 * spl, 9 * spr);
  else if (decimal == 0b00001100) {
    if (pos < 1) pos = 1; motor(10 * spl, 6 * spr);
  }
  else if (decimal == 0b00000100) {
    if (pos < 2) pos = 2; motor(10 * spl, 3 * spr);
  }
  else if (decimal == 0b00000110) {
    if (pos < 3) pos = 3; motor(10 * spl, 0 * spr);
  }
  else if (decimal == 0b00000010) {
    if (pos < 4) pos = 4; motor(10 * spl, -3 * spr);
  }
  else if (decimal == 0b00000011) {
    if (pos < 5) pos = 5; motor(10 * spl, -6 * spr);
  }
  else if (decimal == 0b00000001) {
    if (pos < 6) pos = 6; motor(10 * spl, -9 * spr);
  }
  //left side portion
  else if (decimal == 0b00010000) motor(9 * spl, 10 * spr);
  else if (decimal == 0b00110000) {
    if (pos > -1) pos = -1; motor(6 * spl, 10 * spr);
  }
  else if (decimal == 0b00100000) {
    if (pos > -2) pos = -2; motor(3 * spl, 10 * spr);
  }
  else if (decimal == 0b01100000) {
    if (pos > -3) pos = -3; motor(0 * spl, 10 * spr);
  }
  else if (decimal == 0b01000000) {
    if (pos > -4) pos = -4; motor(-3 * spl, 10 * spr);
  }
  else if (decimal == 0b11000000) {
    if (pos > -5) pos = -5; motor(-6 * spl, 10 * spr);
  }
  else if (decimal == 0b10000000) {
    if (pos > -6) pos = -6; motor(-9 * spl, 10 * spr);
  }
    threeSensor();
}
void threeSensor() {
  //right side portion
  if (decimal == 0b00011100) motor(10 * spl, 8 * spr);
  else if (decimal == 0b00001110) {
    if (pos < 1) pos = 2; motor(10 * spl, 5 * spr);
  }
  else if (decimal == 0b00000111) {
    if (pos < 2) pos = 3; motor(10 * spl, 2 * spr);
  }
  //left side portion
  else if (decimal == 0b00111000) motor(8 * spl, 10 * spr);
  else if (decimal == 0b01110000) {
    if (pos > -1) pos = -2; motor(5 * spl, 10 * spr);
  }
  else if (decimal == 0b11100000) {
    if (pos > -2) pos = -3; motor(2 * spl, 10 * spr);
  }
}
