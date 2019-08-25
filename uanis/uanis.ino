#include <Firebase.h>
#include <FirebaseArduino.h>
#include "DHT.h"
#include <Smoothed.h> 
#include <math.h>
#include <ESP8266WiFi.h>
#define FIREBASE_HOST "spem-d0e30.firebaseio.com"
#define FIREBASE_AUTH "BtY2AcjMHFQyT0FrVy2e7X0tPM0edCkMV7Oow9tp"
#define WIFI_SSID "RAFAY" 
#define WIFI_PASSWORD "hash123mi123" 
#define DHTPIN 14 
#define DHTTYPE DHT11  // DHT 11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
   WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  dht.begin();
  Serial.println ("");
  Serial.println ("WiFi Connected!");
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  Serial.println("connected!!!");
 
  
}

void loop() {
 
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // Reading temperature as Celsius (the default)
  Serial.println (t);

  Firebase.setFloat("Temp",56);
  Firebase.setFloat("Humidity",63);
  
  delay(200);
}
