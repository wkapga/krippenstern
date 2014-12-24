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

const byte pic [] = { 
  B00000000,B00000000,B00000000,B11110000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B10000000,B01100000,B00010000,B00000000,B00000000,B00000000,B00000000,
  B10000000,B01000000,B00100000,B00010000,B00000000,B00000000,B00000000,B00000000,
  B01000000,B00100000,B00100000,B00010000,B00000000,B00000000,B00000000,B00000000 };
  
const byte sternpic [] ={
  B00010000,B01010100,B00111000,B11111110,B00111000,B01010100,B00010000,B00000000,
  B00010000,B00010000,B00111000,B11111110,B00111000,B00010000,B00010000,B00000000,
  B00000000,B00010000,B00010000,B01111100,B00010000,B00010000,B00000000,B00000000,
  B00000000,B00000000,B00010000,B00111000,B00010000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00010000,B00000000,B00000000,B00000000,B00000000};
  



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

void stern2() {
  for(int i=0;i<5;i++) { 
    for(int row=0;row<8;row++) {
        lc.setRow(0,row,sternpic[i*8+row]);  
    }
    delay(delaytime*3);
  }
 lc.clearDisplay(0);
 delay(delaytime*3);
  for(int i=0;i<5;i++) { 
    for(int row=0;row<8;row++) {
        lc.setRow(0,row,sternpic[(4-i)*8+row]);  
    }
    delay(delaytime*3);
  } 
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


void kl_stern(int x, int y) {
 lc.setLed(0,x,y,true);
 delay(3*delaytime);
 lc.setLed(0,x+1,y,true);
 lc.setLed(0,x,y+1,true);
 lc.setLed(0,x-1,y,true);
 lc.setLed(0,x,y-1,true);
 delay(5*delaytime);
 lc.clearDisplay(0);
 lc.setLed(0,x,y,true);
 delay(3*delaytime);
 lc.setLed(0,x,y,false);
 delay(8*delaytime);
 

}



void loop() { 
 for(int i=0;i<8;i++) { stern2(); };
 lc.clearDisplay(0);
 // for(int i=0;i<3;i++) { sternrot(); };
 for(int i=0;i<9;i++) {kl_stern(random(1,7),random(1,7)); }
 for(int i=1;i<7;i++) {kl_stern(i,i); };
 kl_stern(6,6);
 for(int i=1;i<7;i++) {kl_stern(7-i,7-i); };
}
