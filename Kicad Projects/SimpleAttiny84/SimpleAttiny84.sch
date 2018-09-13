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
LIBS:SimpleAttiny84-cache
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
L Conn_02x03_Odd_Even J5
U 1 1 5B4E216F
P 7750 5450
F 0 "J5" H 7800 5650 50  0000 C CNN
F 1 "Conn_02x03_Odd_Even" H 7800 5250 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x03_Pitch2.54mm_SMD" H 7750 5450 50  0001 C CNN
F 3 "" H 7750 5450 50  0001 C CNN
	1    7750 5450
	1    0    0    -1  
$EndComp
$Comp
L ATTINY84-20SSU U1
U 1 1 5B4E221D
P 5700 4250
F 0 "U1" H 4850 5000 50  0000 C CNN
F 1 "ATTINY84-20SSU" H 6400 3500 50  0000 C CNN
F 2 "Housings_SOIC:SOIC-14_3.9x8.7mm_Pitch1.27mm" H 5700 4050 50  0001 C CIN
F 3 "" H 5700 4250 50  0001 C CNN
	1    5700 4250
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x01 J2
U 1 1 5B4E236A
P 3550 4900
F 0 "J2" H 3550 5000 50  0000 C CNN
F 1 "Conn_01x01" H 3550 4800 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.54mm" H 3550 4900 50  0001 C CNN
F 3 "" H 3550 4900 50  0001 C CNN
	1    3550 4900
	-1   0    0    1   
$EndComp
$Comp
L Conn_01x01 J1
U 1 1 5B4E23C5
P 3500 3600
F 0 "J1" H 3500 3700 50  0000 C CNN
F 1 "Conn_01x01" H 3500 3500 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.54mm" H 3500 3600 50  0001 C CNN
F 3 "" H 3500 3600 50  0001 C CNN
	1    3500 3600
	-1   0    0    1   
$EndComp
$Comp
L C C1
U 1 1 5B4E2AF2
P 4550 4200
F 0 "C1" H 4575 4300 50  0000 L CNN
F 1 "C" H 4575 4100 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 4588 4050 50  0001 C CNN
F 3 "" H 4550 4200 50  0001 C CNN
	1    4550 4200
	-1   0    0    1   
$EndComp
$Comp
L R R1
U 1 1 5B4E3B3D
P 4600 6350
F 0 "R1" V 4700 6300 50  0000 C CNN
F 1 "R" V 4600 6350 50  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 4530 6350 50  0001 C CNN
F 3 "" H 4600 6350 50  0001 C CNN
	1    4600 6350
	0    -1   -1   0   
$EndComp
$Comp
L Conn_01x06 J6
U 1 1 5B4E5E3B
P 5850 5150
F 0 "J6" H 5850 5450 50  0000 C CNN
F 1 "Conn_01x06" H 5850 4750 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x06_Pitch2.54mm" H 5850 5150 50  0001 C CNN
F 3 "" H 5850 5150 50  0001 C CNN
	1    5850 5150
	0    -1   -1   0   
$EndComp
$Comp
L Conn_01x06 J7
U 1 1 5B4E5E94
P 5850 6050
F 0 "J7" H 5850 6350 50  0000 C CNN
F 1 "Conn_01x06" H 5850 5650 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x06_Pitch2.54mm" H 5850 6050 50  0001 C CNN
F 3 "" H 5850 6050 50  0001 C CNN
	1    5850 6050
	0    -1   1    0   
$EndComp
Wire Wire Line
	4200 4850 4200 6450
Wire Wire Line
	4200 4850 4650 4850
Wire Wire Line
	4650 3600 4650 3650
Wire Wire Line
	3700 3600 4650 3600
Wire Wire Line
	4550 4050 4550 3600
Connection ~ 4550 3600
Wire Wire Line
	4550 4850 4550 4350
Connection ~ 4550 4850
Wire Wire Line
	4200 4900 3750 4900
Connection ~ 4200 4900
Wire Wire Line
	4350 3600 4350 5800
Wire Wire Line
	4350 3600 4300 3600
Connection ~ 4300 3600
Wire Wire Line
	6750 4050 7450 4050
Wire Wire Line
	8050 5350 8050 3350
Wire Wire Line
	8050 3350 4300 3350
Wire Wire Line
	4300 3350 4300 3600
Wire Wire Line
	8050 5550 8050 6450
Wire Wire Line
	8050 6450 4200 6450
Connection ~ 4200 5650
Wire Wire Line
	8550 5450 8050 5450
Wire Wire Line
	3900 3600 3900 6350
Connection ~ 3900 3600
Wire Wire Line
	4750 6350 7550 6350
Wire Wire Line
	7300 3650 6750 3650
Wire Wire Line
	7250 3750 6750 3750
Wire Wire Line
	7200 3850 6750 3850
Wire Wire Line
	7150 3950 6750 3950
Wire Wire Line
	7550 6350 7550 5550
Wire Wire Line
	6750 6350 6750 4850
Connection ~ 6750 6350
Wire Wire Line
	8550 4250 8550 5450
Wire Wire Line
	6750 4150 7350 4150
Wire Wire Line
	7350 4150 7350 5350
Wire Wire Line
	7350 5350 7550 5350
Wire Wire Line
	7550 5450 7450 5450
Wire Wire Line
	7450 5450 7450 4050
Wire Wire Line
	8550 4250 6750 4250
Wire Wire Line
	5750 5350 5750 5850
Wire Wire Line
	5850 5350 5850 5850
Wire Wire Line
	5950 5350 5950 5850
Wire Wire Line
	4350 5800 5550 5850
Wire Wire Line
	4200 5450 6150 5450
Connection ~ 4200 5450
Wire Wire Line
	5950 5800 7300 5800
Wire Wire Line
	7300 5800 7300 3650
Connection ~ 5950 5800
Wire Wire Line
	5850 5750 7250 5750
Wire Wire Line
	7250 5750 7250 3750
Connection ~ 5850 5750
Wire Wire Line
	5750 5700 7200 5700
Wire Wire Line
	7200 5700 7200 3850
Connection ~ 5750 5700
Wire Wire Line
	7150 3950 7150 5650
Wire Wire Line
	5650 5350 5650 5850
Wire Wire Line
	7150 5650 5650 5650
Connection ~ 5650 5650
Wire Wire Line
	3900 6350 4450 6350
Wire Wire Line
	5550 5850 6050 5850
Wire Wire Line
	6150 5350 6150 5850
Connection ~ 6150 5450
Wire Wire Line
	6050 5850 6050 5350
$EndSCHEMATC
