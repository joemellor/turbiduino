/*Closes the pinch valve and sends a pulse of media to the culture
chamber. Updates pumping and doubling-related global variables. */
void pulse_media() {
    digitalWrite(pinch_control_pin, LOW);
    digitalWrite(pump_control_pin, HIGH);
    delay(110);
    digitalWrite(pump_control_pin, LOW);
    Serial.println("Pulse!");
    pump_counter++; 
    //value of 0.025 uses for pumps of 5ml with culture volume of 200ml
    current_doubling = pump_counter * 0.025;
    pump_cycle = millis();
    delay(5000);
    digitalWrite(pinch_control_pin, HIGH);
}

