PROJECT=h-bridge
SOURCES=$(PROJECT).c
MMCU=attiny84
F_CPU = 8000000
S_MMCU = t84

CFLAGS=-mmcu=$(MMCU) -Wall -Os -DF_CPU=$(F_CPU)

$(PROJECT).hex: $(PROJECT).out
	avr-objcopy -O ihex $(PROJECT).out $(PROJECT).c.hex;\
	avr-size --mcu=$(MMCU) --format=avr $(PROJECT).out

$(PROJECT).out: $(SOURCES)
	avr-gcc $(CFLAGS) -I./ -o $(PROJECT).out $(SOURCES)

program-avrisp2: $(PROJECT).hex
	avrdude -p $(S_MMCU) -P usb -c avrisp2 -U flash:w:$(PROJECT).c.hex

program-avrisp2-fuses: $(PROJECT).hex
	avrdude -p $(S_MMCU) -P usb -c avrisp2 -U lfuse:w:0x5E:m

flash: $(PROJECT).hex
	avrdude -p $(S_MMCU) -P usb -c usbtiny -U flash:w:$(PROJECT).c.hex

program-usbtiny-fuses: $(PROJECT).hex
	avrdude -p $(S_MMCU) -P usb -c usbtiny -U lfuse:w:0x5E:m

clean:
	rm $(PROJECT).c.hex $(PROJECT).out
