#include <Adafruit_NECremote.h>

//*****************************************************************************
//17 button IR remote
//NEC - IR code
//By: LarryD 
//
//This sketch demonstrates interfacing to a 17 button IR remote. http://goo.gl/Jk79FM
//These are commonly available on eBay for $2 USD.
//The remote usually comes with a controller. 
//It is an all in one IR detector/amplifier similar to TSOP38238, yours may vary
//**Always confirm the detector/amplifier you have is wired as per YOUR data sheet**
//Remove the detector from the controller for this discussion and wire it to +5V and GND.
//Datasheet for the IR detector: https://www.sparkfun.com/datasheets/Sensors/Infrared/tsop382.pdf
//For wiring, see:               https://learn.sparkfun.com/tutorials/ir-control-kit-hookup-guide
//Interrupt 0 (pin D2) is used to achieve fast receive response.
//See also:                      http://forum.arduino.cc/index.php?topic=289446.msg
//
//=============================================================================
//17 button IR remote
//NEC - IR code
//By: LarryD
//
//For the remote control, see:  http://goo.gl/Jk79FM
//
//"IRremoteNEC.cpp IRremoteNEC.h" by LarryD
// PERMISSION TO DISTRIBUTE
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software 


//We must use an interrupt pin, 2 or 3 on an UNO, Ethernet or ATmega1284
//connect this pin to the IR Receiver Module
#define interruptPin 3  
//#define interruptPin 2 

//confirm the correct interrupt pin has been selected
#if interruptPin != 2 && interruptPin != 3
#error interruptPin must be 2 or 3!
#endif
IRremoteNEC myRemote(interruptPin); //create the object using this pin

//**************************************
#define tonePin 7            //Piezo speaker is connected to this pin

//*****************************************************************************  
//17 button Keypad
const byte buttonCode[5] = {0xE0984BB6,0x371A3C86,0x4EA240AE,0x39D41DC6,0x4E87E0AB,0x1D2FEFF6}; //END of buttonCode Array

const byte ASCIIcode[5] = {0xE0984BB6,0x371A3C86,0x4EA240AE,0x39D41DC6,0x4E87E0AB,0x1D2FEFF6
}; //END of ASCIIcode Array 

//*****************************************************************************

void setup(void) 
{
  Serial.begin(115200);

  myRemote.beginIR();

} 
//************************** E N D   s e t u p ( ) *****************************

void loop(void) 
{
  //**************************************
  //Check if we have received a valid IR code yet. 
  if(myRemote.getIRflag())
  {
    byte byteRX = myRemote.checkCode();
    //If we get a verified button code, convert it to an ASCII code.
    if(byteRX) 
    {          
      //Scan through the buttonCode Array.
      //NOTE: IR remote repeat codes are not returned.
      for (int i = 0; i < 5; i++) 
      {
        if (buttonCode[i] == byteRX)
        {
          tone(tonePin,3400,100);
          Serial.print(char(ASCIIcode[i])); //get the ASCII code

          //We found it, no need to continue looking.
          break;
        } 
      }
    } // END of if(byteRX)

    //Get ready for the next falling edge.
    myRemote.resetIRflag(); 

  } // END of if(myRemote.getIRflag())
  //**************************************

  // Other loop stuff goes here

}
//************************** E N D   l o o p ( ) *****************************






//=============================================================================
//                             END OF CODE
//=============================================================================
