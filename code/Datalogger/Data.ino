void parse() //Parse input data
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



void get_data() //Read data from compass. Very messy function, need to clean. Get rid of gotos.
{
  heading = "";
  pitch = "";
  roll = "";
  
  while (true){
  if (Serial.available()){
     if (Serial.read() == '$')
        {
           goto lbl1;
        }
    }
} 

  
  lbl1:
  
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

