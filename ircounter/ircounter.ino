#include <LiquidCrystal.h>

LiquidCrystal lcd1(12, 5, 7, 8, 9, 10);
LiquidCrystal lcd2(12, 4, 7, 8, 9, 10);

const int personin = A0;
const int personout = A1;
const int th = A5;

int sensorValue1 = 0;
int sensorValue2 = 0;
int thValue = 0;
int countin = 0;
int countout = 0;
void setup() {
  lcd1.begin(16, 2);
  lcd2.begin(16, 2);
  
  Serial.begin(9600);
  
  pinMode(13, OUTPUT);
  lcd1.print("   PERSON IN   ");
  lcd2.print("   PERSON OUT  ");
}

void loop() {
 
  lcd1.setCursor(6, 1);
  lcd2.setCursor(6, 1);
  sensorValue1 = analogRead(personin);
  sensorValue2 = analogRead(personout);
  thValue = analogRead(th);
  
  
  Serial.print("\nthreshold = ");
  Serial.print(thValue);
  Serial.print("\nsensor1 = ");
  Serial.print(sensorValue1);
  Serial.print("\nsensor2 = ");
  Serial.print(sensorValue2);
  if(sensorValue1 > thValue){ 
    digitalWrite(13, HIGH);
    Serial.print("\nPerson In");
    countin+=1;
    lcd1.print(countin);
    }
  if(sensorValue2 > thValue){
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
