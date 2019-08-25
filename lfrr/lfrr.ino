int s1,s2,s3,s4;
int en1=9;
int en2=10;
int lir1=13;// most left
int lir2=2;// mid left
int rir1=4;// mid right
int rir2=3;// most right
void bwd();
void fwd();
void rth();
void lft();
void stp();
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(lir1,INPUT);
  pinMode(lir2,INPUT);
  pinMode(rir1,INPUT);
  pinMode(rir2,INPUT);
  
  pinMode(en1,OUTPUT);// ENABLE 1 OF LEFT MOTOR (PWM)
  pinMode(5,OUTPUT);// IN1 OF LEFT MOTOR
  pinMode(6,OUTPUT);// IN2 OF LEFT MOTOR
  pinMode(7,OUTPUT);// IN3 OF RIGHT MOTOR
  pinMode(8,OUTPUT);// IN4 OF RIGHT MOTOR
  pinMode(en2,OUTPUT);// ENABLE 2 OF RIGHT MOTOR (PWM)

}

void loop() {
  s1=digitalRead(lir1);
  s2=digitalRead(lir2);
  s3=digitalRead(rir2);
  s4=digitalRead(rir1);
  Serial.println(s1);
  Serial.println(s2);
  Serial.println(s3);
  Serial.println(s4);
  Serial.println("");
  Serial.println("");




if(s1==0 && s2==1 && s3==1&& s4==0)
{
  fwd();
  delay(100);
  stp();
}
else if(s1==1 && s2==1 && s3==1 && s4==0)
{
  lft();
  delay(50);
  stp();
}
else if(s1==1 && s2==0 && s3==0 && s4==0)
{
  lft();
  delay(75);
  stp();
}
else if(s1==1 && s2==1 && s3==0 && s4==0)
{
  lft();
  delay(50);
  stp();
}
else if(s1==1 && s2==1 && s3==1 && s4==0)
{
  fwd();
  delay(100);
  stp();
}
else if(s1==0 && s2==0 && s3==0 && s4==1)
{
  rth();
  delay(75);
  stp();
}
else if(s1==0 && s2==0 && s3==1 && s4==1)
{
  rth();
  delay(50);
  stp();
}
else if(s1==0 && s2==1 && s3==1 && s4==1)
{
  fwd();
  delay(100);
  stp();
}
else if(s1==0 && s2==1 && s3==0 && s4==0)
{
  fwd();
  delay(100);
  stp();
}
else if(s1==0 && s2==0 && s3==1 && s4==0)
{
  fwd();
  delay(100);
  stp();
}



else if(s1==0 && s2==0 && s3==0 && s4==0)
{
  lft();
  delay(100);
  rth();
  delay(100);
  stp();
}
else if(s1==1 && s2==1 && s3==1 && s4==1)
{
  rth();
  delay(100);
  lft();
  delay(100);
  stp();  
}
else if(s1==1 && s2==0 && s3==1 && s4==0)
{
  lft();
  delay(100);
  stp();
}
else if(s1==1 && s2==0 && s3==1 && s4==1)
{
  lft();
  delay(100);
  stp();
}
else if(s1==1 && s2==0 && s3==0 && s4==1)
{
  lft();
  delay(100);
  stp();
}
else if(s1==1 && s2==1 && s3==0 && s4==1)
{
  rth();
  delay(100);
  stp();
}



delay(50);

}


void fwd()
{
  analogWrite(en1,255);// LEFT MOTOR
  digitalWrite(5,HIGH);// LEFT MOTOR
  digitalWrite(6,LOW);// LEFT MOTOR

  analogWrite(en2,255);// RIGHT MOTOR
  digitalWrite(7,HIGH);// RIGHT MOTOR
  digitalWrite(8,LOW);// RIGHT MOTOR


}

void rth()
{
   analogWrite(en1,180);// LEFT MOTOR
  digitalWrite(5,HIGH);// LEFT MOTOR
  digitalWrite(6,LOW);// LEFT MOTOR

   analogWrite(en2,180);// RIGHT MOTOR
  digitalWrite(7,LOW);// RIGHT MOTOR
  digitalWrite(8,HIGH);// RIGHT MOTOR
    
  
}

void lft()
{
    analogWrite(en2,180);// LEFT MOTOR
  digitalWrite(5,LOW);// LEFT MOTOR
  digitalWrite(6,HIGH);// LEFT MOTOR

   analogWrite(en1,180);// RIGHT MOTOR
  digitalWrite(7,HIGH);// RIGHT MOTOR
  digitalWrite(8,LOW);// RIGHT MOTOR


}


 void stp()
 {
   analogWrite(en2,0);// RIGHT MOTOR
  digitalWrite(7,LOW);// RIGHT MOTOR
  digitalWrite(8,LOW);// RIGHT MOTOR

    analogWrite(en1,0);// LEFT MOTOR
  digitalWrite(5,LOW);// LEFT MOTOR
  digitalWrite(6,LOW);// LEFT MOTOR
  
 }
