#include "Wire.h"

#include <Time.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include "Adafruit_BMP085.h"
Adafruit_BMP085 bmp;

/**
 * Tokens:
 * - °
 * 
 */


String NAME = "data.txt";
boolean success;
const int chipSelect = 4;


void setup() {
 Serial.begin(9600);
 bmp.begin();
 setTime(0,0,0,0,0,0);
 Wire.begin();
 Serial.println();
 Serial.print("Initialising SD Card....");
 delay(3000);
 pinMode(10,OUTPUT);
 while(!Serial){
  //Wait for serial (Leonardo only...)
 }
 

 if(!SD.begin(chipSelect)){
  Serial.print("operation failed");
  success = false;
  /**
   * Operating failed...
   * 
   */
  
 } else {
  success = true;
  Serial.print("done");
  
 }

Serial.println();

 

 Serial.print("Fetching for file...");
 delay(3000);
 if(SD.exists("data.txt")){
  Serial.print("Fetched!");
  delay(1000);
  
 } else {
  Serial.print("generating file...");
  File obj = SD.open("data.txt",FILE_WRITE);
  obj.close();
  Serial.println("File succesfully generated!");
 }


 Serial.println();
 Serial.println();
 

}

void loop() {
File data = SD.open("data.txt",FILE_WRITE);
  

  Serial.println("-----------------------------------------");
  Serial.print("Temperature = ");
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");
  Serial.print("Pressure = ");
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");
 
    // Calculate altitude assuming 'standard' barometric
    // pressure of 1013.25 millibar = 101325 Pascal
  Serial.print("Altitude = ");
  Serial.print(bmp.readAltitude());
  Serial.println(" meters");
 
 if(data){

 data.println(setFormatted(data,bmp));
 data.close();
 Serial.println(setFormatted(data,bmp));
 
 } else {
  Serial.println("EXCEPTION: error opening data");
 }
 delay(10000);
  
}





String setFormatted(File object,Adafruit_BMP085 bmp){
  String rcformation = "Temperature = " + String(bmp.readTemperature()) + " *C"  + " |  Pressure = " + String(bmp.readPressure()) + " Pa | Altitude = " + String(bmp.readAltitude()) + " meters";
object.println(rcformation);
return rcformation;

    
}
