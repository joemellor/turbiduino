

void pulse_media() {
    digitalWrite(pinch_control_pin, LOW);
    digitalWrite(pump_control_pin, HIGH);
    delay(110);
    digitalWrite(pump_control_pin, LOW);
    Serial.println("Pulse!");
    pump_counter++; 
    current_doubling = pump_counter * 0.03;
    pump_cycle = millis();
    delay(5000);
    digitalWrite(pinch_control_pin, HIGH);
}

