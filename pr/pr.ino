#include <FirebaseArduino.h>
#include <FirebaseObject.h>
#include "DHT.h"
#include <Smoothed.h> 
#include <Adafruit_BMP085.h>  
#include <math.h>
#include  <ESP8266WiFi.h>
#define FIREBASE_HOST "smart-monitoring-system-c671d.firebaseio.com"
#define FIREBASE_AUTH "Yg0US82BB2e3NM3mgniSB1lLb0zITud2IfGBbqUV"
#define WIFI_SSID "netis" 
#define WIFI_PASSWORD "password1" 
#define DHTPIN 12 //d6
#define DHTTYPE DHT22
float  mq= 0; // pin d3
float  pres = 14;
Adafruit_BMP085 bmp;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
 
   WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
   dht.begin();
  Serial.println ("");
  Serial.println ("WiFi Connected!");
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  Serial.println("connected!!!");
  String path="/";  
  FirebaseObject object = Firebase.get(path);
   Serial.begin(9600);
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085/BMP180 sensor, check wiring!");
  while (1) {}

  
}
}
  void loop() {
  int   sensor_Data = analogRead(A0);
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // Reading temperature as Celsius (the default) 
  Serial.println (t);
  Serial.print("Temperature = ");
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");
    
  Serial.print("Pressure = ");
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");
  Serial.print("Altitude = ");
  Serial.print(bmp.readAltitude());
  Serial.println(" meters");
  Serial.print("Pressure at sealevel (calculated) = ");
  Serial.print(bmp.readSealevelPressure());
  Serial.println(" Pa");
  Serial.print("Real altitude = ");
  Serial.print(bmp.readAltitude(102000));
  Serial.println(" meters");
  Serial.println();
  delay(500);
int sexy=t+"C";
  Firebase.set("Temp=",t);
  Firebase.set("Humidity=",h);
   Firebase.set("Pressure at sealevel (calculated) =",bmp.readSealevelPressure());
   
    Firebase.set("Altitude= ",bmp.readAltitude());
    Firebase.set("Real Altitude= ",bmp.readAltitude(102000));
    Firebase.set("pressure=",bmp.readPressure());
    Firebase.set("GASS SENSOR=",sensor_Data);
  
  delay(200);
}
