unsigned long temp_cycle = 0;


/*checks the temperature every second and switches the heaters on
or off accordingle to mantain the temp at 30 degrees. */
void get_avg_temp() {
  if (millis() - temp_cycle > 1000) {
  //switch off the heat and change the reference voltage for a
  //more accurate temperature read.
  digitalWrite(heat_control_pin, LOW);
  analogReference(INTERNAL);
  analogRead(0);
  delay(5);
  //float tempAvg = 0.0;
  float reading = analogRead(0);
  temp = reading / 9.31; //formula for LM38 when reference altered.
  analogReference(DEFAULT);
  //switch off the heaters if the temp is above 30 and vice-versa.
  if (temp > 30.0) {
    digitalWrite(heat_control_pin, LOW);  }
  else { digitalWrite(heat_control_pin, HIGH); }
  temp_cycle = millis(); }
}
