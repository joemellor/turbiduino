#include <SPI.h>
#include <WiFi.h>
  
char ssid[] = "RothLab";   
char pass[] = "lamarama"; 
int status = WL_IDLE_STATUS;
IPAddress server(142,150,68,220);  
WiFiClient client;
  
/* The UNO and the Wifi shield communicate using pins 11,12,13,10,
4, 7. Do not use these pins for general I/O. Pin 4 is needed for
SD functionality. */
const int IRLED = 9;
const int heat_control_pin = 5;
const int pump_control_pin = 6;
const int pinch_control_pin = 8;
const int autosampler_pin = 4;
const int autosampler_divert_pin = 3;

//initializing global variables
int reading1;
int reading2;
int initial_reading;
float temp;
unsigned long IR_cycle = 0;
unsigned long pump_cycle = 0;
unsigned long timer = 0;
unsigned long secondcounter = 0;
int pump_counter = 0;
int current_doubling = 0;
int last_doubling = 0;

//database variables
char runID[13];

void setup()
{ Serial.begin(9600);

//initializaing arduino pins.
  pinMode(IRLED, OUTPUT);
  pinMode(heat_control_pin, OUTPUT);
  pinMode(pump_control_pin, OUTPUT);
  pinMode(pinch_control_pin, OUTPUT);
  pinMode(autosampler_pin, OUTPUT);
  pinMode(autosampler_divert_pin, OUTPUT);
  digitalWrite(pinch_control_pin, HIGH);
  digitalWrite(pump_control_pin, LOW);
  
// start the server
  connect_to_wifi();
  //this line will not appear on the serial monitor if the 
  //sketch is too large.
  Serial.println("initializing...");
  getRunID();
  

  //records the initial OD to mantain the culture at.
  set_baseline();
  digitalWrite(autosampler_pin, LOW);
  Serial.println(initial_reading);
  take_sample();
}

void loop() {
    //if the run is underway, measure OD every 30 seconds.  
    if (millis() - IR_cycle > 30000) {
      logData();      //sends data to database.
      if (status != WL_CONNECTED) { connect_to_wifi(); }
      IR_onpulse();
      IR_offpulse();
      IR_cycle = millis();
      //limit pumping to every 60 seconds max
      if (reading1 - initial_reading > 5 && millis() - pump_cycle > 60000) {
        pulse_media();
      }
      //adjusts the heaters by getting ambient temperature.
      get_avg_temp();
      if (current_doubling != last_doubling) {
        take_sample(); }
    }
    if (millis() - secondcounter > 1000) {
      secondcounter = millis();
      timer++;
     }      
}

void take_sample() {
  digitalWrite(autosampler_pin, HIGH);
  digitalWrite(autosampler_divert_pin, HIGH);
  last_doubling = current_doubling;
  for (int i = 0; i < 8; i++) {
    digitalWrite(pinch_control_pin, LOW); //close the valve 
    pulse_media();
    delay(6000);
    digitalWrite(pinch_control_pin, HIGH); //open the valve
    delay(25000); 
    }
  digitalWrite(autosampler_divert_pin, LOW);
  digitalWrite(autosampler_pin, LOW);
}

