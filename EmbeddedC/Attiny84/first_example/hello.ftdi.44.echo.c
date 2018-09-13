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

#define output(directions,pin) (directions |= pin) // set port direction for output
#define set(port,pin) (port |= pin) // set port pin
#define clear(port,pin) (port &= (~pin)) // clear port pin
#define pin_test(pins,pin) (pins & pin) // test for port pin
#define bit_test(byte,bit) (byte & (1 << bit)) // test for bit set
#define bit_delay_time 8.5 // bit delay for 115200 with overhead
#define bit_delay() _delay_us(bit_delay_time) // RS232 bit delay
#define half_bit_delay() _delay_us(bit_delay_time/2) // RS232 half bit delay
#define char_delay() _delay_ms(10) // char delay

#define serial_port PORTA
#define serial_direction DDRA
#define serial_pins PINA
#define serial_pin_in (1 << PA0)
#define serial_pin_out (1 << PA1)

#define max_buffer 25


int main(void) {
   //
   // set clock divider to /1
   //
   CLKPR = (1 << CLKPCE);
   CLKPR = (0 << CLKPS3) | (0 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0);
   //Setting Direciotns
   DDRA = (1<<DDA0);
   PORTA = (1<<PA1);
   while (1) {
     //Toggling sleep command
     //Toggling PORTX Registor
     //PINA = (1<<PINA0);
    uint8_t i = (PINA >> PINA1) & 1;
    if (i == 0)
     {
       //Or so that it dosen't change everything n mess lfiei up :D
       PORTA |= (1<<PA0);
       _delay_ms(5000);
       //Write it out n think it thorugh
       PORTA &= ~(1<<PA0);
     }
     //Reading Pins

   }
 }
