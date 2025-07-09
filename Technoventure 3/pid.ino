
//__________or_____________
//kp = 1, kd = 40;  //pid parameter ,need to be adjust
//float P, D;
//int MAX_SPEED = 250, MIN_SPEED = -150, SET_SPEED = 250, SET_POINT = 450;
//int prevError = 0;
//int error, linePos = 0, sumWS = 0;;
//int delSpeed = 0;
//int Weight[8] = {100, 200, 300, 400, 500, 600, 700, 800};
//int Lspeed, Rspeed;
void pid() {

  sumWS = 0;
  //  sensor_read();
  //_______________________-calculate error____________________
  for (int i = 0; i <= 7; i++) {                 //------------------------------------------
    sumWS += sensor_value[i] * Weight[i];        //---------calculate sum * Weight-----------
  }                                              //------------------------------------------
  if (sum != 0) linePos = sumWS / sum;           //---------calculate line Position-----------
  error = linePos - SET_POINT;
  //normal line follow
  P = kp * error;
  D = kd * (error - prevError);
  delSpeed = P + D;
  Lspeed = SET_SPEED - delSpeed;
  Rspeed = SET_SPEED + delSpeed;
  Lspeed = constrain(Lspeed, MIN_SPEED, MAX_SPEED);
  Rspeed = constrain(Rspeed, MIN_SPEED, MAX_SPEED);
  motor(Lspeed, Rspeed);//setting motor speed
  prevError = error;
}
