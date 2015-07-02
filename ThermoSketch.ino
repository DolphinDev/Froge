
/*
 ThemoSketch   is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ThemoSketch is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    
    We ask you very deeply to not sell this.
    
    (c) Modified by DolphinDev (Miguel H) & Milos.
    
    (c) Credits to bildr for original code.
*/



#include <XBee.h>
#include <Time.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>



 /**
  * Creatig a XBee object
  */
 XBee xbee = XBee();
int tmp102Address = 0x48;
const int chipSelect = 4;

File myFile;
void setup(){
 Serial.begin(9600); //Set our baud rate to 9600 for our serial connection
 Wire.begin(); // Initiate the Wire library and join the I2C bus
 setTime(11,3,0,2,6,15);
 xbee.setSerial(Serial);
 uint8_t payload[] = { 'D','A','T','A'};
 XBeeAddress64 addr64 = XBeeAddress64(0x0013a200,0x403e00f30);
 //Create a request
 ZBTxRequest request = ZBTxRequest(addr64,payload,sizeof(payload));
 xbee.send(request);
 Serial.println();
 Serial.println("Initializing SD Card....");
 pinMode(10,OUTPUT);
while(!Serial){
  //waiting for serial
  Serial.println("##########################################");
  Serial.println("Waiting for Serial Connection...");
  Serial.println("##########################################");
}
Serial.println("##########################################");
Serial.println("Connecting to SD Card...");
Serial.println("##########################################");
if(!SD.begin(chipSelect)){
  Serial.println("==========================================");
  Serial.println("ERROR: Card not present or connection fail");
  Serial.println("==========================================");
  
  return;
}
Serial.println("##########################################");
Serial.println("SD Card has been fully connected to Arduino.");
Serial.println("##########################################");

/**
 * SD File Creation
 */


if(SD.exists("thermofile.txt")){
  Serial.println("############################");
  Serial.println("Data file exists");
  Serial.println("############################");
  
}
else {
  Serial.println("=========================");
  Serial.println("Data file does not exists");
  Serial.println("=========================");
  Serial.println("######################");
Serial.println("Creating thermofile...");
Serial.println("######################");
myFile = SD.open("thermofile.txt", FILE_WRITE);
myFile.close();
 
}


}

void digitalClockDisplay(){
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year());
  Serial.println();
}

void loop(){
 String dataString = "";

 for(int analogPin = 0; analogPin < 3; analogPin++){
  int sens = analogRead(analogPin);
  dataString += String(sens);
  if(analogPin < 2){
    dataString += ",";
  }
 }
 File themofile = SD.open("thermofile.txt",FILE_WRITE);

  //Check dat
  if(themofile){
    Serial.println("###############");
    Serial.println("Opening ThemoFile");
    Serial.println("###############");
    themofile.println(dataString);
    themofile.close();
    //Closing Connection to the data.
    //Printing the data to serial console.
    Serial.println(dataString);
  }
  else {
    Serial.println("========================");
    Serial.println("ERROR: Exception while opening themofile.txt");
    Serial.println("========================");
    
  }
  

  float celsius = getTemperature(); // Get the temperature in C and save it as a float called celsius.
 
 Serial.print("Celsius: "); // Print our description of the temp
 Serial.println(celsius); // Print our temp in C

 
 
 
 float fahrenheit = (1.8 * celsius) + 32;  // Get the temperature in C and save it as a float called fahrenheit after converting it from celsius.
 Serial.print("Fahrenheit: "); // Print our description of the temp.
 Serial.println(fahrenheit); // Print the temp in F
 getDigitalClockDisplay();
Serial.println("=======================");

 Serial.write(13);
 delay(30000);
 
 
 
}
 
// Let’s take a look at our getTempurature function. Without it, nothing would work.
float getTemperature(){
 Wire.requestFrom(tmp102Address,2); // We use our wire library’s get two readings from our TMP102. We pass it the address and the quantity.
 
 
// You may have noticed that we didn’t do anything with the request. That’s because we have to read back we requested. We do that sequentially.
 byte MSB = Wire.read(); // The first byte we get, the Most Significant, get’s stored in MSB.
 byte LSB = Wire.read(); // The second byte we get, the Least Significant, get’s stored in LSB.
 
 
 int TemperatureSum = ((MSB << 8) | LSB) >> 4;
 
 float celsius = TemperatureSum*0.0625; // Convert our temp to celsius.
 return celsius; // Return our result to be printed.
}

void getDigitalClockDisplay(){
  // digital clock
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(year());
  Serial.println();
}


void printDigits(int digits){
  Serial.print(":");
  if(digits < 10)
  Serial.print('0');
  Serial.print(digits);
}
