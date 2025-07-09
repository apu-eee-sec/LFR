float l=1,r=1;
//____________________Create motor movement function____________________
void motor(int a,int b){
  if (a>=0){
    digitalWrite(left_motor_forward_pin,1);
    digitalWrite(left_motor_backward_pin,0);
  }
  else{
    a=-a;
    digitalWrite(left_motor_forward_pin,0);
    digitalWrite(left_motor_backward_pin,1);
  }
  if (b>=0){
    digitalWrite(right_motor_forward_pin,1);
    digitalWrite(right_motor_backward_pin,0);
  }
  else{
    b=-b;
    digitalWrite(right_motor_forward_pin,0);
    digitalWrite(right_motor_backward_pin,1);
  }
  a=a*l;
  b=b*r;
  analogWrite(left_motor_speed_pin,a);
  analogWrite(right_motor_speed_pin,b);
}
void motor_coff(){
  Serial.print("Enter left motor coffecient: ");
  while(Serial.available()==0){}
  l=Serial.parseFloat();
  Serial.println(l);
  if (Serial.readStringUntil('\n') == "") {} //clearing buffer
  Serial.print("Enter right motor coffecient: ");
  while(Serial.available()==0){}
  r=Serial.parseFloat();
  Serial.println(r);
  if (Serial.readStringUntil('\n') == "") {} //clearing buffer
}
