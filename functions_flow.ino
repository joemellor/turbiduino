

void pulse_media() {
    digitalWrite(pump_control_pin, HIGH);
    delay(110);
    digitalWrite(pump_control_pin, LOW);
    Serial.println("Pulse!");
    pump_counter++; 
    pump_cycle = millis();
    //tweet();
}



