int GA=11,GB=12,DA=9,DB=10;
void setup() {
  Serial.begin(9600);  
  pinMode(DA,OUTPUT);
  pinMode(DB,OUTPUT);
  pinMode(GA,OUTPUT);
  pinMode(GB,OUTPUT); // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
     digitalWrite(DA,HIGH);
     digitalWrite(DB,LOW);
     digitalWrite(GA,HIGH);
     digitalWrite(GB,LOW);
          
}
