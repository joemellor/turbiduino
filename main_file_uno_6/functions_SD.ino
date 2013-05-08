

//float temps[12];
unsigned long temp_cycle = 0;

void get_avg_temp() {
  if (millis() - temp_cycle > 1000) {
  digitalWrite(heat_control_pin, LOW);
  analogReference(INTERNAL);
  analogRead(0);
  delay(5);
  //float tempAvg = 0.0;
  float reading = analogRead(0);
  temp = reading / 9.31;
  //Serial.print(temp); Serial.println(" degrees C");
  analogReference(DEFAULT);
  if (temp > 30.0) {
    digitalWrite(heat_control_pin, LOW);  }
  else { digitalWrite(heat_control_pin, HIGH); }
  temp_cycle = millis(); }
}
