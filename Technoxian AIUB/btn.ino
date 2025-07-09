//____________________Create button reading function____________________
int button_read() {
  int count = 0;
p:  int t = 0;
  if (digitalRead(switch_pin) == 0) {
    digitalWrite(light_pin, HIGH);
    while (digitalRead(switch_pin) == 0) {
      delay(1); t++;
    }
    digitalWrite(light_pin, LOW);
    if (t > 15) {
     count++;
     t=0;
      while (digitalRead(switch_pin) == HIGH) {
        delay(1); t++;
        if (t > 1000) return count;
      }
      goto p;
    }
  }
  return count;
}
