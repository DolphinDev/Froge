
/*
    ====================================================== 
    ThermoSketch is free software: you can redistribute it and/or modify; (c).
    We hope that you don't redistribute this for money; As this is for free :)
    (c) Modified by DolphinDev (Miguel H) & Milos
    (c) Credits to bildr for original code.
    ======================================================
*/



 //# include <XBee.h>
#include <Time.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>



 /**
  * Creatig a XBee object
  */
 //XBee xbee = XBee();
int tmp102Address = 0x48;
const int chipSelect = 4;

File myFile;
void setup(){
 Serial.begin(9600); //Set our baud rate to 9600 for our serial connection
 Wire.begin(); // Initiate the Wire library and join the I2C bus
 setTime(11,3,0,2,6,15);
 //xbee.setSerial(Serial);
 uint8_t payload[] = { 'D','A','T','A'};
 //XBeeAddress64 addr64 = XBeeAddress64(0x0013a200,0x403e00f30);
 //Create a request
 //ZBTxRequest request = ZBTxRequest(addr64,payload,sizeof(payload));
 //xbee.send(request);
 Serial.println();
 Serial.print("Initializing SD Card....");
 delay(2000);
 pinMode(10,OUTPUT);
while(!Serial){
  //waiting for serial

  Serial.println("Waiting for Serial Connection...");

}

if(!SD.begin(chipSelect)){
Serial.print("operation failed");
  
  return;
} else {
  Serial.print("done");
}

Serial.println();
/**
 * SD File Creation
 */

Serial.print("Checking for data file...");
delay(2000);
if(SD.exists("data.txt")){
  Serial.print("done");
  
}
else {

 Serial.print("operation failed, creating data file");
 
Serial.println("Data file created!");
File file = SD.open("data.txt", FILE_WRITE);
file.close();
 
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
  delay(1000);
  Serial.println();
  Serial.println();
  float celsius = getTemperature(); // Get the temperature in C and save it as a float called celsius.
 Serial.print("Celsius: "); // Print our description of the temp
 Serial.println(celsius); // Print our temp in C
 float fahrenheit = (1.8 * celsius) + 32;  // Get the temperature in C and save it as a float called fahrenheit after converting it from celsius.
 Serial.print("Fahrenheit: "); // Print our description of the temp.
 Serial.println(fahrenheit); // Print the temp in F
 getDigitalClockDisplay();
Serial.println("=======================");




File themofile = SD.open("data.txt",FILE_WRITE);

  
  if(themofile){
    themofile.println(setFormatted(themofile,celsius,fahrenheit));
    themofile.close();
    //Closing Connection to the data.
    //Printing the data to serial console.
   
  }
  else {
    Serial.println("========================");
    Serial.println("ERROR: Exception while opening themofile.txt");
    Serial.println("========================");
    
  }
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

String setFormatted(File file, float celsius, float z){


file.print("Celcius: ");
file.println(celsius);

file.println();

file.print("Fahrenheit: ");
file.println(z);
file.println(getTime());
file.println("============================");

  
  }



 String getTime(){

  String asxc = String(hour()) + "/" + String(minute()) + "/" + String(second());  
  return asxc;
  }
