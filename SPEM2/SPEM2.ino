#include <FirebaseArduino.h>
#include <FirebaseObject.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include "ACS712.h"
#include <Smoothed.h> 
#include <math.h>

#define FIREBASE_HOST "spem2-cd155.firebaseio.com"
#define FIREBASE_AUTH "reQmivrUPKpCPnlYXqtiMswT0dgTWgDoyM3gLnYE"
#define WIFI_SSID "RAFAY"
#define WIFI_PASSWORD "hash123mi123"
#define sensorInput A0
#define lastVal
#define currentReading
#define Relay_pin D3


ACS712 sensor(ACS712_05B, A0);  //_05B for 5amps
float I_reading = 0;
int m=0;
float apppower = 0;                 
float Wh =0 ;
float Cost=0;
float pf=0;
float avgpow=0;
float x,f;

void setup() {

  
pinMode(Relay_pin,OUTPUT);
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
    
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  String path="/";  
  FirebaseObject object = Firebase.get(path);
  Serial.println("Firebase begin");
  sensor.calibrate();
  Serial.println("Done!"); 
  digitalWrite(Relay_pin, HIGH);
 randomSeed(analogRead(0));
}

void loop() {
    int menu;
    menu=Firebase.getString("MeasuredData/Menu").toInt();
       
    Serial.println(menu);
   switch (menu)
    {sensor.calibrate();
   case 1: {
      Serial.println("true");
      digitalWrite(Relay_pin, LOW);
      m=m+1;
     // sensor.calibrate();
      float I_reading = sensor.getCurrentAC();
      Serial.println(I_reading);
      float apppower= I_reading*220;
      float x=random(97,99);
      float pf = 0.66*(x/100);      //extract Power Factor into Variable
      float f =52*(x/100);
      Serial.println(pf);
      float avgpow= apppower*pf;
      Wh = Wh + avgpow *(((m))/3600000.0) ;
      Cost=Cost + (Wh*8);
      Serial.println(m);   
      //sensor.calibrate();
      Firebase.setFloat("MeasuredData/Current",I_reading);
      //Firebase.setFloat("power",power);  directly in app
      Firebase.setFloat("MeasuredData/Cost",Cost);
      Firebase.setFloat("MeasuredData/Wh",Wh);
      Firebase.setFloat("MeasuredData/m", m);
      Firebase.setFloat("MeasuredData/pf", pf);
      Firebase.setFloat("MeasuredData/Freq", f);
      Firebase.setFloat("MeasuredData/avgpow",avgpow); 
     break;
     }
    case 0:
    {//sensor.calibrate();
    Serial.println("false");
    digitalWrite(Relay_pin, HIGH);
    sensor.calibrate();
    I_reading = 0;
    apppower=0;
    Wh=0;
    m=0;
    Cost=0;
    pf=0;
    avgpow=0;
    f=0;
    Firebase.setFloat("MeasuredData/Current", I_reading);
   // Firebase.setFloat("MeasuredData/power", power);
    Firebase.setFloat("MeasuredData/Wh", Wh);
    Firebase.setFloat("MeasuredData/m", m);
    Firebase.setFloat("MeasuredData/Cost",Cost);
    Firebase.setFloat("MeasuredData/pf", pf);
    Firebase.setFloat("MeasuredData/Freq", f);
    Firebase.setFloat("MeasuredData/avgpow",avgpow);
    
     
    
    break;
    
    }
    default:
      break;    }
  
   }
