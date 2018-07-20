//
//
// hello.ftdi.44.echo.c
//
// 115200 baud FTDI character echo, with flash string
//
// set lfuse to 0x5E for 20 MHz xtal
//
// Neil Gershenfeld
// 12/8/10
//
// (c) Massachusetts Institute of Technology 2010
// This work may be reproduced, modified, distributed,
// performed, and displayed for any purpose. Copyright is
// retained and must be preserved. The work is provided
// as is; no warranty is provided, and users accept all
// liability.
//

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>


int main(void) {
  uint8_t m_forward, m_back;
   //
   // set clock divider to /1
   //
   CLKPR = (1 << CLKPCE);
   CLKPR = (0 << CLKPS3) | (0 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0);
   //Setting Direciotns
   PORTA = (1<<PA1) | (1<<PA0);
   DDRA = (1<<DDRA4) | (1<<DDRA3);
   while (1) {
     //Toggling sleep command
     //Toggling PORTX Registor
     //PINA = (1<<PINA0);
    m_forward = (PINA >> PINA0) & 1;
    m_backward = (PINA >> PINA1) & 1;
    //Both Low (which means both buttons r pressed since pull up inverts it)
    if (!m_forward && !m_backward)
    {
      //clear the both pins
      PORTA &= ~((1<<PA1) | (1<<PA0));

    }
    //One High One Low
    else if (m_forward){
      //FIRST MAKE SURE ONE IS LOW
      PORTA &= ~(1<<PA3);
      PORTA |= (1<<PA4);
    }

    else if(m_backward){
      //FIRST MAKE SURE ONE IS LOW
      PORTA &= ~(1<<PA4);
      PORTA |= (1<<PA3);
    }
    //Both high, which is the default resting state. and I want the motor to turn off.
    else{
      PORTA &= ~((1<<PA1) | (1<<PA0));
    }

   }
 }
