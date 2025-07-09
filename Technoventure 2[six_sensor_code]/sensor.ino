void reading(){
  sensor=0;
  sum=0;
  for(int i=0;i<6;i++){
    s[i]=analogRead(i);
    (s[i]>mid[i])?s[i]=1:s[i]=0;
    sensor+=s[i]*base[i];
    sum+=s[i];
  }
}

void cal() {
  for(int i=0;i<6;i++){
    maximum[i]=0;
    minimum[i]=1024;
  }
  motor(10*spl,-10*spr);
  for(int i=0;i<5000;i++){
    for(int i=0;i<6;i++){
      s[i]=analogRead(i);
      maximum[i]=max(maximum[i],s[i]);
      minimum[i]=min(minimum[i],s[i]);
      
    }
  }
  motor(0,0);
  for(int i=0; i<6; i++){
   mid[i] = (maximum[i]+minimum[i])/2;
    EEPROM.write(i,mid[i]/4);
    delay(10);
    EEPROM.write(i+6,maximum[i]/4);
    delay(10);
    EEPROM.write(i+12,minimum[i]/4);
  }
}




void analog_reading() {
  while (1) {
    for (int i = 5 ; i >=0 ; i--) {
      s[i] = analogRead(i);
      Serial.print(String(s[i]) + " ");
    }
    Serial.println();
  }
}

void digital_reading() {
  while (1) {
    reading();
    for (int i = 5 ; i >= 0 ; i--)
      Serial.print(String(s[i]) + " ");
    Serial.println(sensor);
  }
}
