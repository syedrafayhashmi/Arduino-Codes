int count=0;
const int LED=13; // can also use LED_BUILTIN so don't nd to mention pin here
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
 
  pinMode(LED, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  for(count=0;count<=4;count++)
  {
  digitalWrite(LED, HIGH);  
  delay(500);                      
  digitalWrite(LED, LOW);    
  delay(500);    
}
count=0;
for(count=0;count<=4;count++)
  {
  digitalWrite(LED, HIGH);  
  delay(2000);                      
  digitalWrite(LED, LOW);    
  delay(2000);    
}
}
