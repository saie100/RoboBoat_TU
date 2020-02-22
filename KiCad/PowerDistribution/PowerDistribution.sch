EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Power Distribution"
Date "2020-02-03"
Rev "1"
Comp "Temple University College of Engineering"
Comment1 "Author: Byron Gaspard"
Comment2 "Senior Design Project II"
Comment3 "RoboBoat - Team B04"
Comment4 ""
$EndDescr
$Comp
L pspice:VSOURCE V1
U 1 1 5E37390A
P 1150 6950
F 0 "V1" H 1378 6996 50  0000 L CNN
F 1 "22.2" H 1378 6905 50  0000 L CNN
F 2 "" H 1150 6950 50  0001 C CNN
F 3 "~" H 1150 6950 50  0001 C CNN
	1    1150 6950
	1    0    0    -1  
$EndComp
$Comp
L pspice:VSOURCE V2
U 1 1 5E374219
P 2350 6950
F 0 "V2" H 2578 6996 50  0000 L CNN
F 1 "12" H 2578 6905 50  0000 L CNN
F 2 "" H 2350 6950 50  0001 C CNN
F 3 "~" H 2350 6950 50  0001 C CNN
	1    2350 6950
	1    0    0    -1  
$EndComp
$Comp
L pspice:VSOURCE V3
U 1 1 5E3749D3
P 3500 6950
F 0 "V3" H 3728 6996 50  0000 L CNN
F 1 "11.1" H 3728 6905 50  0000 L CNN
F 2 "" H 3500 6950 50  0001 C CNN
F 3 "~" H 3500 6950 50  0001 C CNN
	1    3500 6950
	1    0    0    -1  
$EndComp
$Comp
L pspice:0 #GND01
U 1 1 5E3752E3
P 1150 7450
F 0 "#GND01" H 1150 7350 50  0001 C CNN
F 1 "0" H 1150 7350 50  0000 C CNN
F 2 "" H 1150 7450 50  0001 C CNN
F 3 "~" H 1150 7450 50  0001 C CNN
	1    1150 7450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 7450 1150 7250
$Comp
L pspice:0 #GND03
U 1 1 5E375CC6
P 2350 7450
F 0 "#GND03" H 2350 7350 50  0001 C CNN
F 1 "0" H 2350 7350 50  0000 C CNN
F 2 "" H 2350 7450 50  0001 C CNN
F 3 "~" H 2350 7450 50  0001 C CNN
	1    2350 7450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 7450 2350 7250
$Comp
L pspice:0 #GND04
U 1 1 5E376288
P 3500 7450
F 0 "#GND04" H 3500 7350 50  0001 C CNN
F 1 "0" H 3500 7350 50  0000 C CNN
F 2 "" H 3500 7450 50  0001 C CNN
F 3 "~" H 3500 7450 50  0001 C CNN
	1    3500 7450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 7450 3500 7250
Text GLabel 1000 6500 0    50   Input ~ 0
22.2V
Wire Wire Line
	1000 6500 1150 6500
Wire Wire Line
	1150 6500 1150 6650
Text GLabel 2200 6500 0    50   Input ~ 0
12V
Wire Wire Line
	2200 6500 2350 6500
Wire Wire Line
	2350 6500 2350 6650
Text GLabel 3350 6500 0    50   Input ~ 0
11.1V
Wire Wire Line
	3350 6500 3500 6500
Wire Wire Line
	3500 6500 3500 6650
NoConn ~ -5350 -3900
Wire Wire Line
	2700 1800 2700 1950
Wire Wire Line
	2150 1800 2150 2050
Wire Wire Line
	2700 1800 2150 1800
Wire Wire Line
	2700 1950 2850 1950
Connection ~ 2700 1800
Wire Wire Line
	2700 1650 2700 1800
Wire Wire Line
	2850 1650 2700 1650
Wire Wire Line
	3850 1850 3750 1850
Wire Wire Line
	3750 1750 3850 1750
Wire Wire Line
	3850 2250 3750 2250
Wire Wire Line
	3750 2150 3850 2150
Wire Wire Line
	2600 2350 2850 2350
Text GLabel 2600 2350 0    50   Input ~ 0
12V
Wire Wire Line
	2600 2050 2850 2050
Text GLabel 2600 2050 0    50   Input ~ 0
22.2V
Wire Wire Line
	2600 1550 2850 1550
Text GLabel 2600 1550 0    50   Input ~ 0
12V
Wire Wire Line
	2600 1250 2850 1250
Text GLabel 2600 1250 0    50   Input ~ 0
11.1V
Wire Wire Line
	3850 1400 3850 1450
Wire Wire Line
	3850 1450 3750 1450
Connection ~ 3850 1400
Wire Wire Line
	3850 1350 3850 1400
Wire Wire Line
	3750 1350 3850 1350
$Comp
L RoboBoat_Parts:ChangeoverSwitch SW1
U 1 1 5E38CAE2
P 3350 2050
F 0 "SW1" H 3300 3040 50  0000 C CNN
F 1 "ChangeoverSwitch" H 3300 2949 50  0000 C CNN
F 2 "" H 3250 3000 50  0001 C CNN
F 3 "http://cdn-reichelt.de/documents/datenblatt/C200/DS-Serie%23LOR.pdf" H 3250 3000 50  0001 C CNN
F 4 "R" H 3350 2050 50  0001 C CNN "Spice_Primitive"
F 5 "1" H 3350 2050 50  0001 C CNN "Spice_Model"
F 6 "N" H 3350 2050 50  0001 C CNN "Spice_Netlist_Enabled"
	1    3350 2050
	1    0    0    -1  
$EndComp
Text Notes 5450 750  0    50   ~ 10
Control Systems Power
$Comp
L Device:Fuse F8
U 1 1 5E3B0ADA
P 8250 2100
F 0 "F8" V 8150 2100 50  0000 C CNN
F 1 "3A" V 8350 2100 50  0000 C CNN
F 2 "" V 8180 2100 50  0001 C CNN
F 3 "~" H 8250 2100 50  0001 C CNN
	1    8250 2100
	0    1    1    0   
$EndComp
$Comp
L Device:Fuse F6
U 1 1 5E3A89A3
P 8250 1500
F 0 "F6" V 8150 1500 50  0000 C CNN
F 1 "7.5A" V 8350 1500 50  0000 C CNN
F 2 "" V 8180 1500 50  0001 C CNN
F 3 "~" H 8250 1500 50  0001 C CNN
	1    8250 1500
	0    1    1    0   
$EndComp
$Comp
L Device:Fuse F7
U 1 1 5E3B04A6
P 8250 1800
F 0 "F7" V 8150 1800 50  0000 C CNN
F 1 "3A" V 8350 1800 50  0000 C CNN
F 2 "" V 8180 1800 50  0001 C CNN
F 3 "~" H 8250 1800 50  0001 C CNN
	1    8250 1800
	0    1    1    0   
$EndComp
$Comp
L Device:Fuse F1
U 1 1 5E3D99CE
P 5350 1500
F 0 "F1" V 5250 1500 50  0000 C CNN
F 1 "3A" V 5450 1500 50  0000 C CNN
F 2 "" V 5280 1500 50  0001 C CNN
F 3 "~" H 5350 1500 50  0001 C CNN
	1    5350 1500
	0    1    1    0   
$EndComp
Wire Wire Line
	3850 1750 3850 1800
Wire Wire Line
	3850 2200 4250 2200
Wire Wire Line
	3850 2150 3850 2200
Connection ~ 3850 2200
Wire Wire Line
	3850 2200 3850 2250
Wire Wire Line
	3850 1800 4350 1800
Connection ~ 3850 1800
Wire Wire Line
	3850 1800 3850 1850
Wire Wire Line
	8600 950  8600 1100
Wire Wire Line
	5700 950  5700 1100
Wire Wire Line
	3850 1400 4250 1400
Wire Wire Line
	4250 950  4250 1400
Wire Wire Line
	4250 950  5700 950 
Wire Wire Line
	4350 2950 5700 2950
Wire Wire Line
	4250 3050 9550 3050
Text GLabel 7650 1500 0    50   Input ~ 0
StatusLights
Wire Wire Line
	7650 1500 7750 1500
Text GLabel 7650 1800 0    50   Input ~ 0
FeatherPower
Wire Wire Line
	7650 1800 7750 1800
Text GLabel 7600 2100 0    50   Input ~ 0
MotorRelay
Wire Wire Line
	7600 2100 7750 2100
$Comp
L RoboBoat_Parts:FuseBlock U2
U 1 1 5E397FFC
P 8600 1800
F 0 "U2" H 7900 2550 50  0000 C CNN
F 1 "FuseBlock" H 8050 2450 50  0000 C CNN
F 2 "" H 8600 1800 50  0001 C CNN
F 3 "" H 8600 1800 50  0001 C CNN
	1    8600 1800
	1    0    0    -1  
$EndComp
Text GLabel 4750 1500 0    50   Input ~ 0
Network
Wire Wire Line
	4750 1500 4850 1500
Wire Wire Line
	4750 1800 4850 1800
Text GLabel 4750 2100 0    50   Input ~ 0
RPi
Wire Wire Line
	4750 2100 4850 2100
$Comp
L Device:Fuse F3
U 1 1 5E4BBE9D
P 5350 2100
F 0 "F3" V 5250 2100 50  0000 C CNN
F 1 "3A" V 5450 2100 50  0000 C CNN
F 2 "" V 5280 2100 50  0001 C CNN
F 3 "~" H 5350 2100 50  0001 C CNN
	1    5350 2100
	0    1    1    0   
$EndComp
Text GLabel 4750 1800 0    50   Input ~ 0
TX2
Wire Wire Line
	6650 1500 6550 1500
Text GLabel 6300 2600 2    50   Input ~ 0
USB_Hub_GND
NoConn ~ 9450 1500
NoConn ~ 9450 1800
NoConn ~ 9450 2100
NoConn ~ 6550 2100
NoConn ~ 5900 2100
NoConn ~ 6200 2100
NoConn ~ 8800 1500
NoConn ~ 9100 1500
NoConn ~ 9100 1800
NoConn ~ 8800 1800
NoConn ~ 8800 2100
NoConn ~ 9100 2100
$Comp
L power:GND #PWR01
U 1 1 5E4E6F51
P 2150 2050
F 0 "#PWR01" H 2150 1800 50  0001 C CNN
F 1 "GND" H 2155 1877 50  0000 C CNN
F 2 "" H 2150 2050 50  0001 C CNN
F 3 "" H 2150 2050 50  0001 C CNN
	1    2150 2050
	1    0    0    -1  
$EndComp
Wire Notes Line
	3950 6200 3950 7700
Wire Notes Line
	550  7700 550  6200
Text Notes 1900 6300 0    50   ~ 10
Simulated Sources\n
Wire Notes Line
	550  7700 3950 7700
Wire Notes Line
	550  6200 3950 6200
$Comp
L Device:Fuse F4
U 1 1 5E3B062E
P 6050 1500
F 0 "F4" V 5950 1500 50  0000 C CNN
F 1 "3A" V 6150 1500 50  0000 C CNN
F 2 "" V 5980 1500 50  0001 C CNN
F 3 "~" H 6050 1500 50  0001 C CNN
	1    6050 1500
	0    1    1    0   
$EndComp
$Comp
L Device:Fuse F2
U 1 1 5E4B916C
P 5350 1800
F 0 "F2" V 5250 1800 50  0000 C CNN
F 1 "10A" V 5450 1800 50  0000 C CNN
F 2 "" V 5280 1800 50  0001 C CNN
F 3 "~" H 5350 1800 50  0001 C CNN
	1    5350 1800
	0    1    1    0   
$EndComp
$Comp
L RoboBoat_Parts:FuseBlock U1
U 1 1 5E3D99E0
P 5700 1800
F 0 "U1" H 5000 2550 50  0000 C CNN
F 1 "FuseBlock" H 5150 2450 50  0000 C CNN
F 2 "" H 5700 1800 50  0001 C CNN
F 3 "" H 5700 1800 50  0001 C CNN
	1    5700 1800
	1    0    0    -1  
$EndComp
NoConn ~ 6200 1800
NoConn ~ 5900 1800
NoConn ~ 6550 1800
Connection ~ 5700 2950
Wire Wire Line
	5700 2950 8600 2950
Wire Wire Line
	9550 950  8600 950 
Text GLabel 5100 2600 0    50   Input ~ 0
Network_GND
Text GLabel 5100 2800 0    50   Input ~ 0
RPi_GND
Text GLabel 5100 2700 0    50   Input ~ 0
TX2_GND
Wire Wire Line
	5100 2600 5200 2600
Wire Wire Line
	5200 2600 5200 2500
Wire Wire Line
	5100 2700 5350 2700
Wire Wire Line
	5350 2700 5350 2500
Wire Wire Line
	5100 2800 5500 2800
Wire Wire Line
	5500 2800 5500 2500
Wire Wire Line
	6200 2500 6200 2600
Wire Wire Line
	6200 2600 6300 2600
Text GLabel 6650 1500 2    50   Input ~ 0
USB_Hub
Wire Wire Line
	4350 1800 4350 2950
Wire Wire Line
	4250 2200 4250 3050
Wire Wire Line
	5700 2500 5700 2950
Wire Wire Line
	8600 2500 8600 2950
Text GLabel 8000 2600 0    50   Input ~ 0
StatusLights_GND
Text GLabel 8000 2700 0    50   Input ~ 0
FeatherPower_GND
Text GLabel 8000 2800 0    50   Input ~ 0
MotorRelay_GND
Wire Wire Line
	8000 2600 8100 2600
Wire Wire Line
	8100 2600 8100 2500
Wire Wire Line
	8000 2700 8250 2700
Wire Wire Line
	8250 2700 8250 2500
Wire Wire Line
	8000 2800 8400 2800
Wire Wire Line
	8400 2800 8400 2500
Wire Wire Line
	9550 950  9550 3050
Wire Notes Line
	9700 650  9700 3150
Wire Notes Line
	2000 650  2000 3150
Wire Notes Line
	2000 650  9700 650 
Wire Notes Line
	9700 3150 2000 3150
$Comp
L Switch:SW_SPST SW2
U 1 1 5E4BAB84
P 4300 4550
F 0 "SW2" H 4300 4785 50  0000 C CNN
F 1 "SW_SPST" H 4300 4694 50  0000 C CNN
F 2 "" H 4300 4550 50  0001 C CNN
F 3 "~" H 4300 4550 50  0001 C CNN
	1    4300 4550
	1    0    0    -1  
$EndComp
$Comp
L Device:CircuitBreaker_1P_US CB1
U 1 1 5E4BC0A2
P 5300 4250
F 0 "CB1" V 5575 4250 50  0000 C CNN
F 1 "CircuitBreaker_30A" V 5484 4250 50  0000 C CNN
F 2 "" H 5300 4250 50  0001 C CNN
F 3 "~" H 5300 4250 50  0001 C CNN
	1    5300 4250
	0    -1   -1   0   
$EndComp
$Comp
L Device:CircuitBreaker_1P_US CB2
U 1 1 5E4BE6E2
P 5300 4850
F 0 "CB2" V 5575 4850 50  0000 C CNN
F 1 "CircuitBreaker_30A" V 5484 4850 50  0000 C CNN
F 2 "" H 5300 4850 50  0001 C CNN
F 3 "~" H 5300 4850 50  0001 C CNN
	1    5300 4850
	0    -1   -1   0   
$EndComp
$Comp
L Relay:DIPxx-1Axx-11x K1
U 1 1 5E4BF112
P 6250 4050
F 0 "K1" V 5683 4050 50  0000 C CNN
F 1 "HE1AN-S-DC12V" V 5774 4050 50  0000 C CNN
F 2 "Relay_THT:Relay_StandexMeder_DIP_LowProfile" H 6600 4000 50  0001 L CNN
F 3 "https://media.digikey.com/pdf/Data%20Sheets/Panasonic%20Electric%20Works%20PDFs/HE%20Relays%20TV-10,15.pdf" H 6250 4050 50  0001 C CNN
	1    6250 4050
	0    1    1    0   
$EndComp
$Comp
L Relay:DIPxx-1Axx-11x K2
U 1 1 5E4C0BFE
P 6250 5050
F 0 "K2" V 6717 5050 50  0000 C CNN
F 1 "HE1AN-S-DC12V" V 6626 5050 50  0000 C CNN
F 2 "Relay_THT:Relay_StandexMeder_DIP_LowProfile" H 6600 5000 50  0001 L CNN
F 3 "https://media.digikey.com/pdf/Data%20Sheets/Panasonic%20Electric%20Works%20PDFs/HE%20Relays%20TV-10,15.pdf" H 6250 5050 50  0001 C CNN
	1    6250 5050
	0    1    -1   0   
$EndComp
Wire Wire Line
	5950 4850 5600 4850
Wire Wire Line
	5600 4250 5950 4250
Text GLabel 5700 3850 0    50   Input ~ 0
EmergencyRelayController
Text GLabel 5700 5250 0    50   Input ~ 0
EmergencyRelayController
Text GLabel 6800 3850 2    50   Input ~ 0
EmergencyRelayController_GND
Wire Wire Line
	6800 3850 6550 3850
Text GLabel 6800 5250 2    50   Input ~ 0
EmergencyRelayController_GND
Wire Wire Line
	6800 5250 6550 5250
Wire Wire Line
	5950 3850 5700 3850
Wire Wire Line
	5950 5250 5700 5250
Text GLabel 3950 4550 0    50   Input ~ 0
14.8V
Wire Wire Line
	3950 4550 4100 4550
Wire Wire Line
	5000 4250 4750 4250
Wire Wire Line
	4750 4850 5000 4850
Wire Wire Line
	4500 4550 4750 4550
Wire Wire Line
	4750 4250 4750 4550
Wire Wire Line
	4750 4550 4750 4850
Connection ~ 4750 4550
$Comp
L Motor:Motor_DC M2
U 1 1 5E4E7F26
P 7150 4850
F 0 "M2" V 7445 4800 50  0000 C CNN
F 1 "T200_Thruster" V 7354 4800 50  0000 C CNN
F 2 "" H 7150 4760 50  0001 C CNN
F 3 "~" H 7150 4760 50  0001 C CNN
	1    7150 4850
	0    -1   -1   0   
$EndComp
$Comp
L Motor:Motor_DC M1
U 1 1 5E4E880B
P 7150 4250
F 0 "M1" V 7445 4200 50  0000 C CNN
F 1 "T200_Thruster" V 7354 4200 50  0000 C CNN
F 2 "" H 7150 4160 50  0001 C CNN
F 3 "~" H 7150 4160 50  0001 C CNN
	1    7150 4250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6950 4250 6550 4250
Wire Wire Line
	6550 4850 6950 4850
$Comp
L power:GND #PWR02
U 1 1 5E4ED2A6
P 7950 4650
F 0 "#PWR02" H 7950 4400 50  0001 C CNN
F 1 "GND" H 7955 4477 50  0000 C CNN
F 2 "" H 7950 4650 50  0001 C CNN
F 3 "" H 7950 4650 50  0001 C CNN
	1    7950 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 4850 7700 4850
Wire Wire Line
	7700 4250 7450 4250
Wire Wire Line
	7950 4550 7700 4550
Wire Wire Line
	7700 4850 7700 4550
Wire Wire Line
	7700 4550 7700 4250
Connection ~ 7700 4550
Wire Wire Line
	7950 4650 7950 4550
Text Notes 5550 3400 0    50   ~ 10
Motor Power
Wire Notes Line
	8100 3300 8100 5500
Wire Notes Line
	8100 5500 3600 5500
Wire Notes Line
	3600 5500 3600 3300
Wire Notes Line
	3600 3300 8100 3300
$EndSCHEMATC
