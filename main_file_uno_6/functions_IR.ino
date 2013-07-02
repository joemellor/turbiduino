/*Switches the IRLED on and takes three quick readings using the
photodiode which are then averaged. */
void IR_onpulse() {
  digitalWrite(pinch_control_pin, LOW); //pinch the valve (prevent bubbles)
  delay(1000);
  digitalWrite(IRLED, HIGH); 
  Serial.print("IRLED ON: ");
  reading1 = analogRead(2);
  delay(100);
  reading1 = reading1 + analogRead(2);
  delay(100);
  reading1 = reading1 + analogRead(2);
  reading1 = reading1 / 3;
  Serial.print(reading1);
  Serial.print(" , ");  }
  

/*Switches the IRLED off, takes a photodiode reading, and stores
it in a global variable. */
void IR_offpulse() {
  digitalWrite(IRLED, LOW);
  delay(1000);
  Serial.print("IRLED OFF: ");
  reading2 = analogRead(2);
  Serial.println(reading2);
  digitalWrite(pinch_control_pin, HIGH); //open the valve 
}


/* Follows a very similar procudure to the 'IR_onpulse' function
to store a baseline OD. Averages 5 readings instead of 3. */
void set_baseline() {
  digitalWrite(pinch_control_pin, LOW);
  delay(2000);
  digitalWrite(heat_control_pin, HIGH);
  digitalWrite(IRLED, HIGH);
  int sum = 0;
  for (int i = 0; i < 5; i++) {
    sum = sum + analogRead(2);
    delay(200); }
  initial_reading = sum/5;
  digitalWrite(IRLED, LOW);
  digitalWrite(pinch_control_pin, HIGH);
  delay(10000); //a delay to allow the entire system to normalize.
}
