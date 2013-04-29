int reads[5];

void IR_onpulse() {
  digitalWrite(pinch_control_pin, LOW); //pinch the valve
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
  
void IR_offpulse() {
  digitalWrite(IRLED, LOW);
  delay(1000);
  Serial.print("IRLED OFF: ");
  reading2 = analogRead(2);
  Serial.println(reading2);
  digitalWrite(pinch_control_pin, HIGH); //open the valve 
}

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
  delay(10000);
}
