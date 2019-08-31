
#define IN1 8      //IN1
#define IN2 13        //IN2
#define ENA 2          //ENA
#define ENB 7        //ENB
#define IN3 9          //IN3
#define IN4 6          //IN4
#define trigger 11      //Trigger
#define echo 10        //Echo


void stopm(void);
void forward(void);
void inputs(void);
void sharpright(void);

int duration;
float distance;

void setup(void)
{
  Serial.begin (9600);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
 }


void loop(void) {
 inputs();
if(distance<24){
  sharpright();
}
else
{
forward();
}
}



void forward(void)
{  Serial.println("Forward");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}


void sharpright()
{  Serial.println("sharpright");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(400);
}




void stopm(void)
{  Serial.println("stop");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}


void inputs()
{
      digitalWrite(trigger, LOW);
      delayMicroseconds(2); 
      digitalWrite(trigger, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigger, LOW);
      duration = pulseIn(echo, HIGH);
      distance = (duration / 2) / 29.1;
      digitalWrite(trigger, LOW); 
      
      Serial.print("forward Distance: ");
      Serial.println(distance);
}
