int GA=11,GB=12,DA=9,DB=10;
char junk;
String inputString="";

void setup() {
  Serial.begin(9600);  
  pinMode(DA,OUTPUT);
  pinMode(DB,OUTPUT);
  pinMode(GA,OUTPUT);
  pinMode(GB,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
}
void ar()
          {
      digitalWrite(DA,HIGH);
      digitalWrite(DB,LOW);
      digitalWrite(GA,HIGH);
      digitalWrite(GB,LOW);
          }
void av()
        {
      digitalWrite(DA,LOW);
      digitalWrite(DB,HIGH);
      digitalWrite(GA,LOW);
      digitalWrite(GB,HIGH);
          }
void g()
        {
      digitalWrite(DA,LOW);
      digitalWrite(DB,HIGH);
      digitalWrite(GA,HIGH);
      digitalWrite(GB,LOW);
          }
void d(){
      digitalWrite(DA,HIGH);
      digitalWrite(DB,LOW);
      digitalWrite(GA,LOW);
      digitalWrite(GB,HIGH);
          }
void s(){
      digitalWrite(DA,LOW);
      digitalWrite(DB,LOW);
      digitalWrite(GA,LOW);
      digitalWrite(GB,LOW);
          }
          


void loop() {
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);

  
   if(Serial.available()){
 while(Serial.available())
    {
      char inChar = (char)Serial.read(); //read the input
      inputString += inChar;        //make a string of the characters coming on serial
    }
    Serial.println(inputString);
    while (Serial.available() > 0)  
    { junk = Serial.read() ; }      //clear the serial buffer
    if(inputString == "a"){         //in case of 'a' go backward
     av();                         
    }else if(inputString == "r"){   //incase of 'b'  foward
      ar();
                              
    }/*else if(inputString == "s"){   //incase of 's' stop
      s();
    }*/
    else if(inputString == "g"){    //incase of 'g' turn left
      g();                          
    }
    else if(inputString == "d"){   //incase of 'd' turn right
      d();                          
    }
    else 
    {   //incase of 's' stop
      s();
    }
    inputString = "";
  }
}
