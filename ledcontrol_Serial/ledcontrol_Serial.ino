const int LED=13; // can also use LED_BUILTIN so don't nd to mention pin here
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
 Serial.begin(9600); //9600 baud rate
  pinMode(LED, OUTPUT);
  digitalWrite(LED,LOW);
  while (! Serial);
  {Serial.println("...");
  delay(100);}
  Serial.println("Enter 1 to turn on the LED or 0 to turn off the LED");
   
}

// the loop function runs over and over again forever
void loop() {

 if(Serial.available())
 { char data=Serial.read();
  if (data=='1')
  {digitalWrite(LED, HIGH);}  
  if (data=='0')
  {digitalWrite(LED, LOW);}    
  
}
}
