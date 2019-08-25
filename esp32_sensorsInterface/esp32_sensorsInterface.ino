#include <DHT.h>  
#include <WiFi.h>
#include <IRremote.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Wire.h> 
#include <RtcDS3231.h>

String apiKey = "GYA9DPV7VVZDK62J";     //  Enter your Write API key here
const char *ssid =  "AA";     // Enter your WiFi Name
const char *pass =  "hash123mi123"; // Enter your WiFi Password
const char* server = "api.thingspeak.com";

#define DHTPIN 17   // GPIO Pin where the dht11 is connected
int RECV_PIN = 13;

DHT dht(DHTPIN, DHT11);
IRrecv irrecv(RECV_PIN);

WiFiClient client;
decode_results results;
RtcDS3231<TwoWire> Rtc(Wire);

// I use static IP's, and found i had to put in DNS to make it work properly.
IPAddress local_IP(192,168,43,2);
IPAddress gateway(111,88,192,1);
IPAddress subnet(255,255,255,255);
IPAddress primaryDNS(10,101,11,15);
IPAddress secondaryDNS(10,101,11,35);
// NTP
WiFiUDP ntpUDP;
// i'm in PDT which is +5 from GMT.
NTPClient timeClient(ntpUDP, "us.pool.ntp.org", +5*3600);
// RTC Libraries


void setup() {
 //DHT  
    Serial.begin(115200); 
       delay(10);
       dht.begin();
       Serial.println("Connecting to ");
       Serial.println(ssid);
       WiFi.begin(ssid, pass);
       while (WiFi.status() != WL_CONNECTED) 
     {
            delay(550);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
//IR
 //Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");

//PIR
pinMode(12,INPUT);
 pinMode(14,OUTPUT);
 //Serial.begin(9600);

//RTC
 //Serial.begin(115200);
//  WiFi_Setup();
  // Start NTP Time Client
  timeClient.begin();
  delay(2000);
  timeClient.update();
  Rtc.Begin();
  RTC_Update();

}

void loop() {
  //DHT
  
      float h = dht.readHumidity();
      float t = dht.readTemperature();
      
              if (isnan(h) || isnan(t)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }
                         if (client.connect(server,80))   
                      {  
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(t);
                             postStr +="&field2=";
                             postStr += String(h);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
                             Serial.print("Temperature: ");
                             Serial.print(t);
                             Serial.print(" degrees Celcius, Humidity: ");
                             Serial.print(h);
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
           Serial.println("Waiting...");
    delay(1000);

//IR
 if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
  delay(100);

  //PIR
  Serial.println(digitalRead(12));

if (digitalRead(12)==1)
{digitalWrite(14,HIGH);
//Serial.println("Motion is Detected");
}
else
{digitalWrite(14,LOW);}
delay(1000);

//RTC
if (!RTC_Valid()){
    RTC_Update();
  }
  RtcDateTime currTime = Rtc.GetDateTime();
  printDateTime(currTime);
  Serial.println(timeClient.getFormattedTime());
  delay(1000);
}
// Utility print function
#define countof(a) (sizeof(a) / sizeof(a[0]))
void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];
    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    Serial.println(datestring);
}

void RTC_Update(){
  // Do udp NTP lookup, epoch time is unix time - subtract the 30 extra yrs (946684800UL) library expects 2000
  timeClient.update();
  unsigned long epochTime = timeClient.getEpochTime()-946684800UL;
  Rtc.SetDateTime(epochTime); 
}
bool RTC_Valid(){
  bool boolCheck = true; 
  if (!Rtc.IsDateTimeValid()){
    Serial.println("RTC lost confidence in the DateTime!  Updating DateTime");
    boolCheck = false;
    RTC_Update();    
  }
  if (!Rtc.GetIsRunning())
  {
    Serial.println("RTC was not actively running, starting now.  Updating Date Time");
    Rtc.SetIsRunning(true);
    boolCheck = false;
    RTC_Update();
  }
}

/*void WiFi_Setup(){
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected!");
}*/
