//We always have to include the library
#include "LedControl.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(12,11,10,1);

/* we always wait a bit between updates of the display */
unsigned long delaytime=100;

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
}

void stern() {
  /* here is the data for the characters */
  byte a[8]={B00010000,B01010100,B00111000,B11111110,B00111000,B01010100,B00010000,B00000000};
  byte b[8]={B00010000,B00010000,B00111000,B11111110,B00111000,B00010000,B00010000,B00000000};
  byte c[8]={B00000000,B00010000,B00010000,B01111100,B00010000,B00010000,B00000000,B00000000};
  byte d[8]={B00000000,B00000000,B00010000,B00111000,B00010000,B00000000,B00000000,B00000000};
  byte e[8]={B00000000,B00000000,B00000000,B00010000,B00000000,B00000000,B00000000,B00000000};
  
  
  
  
 stern2led(a); 
 delay(delaytime); 
 stern2led(b); 
 delay(delaytime); 
 stern2led(c); 
 delay(delaytime); 
 stern2led(d);
 delay(delaytime); 
 stern2led(e);
 delay(delaytime); 
 lc.clearDisplay(0);
 delay(delaytime);
 stern2led(e);
 delay(delaytime); 
 stern2led(d);
 delay(delaytime); 
 stern2led(c);
 delay(delaytime); 
 stern2led(b);
 delay(delaytime); 
 stern2led(a);
 
}


void stern2led(byte a[]) {
  for(int row=0;row<8;row++) {
      lc.setRow(0,row,a[row]);  
  }
}




void loop() { 
  stern();
  
}
