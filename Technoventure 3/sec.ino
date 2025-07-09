#include <EEPROM.h>
bool invertUsed = false;
//________________Define sensor pins____________
byte sensor_pin[8] = { A0, A1, A2, A3, A4, A5, A6, A7 };
//_____________variable for line follow______________
uint32_t m1, m2,y;
char flag = 's';
char cross = 's';                               // for detec angle t,T,+
char side = 'l';                                // for left hand rule or right hand rule
int sensor_value[8];                            //store sensor analog read value
int sum = 0;                                    //store total sensor in black line
int decimal;                                    //store sensor analog read value in decimal
int maximum[8], minimum[8], mid[8];             //store sensor analog read  maximum , minimum and mid value
int base[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };  //for convert bin to dec
// float kp = 1.01, kd = 48860.51;  //pid parameter ,need to be adjust 1.68 100
float P, D;
int MAX_SPEED = 255, MIN_SPEED = -255, SET_SPEED = 255, SET_POINT = 450;
float prevError = 0;
int sumWS = 0;
;
float delSpeed = 0, error, linePos = 0;
int Weight[8] = { 100, 200, 300, 400, 500, 600, 700, 800 };
int Lspeed, Rspeed;
// // //___________AllSpark pin_____________
#define left_motor_forward_pin 7
#define left_motor_backward_pin 6
#define left_motor_speed_pin 5
#define right_motor_forward_pin 9
#define right_motor_backward_pin 10
#define right_motor_speed_pin 11
// float kp = 1.01, kd = 248860.51;  //tis
float kp = 1, kd = 40;  //pid parameter ,need to be adjust 1.68 100
//
// //___________Qubit pin_____________
// #define left_motor_forward_pin 6
// #define left_motor_backward_pin 7
// #define left_motor_speed_pin 5
// #define right_motor_forward_pin 10
// #define right_motor_backward_pin 9
// #define right_motor_speed_pin 11
// float kp = 1.01, kd = 248860.51;  //tis
//________________Define button pins____________
#define light_pin 13
#define light_pin2 3
#define switch_pin 12

#define turnspeed 100     //turning speed<=125 (max)                        ----------------------------------------------
#define u_turn_delay 150  //delay for u turn                                    Adjust this value to get perfact result
int node_delay =20;     //to make perfact 90 degree turn                    ----------------------------------------------
int stop_timer =20;     // stop delay if find end point                     ----------------------------------------------
#define bari_speed 150
#define bari_time 40
void setup() {
  // put your setup code here, to run once:
  pinMode(switch_pin, INPUT_PULLUP);  //Switch pinMode
  pinMode(light_pin, OUTPUT);         //Light pinMode
  pinMode(light_pin2, OUTPUT);        //Light pinMode
  // _____motor pinMode_______
  pinMode(left_motor_forward_pin, OUTPUT);
  pinMode(left_motor_backward_pin, OUTPUT);
  pinMode(left_motor_speed_pin, OUTPUT);
  pinMode(right_motor_forward_pin, OUTPUT);
  pinMode(right_motor_backward_pin, OUTPUT);
  pinMode(right_motor_speed_pin, OUTPUT);
  Serial.begin(9600);

  for (int i = 0; i < 8; i++) {
    mid[i] = EEPROM.read(i) * 4;
    maximum[i] = EEPROM.read(i + 8) * 4;
    minimum[i] = EEPROM.read(i + 16) * 4;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int btn_press = button_read();
  // if (btn_press == 1) {
  //   while ((btn_press = button_read()) == 0) {}
  //   if (btn_press == 1) {
  //     side = 'l';
  //     pid_line_follow();
  //   }
  //   else if (btn_press == 2) {
  //     side = 'r';
  //     pid_line_follow();
  //   }
  //   else if (btn_press == 3) {
  //     invertUsed = true;
  //     side = 'l';
  //     pid_line_follow();
  //   }
  //   else if (btn_press == 4) {
  //     invertUsed = true;
  //     side = 'r';
  //     pid_line_follow();
  //   }
  // }

  if (btn_press == 1) {
    invertUsed = true;
    side = 'l';
    pid_line_follow();
  } else if (btn_press == 2) {
    invertUsed = true;
    side = 'r';
    pid_line_follow();
  } else if (btn_press == 3) {
    cal();
  } else if (btn_press == 12) {
    motor(250, 250);
    delay(1500);
    motor(0, 0);
  }
   else if (btn_press == 11) {
    motor(200, 200);
    delay(2000);
    motor(0, 0);
  } 
  else if (btn_press == 6) {
    while (1) {
      sensor_read();
      pid();
      Serial.println(error);
      if (sum == 0) {
        motor(0, 0);
        break;
      }
    }
  } else if (btn_press == 7) {
    while (button_read() == 0) {
      sensor_read();
      show_the_value();
    }
  } else if (btn_press == 8) {
    while (button_read() == 0) {
      show_analog();
    }
  } else if (btn_press == 9) {
    pid_setup();
  } else if (btn_press == 5) {
    motor_coff();
  }
  else if (btn_press == 4) {
    uturnDealay();
  }
}
