/*
 * node delay start from 20 an increment is 5
 * kp start from 0 an increment is 0.5
 * kd start from 0 an increment is 10
 */
byte btn2;
void set_delay() {
  delay(20);
  Serial.print("Enter node delay: ");
  while ((btn2 = button_read()) == 0) {}
  EEPROM.write(100, 20 + 5 * btn2); delay(10);
}
void set_k() {
  delay(20);
  Serial.print("Enter kp: ");
  while ((btn2 = button_read()) == 0) {}
  EEPROM.put(101, 0.5 * btn2); delay(20);
  Serial.print("Enter kd: ");
  while ((btn2 = button_read()) == 0) {}
  EEPROM.put(105, 10 * btn2); delay(10);
}

void get_kpkd_node_delay() {
  node_delay = EEPROM.read(100);
  Serial.println("node delay: " + String(node_delay));
  EEPROM.get(101, kp); delay(20);
  Serial.println("kp: " + String(kp));
  EEPROM.get(105, kd); delay(20);
  Serial.println("kd: " + String(kd));
}

































//#include <pidautotuner.h>
//double output;
//byte loopInterval = 1;
//int errora, linePosa = 0, sumWSa = 0;
//int Weighta[8] = {100, 200, 300, 400, 500, 600,700,800};
//void autotune() {
//
//  PIDAutotuner tuner = PIDAutotuner();
//
//  // Set the target value to tune to
//  // This will depend on what you are tuning. This should be set to a value within
//  // the usual range of the setpoint. For low-inertia systems, values at the lower
//  // end of this range usually give better results. For anything else, start with a
//  // value at the middle of the range.
//  tuner.setTargetInputValue(0);
//
//  // Set the loop interval in microseconds
//  // This must be the same as the interval the PID control loop will run at
//  tuner.setLoopInterval(loopInterval);
//  tuner.setTuningCycles(20);
//
//  // Set the output range
//  // These are the minimum and maximum possible output values of whatever you are
//  // using to control the system (Arduino analogWrite, for example, is 0-255)
//  tuner.setOutputRange(0, 200);
//
//  // Set the Ziegler-Nichols tuning mode
//  // Set it to either PIDAutotuner::ZNModeBasicPID, PIDAutotuner::ZNModeLessOvershoot,
//  // or PIDAutotuner::ZNModeNoOvershoot. Defaults to ZNModeNoOvershoot as it is the
//  // safest option.
//  tuner.setZNMode(PIDAutotuner::ZNModeBasicPID);
//
//  // This must be called immediately before the tuning loop
//  // Must be called with the current time in microseconds
//  tuner.startTuningLoop(micros());
//
//  // Run a loop until tuner.isFinished() returns true
//  long microseconds;
//  while (!tuner.isFinished()) {
//
//    // This loop must run at the same speed as the PID control loop being tuned
//    long prevMicroseconds = microseconds;
//    microseconds = micros();
//
//    sensor_read();
//    sumWSa = 0;
//    for (int i = 0; i <= 7; i++) {                   //------------------------------------------
//      sumWSa += sensor_value[i] * Weighta[i];        //---------calculate sum * Weight-----------
//    }                                                //------------------------------------------
//    if (sum != 0) linePosa = sumWSa / sum;           //---------calculate line Position-----------
//
//    errora = linePosa - 450;
//    // Get input value here (temperature, encoder position, velocity, etc)
//    double input = errora;
//
//    // Call tunePID() with the input value and current time in microseconds
//    output = tuner.tunePID(input, microseconds);
//    //        Serial.print(output);
//    // Set the output - tunePid() will return values within the range configured
//    // by setOutputRange(). Don't change the value or the tuning results will be
//    // incorrect.
//    motor(200 - output, 200 + output); //setting motor speed
//    //        Serial.println(!tuner.isFinished());
//
//    // This loop must run at the same speed as the PID control loop being tuned
//    while (micros() - microseconds < loopInterval) {
//      delayMicroseconds(1);
//      Serial.print(micros() - microseconds);
//      Serial.print(" ");
//      Serial.print(!tuner.isFinished());
//    }
//  }
//
//  // Turn the output off here.
//  motor(0, 0); //setting motor speed
//  Serial.println("finish");
//
//  // Get PID gains - set your PID controller's gains to these
//  Serial.print(tuner.getKp());
//  Serial.print(" ");
//  Serial.print(tuner.getKi());
//  Serial.print(" ");
//  Serial.print(tuner.getKd());
//}
