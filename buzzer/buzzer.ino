const int buzzer=3;     // pin 3 is the buzzer output
const int pushbutton=4; // pin 4 is the pushbutton input

void setup()
{
  pinMode(buzzer,OUTPUT);    //configure pin 4 as OUTPUT
  pinMode(pushbutton,INPUT); //configure pin 4 as INPUT
}
void loop()
{
  int sensor1_value=analogRead(A0);   //read the output of both sensors and compare to the threshold value
  int sensor2_value=analogRead(A1);
  if (sensor1_value>100)
  {
    while(true)
    {
      digitalWrite(buzzer,HIGH);        //sets the alarm ON
      if(digitalRead(pushbutton)==HIGH)
      break;
    }
  } 
  else
  digitalWrite(buzzer,LOW); //turn off alarm 
}
