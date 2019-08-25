void forward();
void right();
void left();
void halt();

int ENA=9;
int ENB=10;

int IN1=5;
int IN2=6;
int IN3=7;
int IN4=8;

int ir1,ir2,ir3,ir4;

int leftir1 =13;//MOST LEFT IR SENSOR
int leftir2=2;// MIDDLE LEFT IR SENSOR
int rightir1=3;// MIDDLE RIGHT IR SENSOR
int rightir2=4;// MOST RIGHT IR SENSOR

void forward();
void right();
void left();
void halt();

void forward()
{
  analogWrite(ENA,200);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  analogWrite(ENB,200);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);


}
void right()
{
   analogWrite(ENA,180);
   digitalWrite(IN1,HIGH);
   digitalWrite(IN2,LOW);
   analogWrite(ENB,180);
   digitalWrite(IN3,LOW);
   digitalWrite(IN4,HIGH);
}
void left()
{
    analogWrite(ENB,180);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    analogWrite(ENA,180);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);


}

 void halt()
 {
   analogWrite(ENB,0);
   digitalWrite(IN3,LOW);
   digitalWrite(IN4,LOW);
   analogWrite(ENA,0);
   digitalWrite(IN1,LOW);
   digitalWrite(IN2,LOW); 
 }






void setup() {
  Serial.begin(9600);
  pinMode(leftir1,INPUT);
  pinMode(leftir2,INPUT);
  pinMode(rightir1,INPUT);
  pinMode(rightir2,INPUT);
  
  pinMode(ENA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENB,OUTPUT);

}

void loop() {
  ir1=digitalRead(leftir1);
  ir2=digitalRead(leftir2);
  ir3=digitalRead(rightir1);
  ir4=digitalRead(rightir2);
  
  Serial.println(ir1);
  Serial.println("\t");
  Serial.println(ir2);
  Serial.println("\t");
  Serial.println(ir3);
  Serial.println("\t");
  Serial.println(ir4);
  

if(ir1==0 && ir2==1 && ir3==1 && ir4==0)
{
  forward();
  delay(75);
  halt();
}
else if(ir1==1 && ir2==1 && ir3==1 && ir4==0)
{
  left();
  delay(50);
  halt();
}
else if(ir1==1 && ir2==0 && ir3==0 && ir4==0)
{
  left();
  delay(75);
  halt();
}
else if(ir1==1 && ir2==1 && ir3==0 && ir4==0)
{
  left();
  delay(50);
  halt();
}
else if(ir1==1 && ir2==1 && ir3==1 && ir4==0)
{
  forward();
  delay(75);
  halt();
}
else if(ir1==0 && ir2==0 && ir3==0 && ir4==1)
{
  right();
  delay(75);
  halt();
}
else if(ir1==0 && ir2==0 && ir3==1 && ir4==1)
{
  right();
  delay(50);
  halt();
}
else if(ir1==0 && ir2==1 && ir3==1 && ir4==1)
{
  forward();
  delay(75);
  halt();
}
else if(ir1==0 && ir2==1 && ir3==0 && ir4==0)
{
  forward();
  delay(75);
  halt();
}
else if(ir1==0 && ir2==0 && ir3==1 && ir4==0)
{
  forward();
  delay(75);
  halt();
}

else if(ir1==0 && ir2==0 && ir3==0 && ir4==0)
{
  left();
  delay(100);
  right();
  delay(100);
  halt();
}
else if(ir1==1 && ir2==1 && ir3==1 && ir4==1)
{
  right();
  delay(100);
  left();
  delay(100);
  halt();  
}
else if(ir1==1 && ir2==0 && ir3==1 && ir4==0)
{
  left();
  delay(100);
  halt();
}
else if(ir1==1 && ir2==0 && ir3==1 && ir4==1)
{
  left();
  delay(100);
  halt();
}
else if(ir1==1 && ir2==0 && ir3==0 && ir4==1)
{
  left();
  delay(100);
  halt();
}
else if(ir1==1 && ir2==1 && ir3==0 && ir4==1)
{
  right();
  delay(100);
  halt();
}

delay(50);
}
