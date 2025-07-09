//bool isNotInverted = true;
//uint32_t m3 = 0;
//void sensor_read(){
//  decimal=0;
//  sum=0;
//
//  if(isNotInverted) {
//    for(int i=0; i<8; i++){
//      (analogRead(i)>mid[i]) ? sensor_value[i]=1 : sensor_value[i]=0;
//      decimal += sensor_value[i]*base[i];
//      sum += sensor_value[i];
//    }
//  }
//  else {
//    for(int i=0; i<8; i++){
//      (analogRead(i)>mid[i]) ? sensor_value[i]=0 : sensor_value[i]=1;
//      decimal += sensor_value[i]*base[i];
//      sum += sensor_value[i];
//    }
//  }
//
//  if (invertUsed)invert_mech();
//}
//
//void invert_mech(){
//  if(sensor_value[7]+sensor_value[6]+sensor_value[5]>=2  && sensor_value[3]+sensor_value[4]<=1 && sensor_value[2]+sensor_value[1]+sensor_value[0]>=2) {
//    while (sensor_value[7]+sensor_value[6]+sensor_value[5]>=2  && sensor_value[3]+sensor_value[4]<=1 && sensor_value[2]+sensor_value[1]+sensor_value[0]>=2){
//
//      m3= millis();
//      if(isNotInverted) {
//      for(int i=0; i<8; i++){
//          (analogRead(i)>mid[i]) ? sensor_value[i]=1 : sensor_value[i]=0;
//          decimal += sensor_value[i]*base[i];
//          sum += sensor_value[i];
//        }
//      }
//      else {
//        for(int i=0; i<8; i++){
//          (analogRead(i)>mid[i]) ? sensor_value[i]=0 : sensor_value[i]=1;
//          decimal += sensor_value[i]*base[i];
//          sum += sensor_value[i];
//        }
//      }
//
//      if (millis()-m3 > 200) {
//        flag='s';cross='s';
//        (isNotInverted) ? isNotInverted=false : isNotInverted=true;
//        for(int i=0; i<8; i++) {
//          (sensor_value[i]==1) ? sensor_value[i]=0 : sensor_value[i]=1;
//        }
//      }
//    }
//  }
//}
