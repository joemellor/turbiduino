

void pulse_media() {
    digitalWrite(pump_control_pin, HIGH);
    delay(110);
    digitalWrite(pump_control_pin, LOW);
    Serial.println("Pulse!");
    pump_counter++; 
    current_doubling = pump_counter * 0.015;
    pump_cycle = millis();
    //tweet();
}

