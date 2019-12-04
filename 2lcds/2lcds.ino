// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd1(12, 5, 7, 8, 9, 10);
LiquidCrystal lcd2(12, 4, 7, 8, 9, 10);


void setup() {
  // set up the LCD's number of rows and columns: 
  lcd1.begin(16, 2);
  lcd2.begin(16, 2);
  

  // Print a message to the LCD.
  lcd1.print("Disp1");
  lcd2.print("Disp2");
  
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd1.setCursor(0, 1);
  lcd2.setCursor(0, 1);
  
 
 // print the number of seconds since reset:
  lcd1.print(millis()/1);
  lcd2.print(millis()/10);
  
}
