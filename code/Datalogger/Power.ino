// Functions for power management.


// Arduino goes to sleep to save power.
void sleepNow()         
{
 
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable(); 
  attachInterrupt(0,wakeUpNow, LOW);
  sleep_mode(); 
  sleep_disable();
  detachInterrupt(0); 
}


// Switches a transistor to turn on the compass.
void compass_on() 
{ 
  digitalWrite(5, HIGH);
}

// Switches a transistor to turn off the compass.
void compass_off()
{
  digitalWrite(5, LOW);
}
