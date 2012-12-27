void getRunID() {
  client.connect(server, 80);
  client.println("GET /turbiduino/date.php HTTP/1.1");
  client.println("Host: ferment.ccbr.utoronto.ca");
  client.println();
  memset(&runID, 0, 17);
  char c = client.read();
  while (c != '<') {
    c = client.read(); }
    for(int i = 0; i < 12; i++) {
    runID[i] = client.read(); }
  runID[12] = '\0';
  
  client.stop();
  client.flush();
}


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
  client.print(pump_counter * 0.025);
  client.print("&temp=");
  client.print(temp);
  client.println(" HTTP/1.1");
  client.println("Host: ferment.ccbr.utoronto.ca");
  client.println();
}


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



