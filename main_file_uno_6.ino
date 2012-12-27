#include <SPI.h>
#include <WiFi.h>
#include <SD.h>
  
char ssid[] = "RothLab";   
char pass[] = "lamarama"; 
int status = WL_IDLE_STATUS;
IPAddress server(142,150,68,220);  
//char server[] = "www.ferment.ccbr.utoronto.ca";
WiFiClient client;
  
//these pins will need to modified is the arduino uno is used.
const int IRLED = 9;
const int heat_control_pin = 5;
const int pump_control_pin = 6;
const int pinch_control_pin = 8;

//initializing global variables
int reading1;
int reading2;
int initial_reading;
int val = 1;
int Shutdown = 0;
float temp;
unsigned long IR_cycle = 0;
unsigned long pump_cycle = 0;
unsigned long tweet_cycle = millis();
unsigned long timer = 0;
unsigned long minutecounter = 0;
int pump_counter = 0;

//database variables
char runID[13];

void setup()
{ Serial.begin(9600);

// start the server
  while ( status != WL_CONNECTED) { 
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  status = WiFi.begin(ssid, pass);
  // wait 5 seconds for connection:
  delay(5000); }
  Serial.println(WiFi.localIP());
  SD.begin(4);
  //this line will not appear on the serial monitor if the sketch is too large.
  Serial.println("initializing...");
  getRunID();
  //if (client.connect(server, 80)) {
    //Serial.println("connected to server.");
    //client.println("GET /~jmellor/pub/turbidostat/test.php?time=5");
    //client.println(" HHTP/1.1\r\n");
    //client.println("Host: llama.mshri.on.ca");
    //client.println();
    //Serial.println("Sent a request"); 
  //}
  //wait 5 seconds before beggining.
  // start the server
  pinMode(IRLED, OUTPUT);
  pinMode(heat_control_pin, OUTPUT);
  pinMode(pump_control_pin, OUTPUT);
  pinMode(pinch_control_pin, OUTPUT);
  //initially adds the same amount of media as purge_volume to the culture chamber, comment out if unneeded.
  //purge();
  //records the initial OD to mantain the culture at.
  set_baseline();
  Serial.println(initial_reading);
}

void loop() {
  if (Shutdown == 0) {
    //if the run is underway, measure OD every 15 seconds.  
    if (millis() - IR_cycle > 15000) {
      logData();
      IR_onpulse();
      IR_offpulse();
      IR_cycle = millis();
      writeto_sd();
      //Serial.print(temp); 
      //Serial.println(" degrees C");
      //limit pumping to every 60 seconds max
      if (reading1 - initial_reading > 5 && millis() - pump_cycle > 60000) {
        pulse_media();
      }

      get_avg_temp();
      
      if (millis() - minutecounter > 60000) {
        minutecounter = millis();
        timer++;
      }      

    }
    //measure the culture temperature and adjust heaters every iteration.
    //if the OD has become too high and it has been 90 seconds since the last pulse, add media and record pulse time on the sd card.
  }
  //mantain the web interface.
  //webloop(temp, reading1, reading2); 
}

