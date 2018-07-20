# Electronics
# Attiny 84


## Bit Shifting: 

#### Set a bit(output)
byte |= (1 << pin_number) 
byte = byte | (1<< pin_number) 
10000000
or: doesn’t overwrite. 
because if u compare it as u do as multiplication 0 and a 1 will give out a high and 1 and 1 will still give a high yaya. 

#### Clear a bit(input) 
and: Overwrites (for 0)
byte &= ~(1<<pin_number) 
 ~: Flip all the bits

#### Checking a bit
Use and. Value shifted over to the rite(bit u wanna check)
and one. 
if (!(byte1 >> 2) & 1  == (old_byte1 >>2) &1)

## Pushing Firmware
Use "Make" to compile new .hex and .out
Make File contains all the commands in terminal: 
If like there are different libraries: (aka if I switch a different type of chip) *make clean*. 
Clean it to make completely new hex and out files--> Command: make clean
Make program-usbtiny (Or whatever programmer you're using) → to take the firmware and put it into the microbit. 

