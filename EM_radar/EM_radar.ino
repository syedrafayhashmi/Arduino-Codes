#include <Servo.h>
#include <LiquidCrystal.h>

Servo myservo;
LiquidCrystal lcd(10, 11, 14, 15, 16, 17); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)

int pos = 0; // la position initiale du servo moteur
const int trigPin = 8;
const int echoPin = 9;
//const int moter = 11;
const int buzzer = 6;
const int ledPin1 = 4;
const int ledPin2 = 7;
float distanceCm, DistanceSec,duration;

void setup() {
  Serial.begin(9600);
myservo.attach(2); // attache le Servo moteur a la pin numéro 11+
lcd.begin(16,2); // Initialiser l'interface de Lcd avec leurs Dimensions
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(buzzer, OUTPUT);
pinMode(ledPin1, OUTPUT);
pinMode(ledPin2, OUTPUT);
DistanceSec=20;

}

void loop() {
for (pos = 0; pos <= 180; pos += 1) { // aller de 0 a 180 degée
// in steps of 1 degree
myservo.write(pos); // Programmer le Servo pour aller a la position (pos)
digitalWrite(trigPin, LOW);
delay(15);
digitalWrite(trigPin, HIGH); //envoyer une impulsion de 10 micro seconds
delay(15);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);
distanceCm= duration*0.034/2;
Serial.println(distanceCm);
if (distanceCm <= DistanceSec)
{

if(distanceCm <= DistanceSec/2)
{

tone(buzzer, 10); // Send 1KHz sound signal...
digitalWrite(ledPin1, LOW);
digitalWrite(ledPin2, HIGH);
delay(300);
noTone(buzzer); // Stop sound...
lcd.setCursor(0,0); // positionner le cursor a 0,0
lcd.print("Distance: "); // Printe "Distance" sur LCD
lcd.print(distanceCm); // Printe la valeur Obtenue sur LCD
lcd.print(" cm "); 
Serial.println(distanceCm);// Printe l'unité sur LCD
delay(10);
lcd.setCursor(0,1);
lcd.print("Angle : ");
lcd.print(pos);
lcd.print(" deg ");
Serial.println(pos);
delay(100);
}
else
{
digitalWrite(buzzer, HIGH);
digitalWrite(ledPin2, LOW);
digitalWrite(ledPin1, HIGH);
delay(100);
digitalWrite(buzzer, LOW);
lcd.setCursor(0,0); // positionner le cursor a 0,0
lcd.print("Distance: "); // Printe "Distance" sur LCD
lcd.print(distanceCm); // Printe la valeur Obtenue sur LCD
lcd.print(" cm ");

Serial.println(distanceCm);// Printe l'unité sur LCD
delay(10);
lcd.setCursor(0,1);
lcd.print("Angle : ");
lcd.print(pos);
lcd.print(" deg ");

Serial.println(pos);
delay(100);
}
}
else{
digitalWrite(buzzer, LOW);
digitalWrite(ledPin1, LOW);
digitalWrite(ledPin2, LOW);
}

lcd.setCursor(0,0); // positionner le cursor a 0,0
lcd.print("Distance:"); // Printe "Distance" sur LCD
lcd.print(distanceCm); // Printe la valeur Obtenue sur LCD
lcd.print(" cm "); // Printe l'unité sur LCD
delay(10);
lcd.setCursor(0,1);
lcd.print("Angle : ");
lcd.print(pos);
lcd.print(" deg ");
delay(80); //attendre 100ms pour que le servo cherche sa position

}
for (pos = 180; pos >= 0; pos -= 1) { //
myservo.write(pos); //
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);
distanceCm= duration*0.034/2;
Serial.println(distanceCm);
if (distanceCm <= DistanceSec){
if(distanceCm <= DistanceSec/2)
{
tone(buzzer, 10); // Send 1KHz sound signal...
digitalWrite(ledPin1, LOW);
digitalWrite(ledPin2, HIGH);
delay(300);
noTone(buzzer); // Stop sound...
lcd.setCursor(0,0); // positionner le cursor a 0,0
lcd.print("Distance: "); // Printe "Distance" sur LCD
lcd.print(distanceCm); // Printe la valeur Obtenue sur LCD
lcd.print(" cm "); // Printe l'unité sur LCD
delay(10);
lcd.setCursor(0,1);
lcd.print("Angle : ");
lcd.print(pos);
lcd.print(" deg ");
delay(100);
}
else
{
digitalWrite(buzzer, HIGH);
digitalWrite(ledPin2, LOW);
digitalWrite(ledPin1, HIGH);
delay(100);
digitalWrite(buzzer, LOW);
lcd.setCursor(0,0); // positionner le cursor a 0,0
lcd.print("Distance: "); // Printe "Distance" sur LCD
lcd.print(distanceCm); // Printe la valeur Obtenue sur LCD
lcd.print(" cm "); // Printe l'unité sur LCD
delay(10);
lcd.setCursor(0,1);
lcd.print("Angle : ");
lcd.print(pos);
lcd.print(" deg ");
delay(100);
}
}
else{
digitalWrite(buzzer, LOW);
digitalWrite(ledPin1, LOW);
digitalWrite(ledPin2, LOW);
}

lcd.setCursor(0,0); //
lcd.print("Distance: "); //
lcd.print(distanceCm); //
lcd.print(" cm ");
delay(10);
lcd.setCursor(0,1);
lcd.print("Angle : ");
lcd.print(pos);
lcd.print(" deg ");
delay(80);
}
}
