#include <WiFi.h>
#include <DHT.h>
#include <Wire.h>
#include "SSD1306.h"
//#include "esp_system.h"

#include <NTPClient.h>
#include <WiFiUdp.h>
 

dht DHT;
SSD1306 display(0x3c, 15, 13); 

#define DHT22_PIN 5

#define NTP_OFFSET 2 * 60 * 60 // In seconds
#define NTP_INTERVAL 60 * 1000 * 60 // In miliseconds
#define NTP_ADDRESS "0.cz.pool.ntp.org"

// Replace with your network credentials
const char* ssid     = "Rafay";
const char* password = "hash123mi123";

WiFiServer server(8080);

// Temporary variables
static char celsiusTemp[7];
static char humidityTemp[7];

// Client variables
char linebuf[80];
int charcount = 0;

unsigned long startTimeTemp;
unsigned long startTimeTime;
String motd;
int day = -1;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);

/* hw_timer_t *timer = NULL;

void IRAM_ATTR resetModule(){
    ets_printf("reboot\n");
    esp_restart_noos();
} */

void setup() {
  startTimeTemp = millis();
  startTimeTime = millis();
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

/*  timer = timerBegin(0, 80, true); //timer 0, div 80
  timerAttachInterrupt(timer, &resetModule, true);
  timerAlarmWrite(timer, 600000000, false); //set time in us
  timerAlarmEnable(timer); //enable interrupt
*/

  display.init();


  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  // attempt to connect to Wifi network:
  while (WiFi.status() != WL_CONNECTED) {
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
  motd = String("Listening on ") + WiFi.localIP().toString();
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 0, motd);
  //display.setContrast(10,5,0);
  display.display();
}

void loop() {
    if (WiFi.status() != WL_CONNECTED) {
      wifiReconnect();
    }
    // listen for incoming clients
    WiFiClient client = server.available();
    if (millis() - startTimeTime >= 500) {
      // update time
      timeClient.update();
      String formattedTime = timeClient.getFormattedTime();

      
      if (timeClient.getHours() > 7 && timeClient.getHours() < 21){
        // day
        if (day != 1){
          display.clear();
          display.setContrast(100);
          display.displayOn();
          day = 1;
        }
      } else {
        // night
        if (day != 0){
          display.clear();
          display.setContrast(1,1,0);
          display.displayOff();
          day = 0;
        }
      }

      display.setColor(BLACK);
      display.fillRect(0, 26, 128, 24);
      display.setColor(WHITE);
      
      if (day == 1){
        display.setFont(ArialMT_Plain_24);
      }else{
        display.setFont(ArialMT_Plain_10);
      }
      
      display.drawString(0, 26, formattedTime);
      display.display();
    }
    if (millis() - startTimeTemp >= 5000) {
      // 5 seconds have elapsed. ... do something interesting ...
      getDhtValues();
      display.setColor(BLACK);
      display.fillRect(0, 10, 128, 16);
      display.setColor(WHITE);
      
      if(day == 1){
        display.setFont(ArialMT_Plain_16);
        display.drawString(0, 10, String(DHT.temperature) + " *C " + String(DHT.humidity) + "%");
      }else{
        display.setFont(ArialMT_Plain_10);
        display.drawString(0, 10, String(DHT.temperature) + " *C ");
      }
      display.display();
      startTimeTemp = millis();
    }
    if (!client) {
        return;
    }
    
    //timerWrite(timer, 0); //reset timer (feed watchdog)
    
    Serial.println("");
    Serial.println("New client");

    // Wait for data from client to become available
    while(client.connected() && !client.available()){
        delay(1);
    }

    // Read the first line of HTTP request
    String req = client.readStringUntil('\r');

    // First line of HTTP request looks like "GET /path HTTP/1.1"
    // Retrieve the "/path" part by finding the spaces
    int addr_start = req.indexOf(' ');
    int addr_end = req.indexOf(' ', addr_start + 1);
    if (addr_start == -1 || addr_end == -1) {
        Serial.print("Invalid request: ");
        Serial.println(req);
        return;
    }
    req = req.substring(addr_start + 1, addr_end);
    Serial.print("Request: ");
    Serial.println(req);
    client.flush();

   
    if (req == "/getNice")
    {
          getDhtValues();
          Serial.print("Humidity: ");
          Serial.print(DHT.humidity);
          Serial.print(" %\t Temperature: ");
          Serial.print(DHT.temperature);
          Serial.print(" *C \n");
          // send a standard http response header
          clientSendHeader(client);
          client.println("<!DOCTYPE HTML><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
          client.println("<meta http-equiv=\"refresh\" content=\"30\"></head>");
          client.println("<body><div style=\"font-size: 3.5rem;\"><p>ESP32 - DHT</p><p>");
          if (DHT.temperature >= 25) {
            client.println("<div style=\"color: #930000;\">");
          }
          else if (DHT.temperature < 25 && DHT.temperature >= 5) {
            client.println("<div style=\"color: #006601;\">");
          }
          else if (DHT.temperature < 5) {
            client.println("<div style=\"color: #009191;\">");
          }
          client.println(DHT.temperature);
          client.println("*C</p></div>");
          client.println(DHT.humidity);
          client.println("%</p></div>");
          client.println("</body></html>");
        Serial.println("Sending 200");
    }
    else if(req == "/get"){
      // temp:humidity:retries
      getDhtValues();
      clientSendHeader(client);
      client.println(String(DHT.temperature) + ":" + String(DHT.humidity) + ":0");
    }
    else
    {
        String s;
        s = "HTTP/1.1 404 Not Found\r\n\r\n";
        client.print(s);
        Serial.println("Sending 404");
    }
    

    Serial.println("Done with client");
}

void getDhtValues(){
          int check;
          check = 1;
          while(check != 0 && check < 10){
            int chk = DHT.read22(DHT22_PIN);
            switch (chk)
            {
            case DHTLIB_OK:
                check = 0;
                Serial.print("OK,\t");
                break;
            case DHTLIB_ERROR_CHECKSUM:
                check++;
                Serial.print("Checksum error,\t");
                break;
            case DHTLIB_ERROR_TIMEOUT:
                check++;
                Serial.print("Timeout error,\t");
                break;
            default:
                check++;
                Serial.print("Unknown error,\t");
                break;
            }
            delay(500);
          }

          //return DHT;
}

void clientSendHeader(WiFiClient &client){
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println("Connection: close");  // the connection will be closed after completion of the response
        client.println(); 
}

void wifiReconnect() {
  while (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    for(int i=0; i<=50; i++) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(100);
      Serial.print(".");
      digitalWrite(LED_BUILTIN, LOW);
      delay(100);
    }
  }
}
