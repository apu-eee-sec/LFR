void turn(){
  (flag == 'l') ? motor(-6 * spl, 6 * spr) : motor(6 * spl, -6 * spr);
  while (s[2] == 0 && s[3] == 0) reading();

  (flag == 'l') ? motor(10 * spl, -10 * spr) : motor(-10 * spl, 10 * spr);
  delay(node_bari_delay);

  flag = 's'; cross = 's'; pos = 0; //when you are done turning robot, make the flag to its normal state so that robot wont turn on its own when it finds no line without detecting 90degree logic    
}


void uturn_or_not(){
  m2 = millis();
  while (sum == 0) {
    reading();
    if (millis() - m2 > u_turn_delay) {
      motor(0, 0); delay(100);
      (side == 'l') ? motor(-6 * spl, 6 * spr) : motor(6 * spl, -6 * spr);
      while (s[2] == 0 && s[3] == 0) reading();

      (side == 'l') ? motor(10 * spl, -10 * spr) : motor(-10 * spl, 10 * spr);
      delay(u_bari_delay);

      pos = 0; break;
    }
  }
}


void cross_or_L(){
  (cross == 'l') ? motor(-6 * spl, 6 * spr) : motor(6 * spl, -6 * spr);
  while (s[4] + s[3] + s[2] + s[1] > 0) reading();
  while (s[2] == 0 && s[3] == 0) reading();

  (cross == 'l') ? motor(10 * spl, -10 * spr) : motor(-10 * spl, 10 * spr);
  delay(node_bari_delay);

  cross = 's'; flag = 's'; pos = 0;
}


void s_bari(){
  (pos > 0) ? motor(-10 * spl, 10 * spr) : motor(10 * spl, -10 * spr);
  (pos > 0) ? delay(pos * 5) : delay(-pos * 5); pos = 0; //this logic is for those whose bot is wabbling during high speed run. this logic will forcefully return bot to its midpoint. don't give more than 30ms delay here! 
}


void stay_straight(){
  if (sensor == 0b000100)      {motor(10*spl,9*spr);}
  else if (sensor == 0b000110) {motor(10*spl,6*spr);   if(pos<1)pos=1;}
  else if (sensor == 0b000010) {motor(10*spl,3*spr);   if(pos<2)pos=2;}
  else if (sensor == 0b000011) {motor(10*spl,0*spr);   if(pos<3)pos=3;}
  else if (sensor == 0b000001) {motor(10*spl,-3*spr);  if(pos<4)pos=4;}
  
  else if (sensor == 0b001000) {motor(9*spl,10*spr);}
  else if (sensor == 0b011000) {motor(6*spl,10*spr);   if(pos>-1)pos=-1;}
  else if (sensor == 0b010000) {motor(3*spl,10*spr);   if(pos>-2)pos=-2;}
  else if (sensor == 0b110000) {motor(0*spl,10*spr);   if(pos>-3)pos=-3;}
  else if (sensor == 0b100000) {motor(-3*spl,10*spr);  if(pos>-4)pos=-4;}
}

