void pid_setup() {
  Serial.print("Enter value Kp:");
  while (Serial.available() == 0) {}
  kp = Serial.parseFloat();
  Serial.println(kp);
  if (Serial.readStringUntil('\n') == "") {} //clearing buffer
  Serial.print("Enter value Kd:");
  while (Serial.available() == 0) {}
  kd = Serial.parseFloat();
  Serial.println(kd);
  if (Serial.readStringUntil('\n') == "") {} //clearing buffer
}
