const int collector = 4;

void setup() {
  pinMode(collector, OUTPUT);
}

void loop() {
  digitalWrite(collector, HIGH);
  delay(3000);
  digitalWrite(collector, LOW);
  delay(3000);
}

