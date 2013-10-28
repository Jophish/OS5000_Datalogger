/*


ARDUINO OS5000 BASED DATALOGGER

This sketch is for use with the Arduino OS5000 Datalogger. After logging
data, The ATmega puts itself to sleep to conserve power. When the inturrept on 
Pin 2 recieves a LOW signal from an external async 555 timer, it wakes up, logs 
data, and puts itself back to sleep. 

To change the samples are taken every logging cycle, browse to void_loop() and 
change the variable "times" to however many samples you would like taken each time
data is logged. 

Joe Bergeron

Contact: Jophish126@Gmail.com

*/


#include <avr/sleep.h>
#include <SD.h>
#include <Wire.h>

// Set variables

String heading;
String pitch;
String roll;
String wow;

int wakePin = 2;
int sleepStatus = 0;
int count = 0;
long mb = 1048576;
int q = 0;
File myFile;
String name;

void wakeUpNow()
{
}


// Use these for resetting the date and time //
///////////////////////////////////////////////

int seconds = 30; //00-59;
int minutes= 43; //00-59;
int hours = 12;//1-12 - 00-23;
int day = 4;//1-7
int date = 14;//01-31
int month = 8;//01-12
int year = 13;//0-99;
char filename[] = "000000000000";

//////////////////////////////////////////////

void setup()
{
  pinMode(wakePin, INPUT);  // Set inputs/outputs
  pinMode(5, OUTPUT);
  pinMode(10, OUTPUT);  
  
  Wire.begin();          // Begin Wire and Serial
  Serial.begin(9600);

  SD.begin(10);
  attachInterrupt(0, wakeUpNow, LOW); // Set interrupt
  
 

}

void loop() {
  int times = 3; //Initialize logging procedures
    int x = 0;
  //set_date();
  //set_time();
  getFilename(filename);
  
  while (true){
    compass_on();   
    while (x < times) { // Log data "times" times
      get_time();
      get_date();
      get_data();
      write_data();
      x += 1;
      }
   x = 0;
  compass_off();
  sleepNow();
  }
}
  
    






