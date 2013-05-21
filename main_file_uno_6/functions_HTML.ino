/*Uses the Arduino's wifi shield to connect to the specificed
wifi network. Opens pinch valve during this lengthy process.*/
void connect_to_wifi() {
  digitalWrite(pinch_control_pin, HIGH);
  while ( status != WL_CONNECTED) { 
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  status = WiFi.begin(ssid, pass);
  // wait 5 seconds for connection to fully resolve.
  delay(5000);
  Serial.println(WiFi.localIP()); }
}


/* Calls a script on the server to get the current date and time,
which is parsed and stored as a unique 'runID' */
void getRunID() {
  client.connect(server, 80);
  client.println("GET /turbiduino/date.php HTTP/1.1");
  client.println("Host: ferment.ccbr.utoronto.ca");
  client.println();
  //allocate memory for the runID variable and fill it up.
  memset(&runID, 0, 17);
  char c = client.read();
  while (c != '<') {
    c = client.read(); }
    for(int i = 0; i < 12; i++) {
    runID[i] = client.read(); }
  runID[12] = '\0';  //null-terminate the string
  
  client.stop();
  client.flush();
}


/* sends data about the current run to a server-side script using
a 'GET' method. */
void logData() {
  client.connect(server, 80);
  client.print("GET /turbiduino/update.php?runID=");
  Serial.println(runID);
  client.print(runID);
  client.print("&baseline=");
  client.print(initial_reading);
  client.print("&currentRead=");
  client.print(reading1);
  client.print("&maxRead=");
  client.print(reading2);
  client.print("&time=");
  client.print(timer);
  client.print("&doublings=");
  client.print(pump_counter);
  client.print("&temp=");
  client.print(temp);
  client.println(" HTTP/1.1");
  client.println("Host: ferment.ccbr.utoronto.ca");
  client.println();
}


/* a complicated although memory-efficient function that gives
the arduino float to String conversion. Taken from the forums. */
char * floatToString(char * outstr, double val, byte precision, byte widthp){
  char temp[16];
  byte i;

  // compute the rounding factor and fractional multiplier
  double roundingFactor = 0.5;
  unsigned long mult = 1;
  for (i = 0; i < precision; i++)
  {
    roundingFactor /= 10.0;
    mult *= 10;
  }
  
  temp[0]='\0';
  outstr[0]='\0';

  if(val < 0.0){
    strcpy(outstr,"-\0");
    val = -val;
  }

  val += roundingFactor;

  strcat(outstr, itoa(int(val),temp,10));  //prints the int part
  if( precision > 0) {
    strcat(outstr, ".\0"); // print the decimal point
    unsigned long frac;
    unsigned long mult = 1;
    byte padding = precision -1;
    while(precision--)
      mult *=10;

    if(val >= 0)
      frac = (val - int(val)) * mult;
    else
      frac = (int(val)- val ) * mult;
    unsigned long frac1 = frac;

    while(frac1 /= 10)
      padding--;

    while(padding--)
      strcat(outstr,"0\0");

    strcat(outstr,itoa(frac,temp,10));
  }

  // generate space padding 
  if ((widthp != 0)&&(widthp >= strlen(outstr))){
    byte J=0;
    J = widthp - strlen(outstr);
    
    for (i=0; i< J; i++) {
      temp[i] = ' ';
    }

    temp[i++] = '\0';
    strcat(temp,outstr);
    strcpy(outstr,temp);
  }
  
  return outstr;
}



