EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:switches
LIBS:SimpleLED-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L R_Small R1
U 1 1 5B461DEB
P 2700 3350
F 0 "R1" H 2750 3350 50  0000 L CNN
F 1 "100 ohms" V 2600 3200 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" H 2700 3350 50  0001 C CNN
F 3 "" H 2700 3350 50  0001 C CNN
	1    2700 3350
	0    -1   -1   0   
$EndComp
$Comp
L LED D1
U 1 1 5B461EAB
P 3000 3150
F 0 "D1" H 3000 3250 50  0000 C CNN
F 1 "LED" H 3000 3000 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 3000 3150 50  0001 C CNN
F 3 "" H 3000 3150 50  0001 C CNN
	1    3000 3150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2550 3250 2550 3350
Wire Wire Line
	2550 3350 2600 3350
Wire Wire Line
	2550 2900 2600 2900
$Comp
L Battery_Cell BT1
U 1 1 5B46490A
P 2550 3150
F 0 "BT1" H 2650 3250 50  0000 L CNN
F 1 "Battery_Cell" H 2000 3200 50  0000 L CNN
F 2 "My_Lib:bu-2032-1" V 2550 3210 50  0001 C CNN
F 3 "" V 2550 3210 50  0001 C CNN
	1    2550 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 2900 2550 2950
$Comp
L SW_Push SW1
U 1 1 5B464994
P 2800 2900
F 0 "SW1" H 2850 3000 50  0000 L CNN
F 1 "SW_Push" H 2800 2840 50  0000 C CNN
F 2 "Buttons_Switches_THT:SW_PUSH-12mm_Wuerth-430476085716" H 2800 3100 50  0001 C CNN
F 3 "" H 2800 3100 50  0001 C CNN
	1    2800 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 3350 3000 3350
Wire Wire Line
	3000 3350 3000 3300
Wire Wire Line
	3000 3000 3000 2900
$EndSCHEMATC
