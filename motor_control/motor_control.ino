
#define IN1 8      //IN1
#define IN2 13        //IN2
#define ENA 2          //ENA
void motor_on(void);
int speedcontrol = 255; //range of speed control is from  0 to 255
void setup(void)
{
  Serial.begin (9600);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENA,OUTPUT);
  analogWrite(ENA,speedcontrol);
 }


void loop(void) {
  motor_on();
} 
void motor_on(void)
{  Serial.println("MOTOR RUNNING");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}
