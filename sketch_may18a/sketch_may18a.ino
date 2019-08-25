int xPin=A0;
int yPin=A1;


int out1=11;     //output1 for HT12E IC
int out2=10;     //output1 for HT12E IC
int out3=9;    //output1 for HT12E IC
int out4=8;


void setup() {

  pinMode(xPin,INPUT);
  pinMode(yPin,INPUT);

  pinMode(out1,OUTPUT);
  pinMode(out2,OUTPUT);
  pinMode(out3,OUTPUT);
  pinMode(out4,OUTPUT);
}

void loop() {
  int xval=analogRead(xPin);
  int yval=analogRead(yPin);
  Serial.begin(9600);
  Serial.println(xval);
  Serial.println(yval);
  Serial.println("\n");


     digitalWrite(out1,HIGH);   
   digitalWrite(out2,LOW);  
   digitalWrite(out3,HIGH);   
   digitalWrite(out4,LOW);
     delay(2000);

}
