#include <SPI.h>
#include <Wire.h>
#include "RTClib.h"
RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
void setup() 
{
Serial.begin(9600);
if (! rtc.begin()) {
Serial.println("Couldn't find RTC");
while (1);
}
rtc.adjust(DateTime(__DATE__, __TIME__));
Serial.println("  Clock ");
delay(3000);
}
void loop()
{
DateTime now = rtc.now();
Serial.println(now.second(), DEC);
Serial.println(":");
Serial.println(":");
Serial.println(now.minute(), DEC);
Serial.println(now.hour(), DEC);
Serial.println(now.day(), DEC);
Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
Serial.println("-");
Serial.println(now.month(), DEC);
Serial.println("-");
Serial.println(now.year(), DEC);
}
