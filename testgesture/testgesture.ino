int xPin = A0; //X axis input
int yPin = A1; //Y axis input

int D1=11; 
int D2=10;
int D3=9;
int D4=8;
long x;  //Variable for storing X Coordinates
long y;  //Variable for storing Y Coordinates
long z;  //Variable for storing Z Coordinates

void setup()
{
  Serial.begin(9600);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
}
void loop()
{
  x = analogRead(xPin);  //Reads X coordinates
  y = analogRead(yPin);  //Reads Y coordinates
  Serial.print("x= ");
  Serial.print(x);
  Serial.print(" y= ");
  Serial.print(y);
  delay(5000);
  left();
  delay(5000);
  right();
}
void stop_()
{
  Serial.println("");
  Serial.println("STOP");
  digitalWrite(D1, HIGH);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
}
void forward()
{
  Serial.println("");
  Serial.println("Forward");
  digitalWrite(D1, HIGH);
  digitalWrite(D2, LOW);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, LOW);
}
void backward()
{
  Serial.println("");
  Serial.println("Backward");
  digitalWrite(D1, LOW);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, LOW);
  digitalWrite(D4, HIGH);
}
void left()
{
  Serial.println("");
  Serial.println("Left");
  digitalWrite(D1, HIGH);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, HIGH);
}
void right()
{
  Serial.println("");
  Serial.println("Right");
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, LOW);
}
