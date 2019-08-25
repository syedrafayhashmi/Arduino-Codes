#include "EmonLib.h"             
#define VOLT_CAL 640.7
#define CURRENT_CAL 27.6
#include <ESP8266WiFi.h>

EnergyMonitor emon1;
const char* ssid = "RAFAY" ;
const char* password = "hash123mi123"; 
WiFiServer server(80);
String header;

void setup()
 { Serial.begin(115200);
emon1.voltage(1, VOLT_CAL, 1.7);
emon1.current(2, CURRENT_CAL);
Serial.print("Connecting to "); Serial.println(ssid); 
WiFi.begin(ssid, password); 
while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); } 
Serial.println("");
Serial.println("WiFi connected."); Serial.println("IP address: "); Serial.println(WiFi.localIP()); server.begin(); }

void loop()
{ emon1.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
//  emon1.calcF(50); 
  
  float currentDraw            = emon1.Irms;             //extract Irms into Variable
  float supplyVoltage   = emon1.Vrms;
  float realpower = emon1.realPower;
  float pwrfct = emon1.powerFactor;
//  float ractivepower = emon1.reactivePower;
 // float freq = emon1.frequency;
  
WiFiClient client = server.available();
if (client) 
{ 
Serial.println("New Client.");
String currentLine = "";
while (client.connected()) 
{
if (client.available())
{
char c = client.read();
Serial.write(c);
header += c;
if (c == '\n') 
{if (currentLine.length() == 0) {
client.println("HTTP/1.1 200 OK"); client.println("Content-type:text/html");
client.println("<!DOCTYPE html><html>"); client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"); client.println("<link rel=\"icon\" href=\"data:,\">");

client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
 client.println(".button2 {background-color: #77878A;}</style></head>");
client.println("Connection: close"); client.println();

client.println("<body><h1>Energy meter</h1>");

client.println("<p> (supplyVoltage)</p>");
client.println("<p> (currentDraw)</p>");
client.println("<p> (currentDraw*supplyVoltag)</p>");
client.println("<p> (realpower)</p>");
client.println("<p> (pwrfct)</p>");
//client.println("<p> ((-1)*realpower+"+"j" "+(-1)*ractivepower<p>)");
client.println("<p> (freq)</p>");

client.println("</body></html>");
client.println();
break;} else { currentLine = ""; } 
} else if (c != '\r') {currentLine += c;}
}}
header = "";
client.stop(); 
Serial.println("Client disconnected."); Serial.println(""); } }
