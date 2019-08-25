//EmonLibrary examples openenergymonitor.org, Licence GNU GPL V3

#include "EmonLib.h"             // Include Emon Library



#define VOLT_CAL 640.7
#define CURRENT_CAL 27.6

EnergyMonitor emon1;             // Create an instance

void setup()
{  
  Serial.begin(9600);
  
  emon1.voltage(1, VOLT_CAL, 1.7);  // Voltage: input pin, calibration, phase_shift
  emon1.current(2, CURRENT_CAL);       // Current: input pin, calibration.
}

void loop()
{
  emon1.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
  emon1.calcF(50); 
  
  float currentDraw            = emon1.Irms;             //extract Irms into Variable
  float supplyVoltage   = emon1.Vrms;  //extract Vrms into Variable
  float realpower = emon1.realPower;
  float pwrfct = emon1.powerFactor;
  float ractivepower = emon1.reactivePower;
  float freq = emon1.frequency;
  
  Serial.print("****");
  Serial.println("\n\n\n\n\n\n");
  Serial.print("Voltage: ");
  Serial.println(supplyVoltage);
  
  Serial.print("Current: ");
  Serial.println(currentDraw);

  Serial.print("Apparent Power: ");
  Serial.println(currentDraw * supplyVoltage);
  

  Serial.print("Real Power: ");
  Serial.println(realpower);

  Serial.print("Power Factor: ");
  Serial.println(pwrfct);
 
  Serial.print("Complex power: ");
  Serial.print(realpower);
  Serial.print(" + j");
  Serial.println(ractivepower);

  Serial.print("Frequency: ");
  Serial.println(freq);
}
