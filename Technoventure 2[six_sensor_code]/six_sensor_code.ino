#include<EEPROM.h>
#define left_motor_forward 6
#define left_motor_backward 7
#define right_motor_forward 10
#define right_motor_backward 9
#define left_motor_speed 5
#define right_motor_speed 11
#define light 13
#define spl 20 //left motor speed coeficient
#define spr 20 //right motor speed coeficient
#define sw 12
#define node_delay 25
#define stop_timer 80
#define u_turn_delay 180

#define node_bari_delay 50
#define u_bari_delay 70

char side = 'l';
char flag = 's';
int pos;
char cross = 's';

uint32_t m1, m2;

int s[6];
int mid[6], maximum[6], minimum[6];
int base[6] = {1, 2, 4, 8, 16, 32}; //this is for binary to decimal conversion
int sensor; //this is to store final value after binary conversion
int sum = 0; //this is to store the count of detected sensor

void setup() {
  pinMode(left_motor_forward, OUTPUT);
  pinMode(left_motor_backward, OUTPUT);
  pinMode(left_motor_speed, OUTPUT);
  pinMode(right_motor_forward, OUTPUT);
  pinMode(right_motor_backward, OUTPUT);
  pinMode(right_motor_speed, OUTPUT);
  pinMode(light, OUTPUT);
  pinMode(sw, INPUT_PULLUP);
  Serial.begin(9600);
  for (int i = 0; i < 6; i++) {
    mid[i] = EEPROM.read(i) * 4;
    maximum[i] = EEPROM.read(i + 6) * 4;
    minimum[i] = EEPROM.read(i + 12) * 4;
    Serial.println(String(maximum[i]) + " " + String(mid[i]) + " " + String(minimum[i]));
  }
}

void loop() {
  int r = button_read();
  if (r == 1) line_follow();
  else if (r == 2) cal();
  else if (r == 3) side = 'r';
  else if (r == 3) motor(10 * spl, 10 * spr); //to test out if the robot is moving perfectly straight forward
}
