void setup() {
pinMode(A5,OUTPUT);  // put your setup code here, to run once:

}

void loop() {analogWrite(A5,0);
delay(500);
analogWrite(A5,90);
delay(500);  // put your main code here, to run repeatedly:

}
