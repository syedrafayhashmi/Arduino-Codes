/*
  Melody

 Plays a melody

 circuit:
 * 8-ohm speaker on digital pin 8

 created 21 Jan 2010
 modified 30 Aug 2011
 by Tom Igoe

This example code is in the public domain.

 http://arduino.cc/en/Tutorial/Tone

 */
 int buzzer = 11;              //Buzzer is connected to pin11
int redPin =3;
int greenPin = 5;
int bluePin = 6;
//#include "pitches.h"

// notes in the melody:
int melody[] = {
 2000,2000,2000,2000,2000      //Enter notes or frequencies here
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4      //Enter duration of each note or frequency
};

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
   
    tone(buzzer, melody[thisNote], noteDuration);
 switch (thisNote){
    case 0:
    setColor(150, 0, 255); 
     break;
    case 1:
    setColor(255, 0, 0);  // red
    break;   
    case 2:
    setColor(0, 255, 0);  // green
    break;
    case 3:
    setColor(0, 0, 255);  // blue
    break;
    case 4:
    setColor(255, 255, 0);  // yellow
    break;
    case 5:
    setColor(80, 0, 80);  // purple
    break;
    case 6:
    setColor(0, 255, 255);  // aqua
    break; 
    case 7:
    setColor(0, 80, 255);  // aqua
    break;    
}
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(buzzer);
  }
}

void loop() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buzzer, melody[thisNote], noteDuration);
   switch (thisNote){
    case 0:
    setColor(150, 0, 255); 
    break;
    case 1:
    setColor(255, 0, 0);  // red
    break;   
    case 2:
    setColor(0, 255, 0);  // green
    break;
    case 3:
    setColor(0, 0, 255);  // blue
    break;
    case 4:
    setColor(255, 255, 0);  // yellow
    break;
    case 5:
    setColor(80, 0, 80);  // purple
    break;
    case 6:
    setColor(0, 255, 255);  // aqua
    break; 
    case 7:
    setColor(0, 80, 255);  // aqua
    break;}
  
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(buzzer);
delay(10);
  }
 // no need to repeat the melody.
}
void setColor(int red, int green, int blue)
{
#ifdef COMMON_ANODE
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
#endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
