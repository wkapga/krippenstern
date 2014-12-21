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
unsigned long delaytime=33;
// uint8_t pic[5][8] = {0};

byte pic [] = { 
  B00000000,B00000000,B00000000,B11110000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B10000000,B01100000,B00010000,B00000000,B00000000,B00000000,B00000000,
  B10000000,B01000000,B00100000,B00010000,B00000000,B00000000,B00000000,B00000000,
  B01000000,B00100000,B00100000,B00010000,B00000000,B00000000,B00000000,B00000000 };
  



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
 stern2led(b); 
 stern2led(c); 
 stern2led(d);
 stern2led(e);
 lc.clearDisplay(0);
 stern2led(e);
 stern2led(d);
 stern2led(c);
 stern2led(b);
 stern2led(a);
}




void sternrot() {

  //left down 
  for(int i=0;i<4;i++) {
    for(int row=0;row<8;row++) {
      lc.setColumn(0,row,mirror(pic[i*8+row]) << 1);
    }
    delay(delaytime);
  }
  
  //left up normal
  for(int i=0;i<4;i++) {
    for(int row=0;row<8;row++) {
      lc.setRow(0,row,pic[i*8+row] );
    }
    delay(delaytime);
  }
  
  // right up
  for(int i=0;i<4;i++) {
    for(int row=0;row<9;row++) {
      lc.setColumn(0,row,(pic[(i+1)*8-row-2]));
    }
    delay(delaytime);
  }
   
  // right bottom:mirror x & y
  for(int i=0;i<4;i++) {
    for(int row=0;row<9;row++) {
      lc.setRow(0,row,mirror(pic[(i+1)*8-row-2]) << 1);
    }
    delay(delaytime);
  }
  

}

unsigned char mirror( unsigned char a )
{
  a = ((a >> 4) & 0x0F) | ((a << 4) & 0xF0);
  a = ((a >> 2) & 0x33) | ((a << 2) & 0xCC);
  a = ((a >> 1) & 0x55) | ((a << 1) & 0xAA);

  return a;
}





void stern2led(byte a[]) {
  for(int row=0;row<8;row++) {
      lc.setRow(0,row,a[row]);  
  }
  delay(delaytime*3);
}



void loop() { 
 for(int i=0;i<8;i++) { stern(); };
 for(int i=0;i<3;i++) { sternrot(); };

}
