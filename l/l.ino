void setup() {
  // put your setup code here, to run once:

}

void loop() {
 
void printDateTime(const RtcDateTime&amp; dt)
{
    char datestring[20];
 
    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Day(),
            dt.Month(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    Serial.print(datestring);
} // put your main code here, to run repeatedly:

}
