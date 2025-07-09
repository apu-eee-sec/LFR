int btn_index,bot_index=0,btn_flag,prev_index;
bool manual_skip=false;
char fix_flag;
void manual_setup(){
  delay(20);
  Serial.print("Enter the index: ");
  while((btn_index=button_read())==0){}
  Serial.println(btn_index);
  a:Serial.print("Enter the flag(l=1,s=2,r=3): ");
  while((btn_flag=button_read())==0){}
  if(btn_flag==1) fix_flag='l';
  else if(btn_flag==2) fix_flag='s';
  else if(btn_flag==3) fix_flag='r';
  else{
    Serial.println("Invalid Input");
    goto a;
  }
  Serial.println(fix_flag);
  manual_skip=true;
}
void run_manual_skip(){
  if(manual_skip==true){
    if(flag!='s'||cross!='s'){
      bot_index++;
      Serial.println(bot_index);
    }
    if(bot_index==btn_index){
      flag=fix_flag;
      cross=fix_flag;Serial.println("finish");
      manual_skip=false;
    }
  }
}
