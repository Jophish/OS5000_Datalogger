//Functions for getting and setting the date on the RTC.

//Sets date.
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

//Gets date.
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

//Sets time.
void set_time()
{
   Wire.beginTransmission(104);
   Wire.write((uint8_t)0);
   Wire.write((uint8_t)decToBcd(seconds));
   Wire.write((uint8_t)decToBcd(minutes));
   Wire.write((uint8_t)decToBcd(hours));
   Wire.endTransmission();
}

//Gets time.
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

//Sets hour.
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

//Sets minutes.
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
