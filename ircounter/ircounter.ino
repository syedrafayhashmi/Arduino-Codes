#include <LiquidCrystal.h>

LiquidCrystal lcd1(12, 5, 7, 8, 9, 10);
LiquidCrystal lcd2(12, 4, 7, 8, 9, 10);

const int personin = A0;
const int personout = A1;
const int th = A5;
// Analog input pin that the receiver is attached to
int sensorValue1 = 0;
int sensorValue2 = 0;// value read from the receiver
int thValue = 0;
int countin = 0;
int countout = 0;
void setup() {
  lcd1.begin(16, 2);
  lcd2.begin(16, 2);
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  //initialize the indicator LED:
  pinMode(13, OUTPUT);
  lcd1.print("   PERSON IN   ");
  lcd2.print("   PERSON OUT  ");
}

void loop() {
  // read the analog in value:
  lcd1.setCursor(6, 1);
  lcd2.setCursor(6, 1);
  sensorValue1 = analogRead(personin);
  sensorValue2 = analogRead(personout);
  thValue = analogRead(th);
  
  // print the results to the serial monitor:
  Serial.print("\nthreshold = ");
  Serial.print(thValue);
  Serial.print("\nsensor1 = ");
  Serial.print(sensorValue1);
  Serial.print("\nsensor2 = ");
  Serial.print(sensorValue2);
  //the threshold found fron analog In Out program was when object is detected, the sensor value is below 100
  //set the threshold whihc you get
  //the threshold varies for different sets of emitter-receiver pairs
  if(sensorValue1 > thValue){ //checks if object is there or not
    digitalWrite(13, HIGH);
    Serial.print("\nPerson In");
    countin+=1;
    lcd1.print(countin);
    }
  if(sensorValue2 > thValue){ //checks if object is there or not
    digitalWrite(13, HIGH);
    Serial.print("\nperson out");
    countout+=1;
    lcd2.print(countout);
    }
  else{
    digitalWrite(13, LOW);
    Serial.print("\nNo object in Front");
    }
  delay(500);
}
