int en1=9;
int en2=10;
void fwd();

void setup() {
    pinMode(en1,OUTPUT);// ENABLE 1 OF LEFT MOTOR (PWM)
  pinMode(5,OUTPUT);// IN1 OF LEFT MOTOR
  pinMode(6,OUTPUT);// IN2 OF LEFT MOTOR
  pinMode(7,OUTPUT);// IN3 OF RIGHT MOTOR
  pinMode(8,OUTPUT);// IN4 OF RIGHT MOTOR
  pinMode(en2,OUTPUT);// ENABLE 2 OF RIGHT MOTOR (PWM)

  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
fwd();
}
void fwd()
{
  digitalWrite(en1,HIGH);// LEFT MOTOR
  digitalWrite(5,HIGH);// LEFT MOTOR
  digitalWrite(6,LOW);// LEFT MOTOR

  digitalWrite(en2,HIGH);// RIGHT MOTOR
  digitalWrite(7,HIGH);// RIGHT MOTOR
  digitalWrite(8,LOW);// RIGHT MOTOR


}
