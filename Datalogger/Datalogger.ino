/*


ARDUINO OS5000 BASED DATALOGGER

This sketch is for use with the Arduino OS5000 Datalogger. After logging
data, The ATmega puts itself to sleep to conserve power. When the inturrept on 
Pin 2 recieves a LOW signal from an external async 555 timer, it wakes up, logs 
data, and puts itself back to sleep. 

To change the samples are taken every logging cycle, browse to void_loop() and 
change the variable "times" to however many samples you would like taken each time
data is logged. 



*/
    String heading;
    String pitch;
    String roll;
String wow;

#include <avr/sleep.h>
#include <SD.h>
#include <Wire.h>



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


int seconds = 30; //00-59;
int minutes= 43; //00-59;
int hours = 12;//1-12 - 00-23;
int day = 4;//1-7
int date = 14;//01-31
int month = 8;//01-12
int year = 13;//0-99;
char filename[] = "000000000000";


void setup()
{
 pinMode(wakePin, INPUT); 
  Wire.begin();  
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  
  pinMode(10, OUTPUT);
  SD.begin(10);

  attachInterrupt(0, wakeUpNow, LOW);
  
 

}

void sleepNow()         // here we put the arduino to sleep
{
 
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable(); 
  attachInterrupt(0,wakeUpNow, LOW);
  sleep_mode(); 
  sleep_disable();
  detachInterrupt(0); 
}

void parse()
{
    int mark1 = wow.indexOf('C');
    int mark2 = wow.indexOf('P');
    int mark3 = wow.indexOf('R');
    int a = mark1 + 1;
    int b = mark2 + 1;
    int c = mark3 + 1;
    while (a < (b - 1))
    {
        heading += wow[a];
      a += 1;
    }
        while (b < (c - 1))
    {
      pitch += wow[b];
      b += 1;
    }
         while (c < wow.length())
    {
       roll += wow[c];
      c += 1;
    }
}
void get_data()
{
  heading = "";
  pitch = "";
  roll = "";
  
  happy:
  
  while (true){
  if (Serial.available()){
   if (Serial.read() == '$')
  {
   goto ooh;
  }
  }
} 

  
  ooh:
  while (true) {
    if (Serial.available()){
    
  
 char o = Serial.read();
 if (o == '*')
 {
   parse();
   wow = "";
   goto lbl2;
   }
 
 if (o != '*')
 {
   wow += o;
 }
  }
  
  
}
 lbl2:
 int g = 1;

}

void write_data ()

{
  
      myFile = SD.open(filename, FILE_WRITE);
      
      if (myFile.size() >= mb)
      {
        myFile.close();
        getFilename(filename);
         myFile = SD.open(filename, FILE_WRITE);
      }
 
      if (myFile){
          myFile.print(month);
          myFile.print("/");
          myFile.print(date);
          myFile.print("/");
         myFile.print("1");
         myFile.print(year%10);
           myFile.print(" ");
          myFile.print(hours);
         myFile.print(":");
          myFile.print(minutes);
         myFile.print(":");
          myFile.print(seconds);
        myFile.print(", ");
            myFile.print("H");
          myFile.print(heading);
         myFile.print(", ");
           myFile.print("P");
          myFile.print(pitch);
          myFile.print(", ");
          myFile.print("R");
          myFile.println(roll);
          myFile.close();
                }
 }

 void getFilename(char *filename) {
   int i = 0;
      Wire.beginTransmission(104);
  Wire.write(3);//set register to 3 (day)
  Wire.endTransmission();
  Wire.requestFrom(104, 4); //get 5 bytes(day,date,month,year,control);
  day   = bcdToDec(Wire.read());
  date  = bcdToDec(Wire.read());
  month = bcdToDec(Wire.read());
  year  = bcdToDec(Wire.read());
  while (i < 1000)
  {
    filename[0] = '2';
    filename[1] = '0';
    filename[2] = '1';
    filename[3] = year%10 + '0';
    filename[4] = month/10 + '0';
    filename[5] = month%10 + '0';
    filename[6] = date/10 + '0';
    filename[7] = date%10 + '0';
    filename[8] = '.';
    filename[9] = i/100 + '0';
    filename[10] = (((i - ((i/100)*100))/10) + '0');
    filename[11] = i%10 + '0';

    if (!SD.exists(filename))
   {
      return;
   }
    i += 1;
 // return;
    
  }
  
 }
 
void compass_on()
{ 
  digitalWrite(5, HIGH);
}

void compass_off()
{
  digitalWrite(5, LOW);
}
void loop() {
  int times = 3;
    int x = 0;
  //set_date();
  //set_time();
  getFilename(filename);
  
  
  while (true){
    
    
    compass_on();
    
    while (x < times) {
      
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
  
    
void set_date()
{
  Wire.beginTransmission(104);
  Wire.write(3);
  Wire.write(decToBcd(day));
  Wire.write(decToBcd(date));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));
  Wire.endTransmission();
}
void get_date()
{
  Wire.beginTransmission(104);
  Wire.write(3);//set register to 3 (day)
  Wire.endTransmission();
  Wire.requestFrom(104, 4); //get 5 bytes(day,date,month,year,control);
  day   = bcdToDec(Wire.read());
  date  = bcdToDec(Wire.read());
  month = bcdToDec(Wire.read());
  year  = bcdToDec(Wire.read());
}

void set_time()
{
   Wire.beginTransmission(104);
   Wire.write((uint8_t)0);
   Wire.write((uint8_t)decToBcd(seconds));
   Wire.write((uint8_t)decToBcd(minutes));
   Wire.write((uint8_t)decToBcd(hours));
   Wire.endTransmission();
}
void get_time()
{
  Wire.beginTransmission(104);
  Wire.write((uint8_t)0);//set register to 0
  Wire.endTransmission();
  Wire.requestFrom(104, 3);//get 3 bytes (seconds,minutes,hours);
  seconds = bcdToDec(Wire.read() & 0x7f);
  minutes = bcdToDec(Wire.read());
  hours = bcdToDec(Wire.read() & 0x3f);

}
void setHour()
{
  hours++;
  if(hours > 23)
  {
   hours = 0;
   seconds = 0;
   minutes = 0;
  }
  set_time();

}
void setMinutes()
{
  minutes++;
  if(minutes > 59)
  {
   minutes = 0;

  }
  seconds=0;

  set_time();

}

///////////////////////////////////////////////////////////////////////

byte decToBcd(byte val)
{
  return ( (val/10*16) + (val%10) );
}

byte bcdToDec(byte val)
{
  return ( (val/16*10) + (val%16) );
}
//////////////////////////////////////////////////////////////////////

//  LCD  FUNCTIONS-- keep the ones you need. 

// clear the LCD
void clearLCD(){
  Serial.write(0xFE);
  Serial.write(0x51);
}




// move the cursor to the home position
void cursorHome(){
  Serial.write(0xFE);
  Serial.write(0x46);
}




void line2(){
  Serial.write(0xFE);
  Serial.write(0x45);
    Serial.write(0x40);
}

void line3(){
  Serial.write(0xFE);
  Serial.write(0x45);
  Serial.write(0x14);
}

void line4(){
  Serial.write(0xFE);
  Serial.write(0x45);
  Serial.write(0x54);
}



