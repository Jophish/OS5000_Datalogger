// Functions for reading and writing data to and from the SD card.


//Writes formatted compass data to the SD card.
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
 
 
 
 // Gets a filename.
 
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
    filename[2] = year/10 + '0';
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

