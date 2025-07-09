void red(){
  digitalWrite(light_pin2,1);
}
void green(){
  digitalWrite(light_pin,1);
}
void yellow(){
  digitalWrite(light_pin,1);
  digitalWrite(light_pin2,1);
}
void stopLight(){
  digitalWrite(light_pin,0);
  digitalWrite(light_pin2,0);
}
