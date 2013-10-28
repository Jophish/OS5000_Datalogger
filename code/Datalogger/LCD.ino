//  Optional LCD functions for LCD capacilities.

// Clear LCD.
void clearLCD(){
  Serial.write(0xFE);
  Serial.write(0x51);
}




// Move the cursor home.
void cursorHome(){
  Serial.write(0xFE);
  Serial.write(0x46);
}



// Move the cursor to line 2.
void line2(){
  Serial.write(0xFE);
  Serial.write(0x45);
    Serial.write(0x40);
}

// Move the cursor to line 3.
void line3(){
  Serial.write(0xFE);
  Serial.write(0x45);
  Serial.write(0x14);
}

//Move the cursor to line 4.
void line4(){
  Serial.write(0xFE);
  Serial.write(0x45);
  Serial.write(0x54);
}

