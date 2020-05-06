EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Battery Monitor"
Date "2020-04-25"
Rev "2"
Comp "Temple University College of Engineering"
Comment1 "Author: Byron Gaspard"
Comment2 "Senior Design Project II"
Comment3 "RoboBoat - Team B04"
Comment4 ""
$EndDescr
$Comp
L RoboBoat_Arduino:MEGA2560_V3 U1
U 1 1 5E32039F
P 9100 4200
F 0 "U1" H 9100 5575 50  0000 C CNN
F 1 "MEGA2560_V3" H 9100 5484 50  0000 C CNN
F 2 "" H 8700 5350 50  0001 C CNN
F 3 "" H 8700 5350 50  0001 C CNN
F 4 "R" H 9100 4200 50  0001 C CNN "Spice_Primitive"
F 5 "100me" H 9100 4200 50  0001 C CNN "Spice_Model"
F 6 "N" H 9100 4200 50  0001 C CNN "Spice_Netlist_Enabled"
	1    9100 4200
	1    0    0    -1  
$EndComp
Text GLabel 1000 2800 0    50   Input ~ 0
B1_C6
Text GLabel 1000 2450 0    50   Input ~ 0
B1_C5
Text GLabel 1000 2100 0    50   Input ~ 0
B1_C4
Text GLabel 1000 1750 0    50   Input ~ 0
B1_C3
Text GLabel 1000 1400 0    50   Input ~ 0
B1_C2
$Comp
L Device:R_US R5
U 1 1 5E4B64F9
P 1400 2800
F 0 "R5" V 1300 2800 50  0000 C CNN
F 1 "R_US" V 1500 2800 50  0001 C CNN
F 2 "" V 1440 2790 50  0001 C CNN
F 3 "~" H 1400 2800 50  0001 C CNN
F 4 "R" H 1400 2800 50  0001 C CNN "Spice_Primitive"
F 5 "560e3" V 1500 2800 50  0000 C CNN "Spice_Model"
F 6 "Y" H 1400 2800 50  0001 C CNN "Spice_Netlist_Enabled"
	1    1400 2800
	0    -1   1    0   
$EndComp
$Comp
L Device:R_US R3
U 1 1 5E4B6502
P 1400 2100
F 0 "R3" V 1300 2100 50  0000 C CNN
F 1 "R_US" V 1500 2100 50  0001 C CNN
F 2 "" V 1440 2090 50  0001 C CNN
F 3 "~" H 1400 2100 50  0001 C CNN
F 4 "R" H 1400 2100 50  0001 C CNN "Spice_Primitive"
F 5 "560e3" V 1500 2100 50  0000 C CNN "Spice_Model"
F 6 "Y" H 1400 2100 50  0001 C CNN "Spice_Netlist_Enabled"
	1    1400 2100
	0    -1   1    0   
$EndComp
$Comp
L Device:R_US R2
U 1 1 5E4B650B
P 1400 1750
F 0 "R2" V 1300 1750 50  0000 C CNN
F 1 "R_US" V 1500 1750 50  0001 C CNN
F 2 "" V 1440 1740 50  0001 C CNN
F 3 "~" H 1400 1750 50  0001 C CNN
F 4 "R" H 1400 1750 50  0001 C CNN "Spice_Primitive"
F 5 "560e3" V 1500 1750 50  0000 C CNN "Spice_Model"
F 6 "Y" H 1400 1750 50  0001 C CNN "Spice_Netlist_Enabled"
	1    1400 1750
	0    -1   1    0   
$EndComp
$Comp
L Device:R_US R1
U 1 1 5E4B6514
P 1400 1400
F 0 "R1" V 1300 1400 50  0000 C CNN
F 1 "R_US" V 1500 1400 50  0001 C CNN
F 2 "" V 1440 1390 50  0001 C CNN
F 3 "~" H 1400 1400 50  0001 C CNN
F 4 "R" H 1400 1400 50  0001 C CNN "Spice_Primitive"
F 5 "560e3" V 1500 1400 50  0000 C CNN "Spice_Model"
F 6 "Y" H 1400 1400 50  0001 C CNN "Spice_Netlist_Enabled"
	1    1400 1400
	0    -1   1    0   
$EndComp
$Comp
L Device:R_US R4
U 1 1 5E4B651D
P 1400 2450
F 0 "R4" V 1300 2450 50  0000 C CNN
F 1 "R_US" V 1500 2450 50  0001 C CNN
F 2 "" V 1440 2440 50  0001 C CNN
F 3 "~" H 1400 2450 50  0001 C CNN
F 4 "R" H 1400 2450 50  0001 C CNN "Spice_Primitive"
F 5 "560e3" V 1500 2450 50  0000 C CNN "Spice_Model"
F 6 "Y" H 1400 2450 50  0001 C CNN "Spice_Netlist_Enabled"
	1    1400 2450
	0    -1   1    0   
$EndComp
$Comp
L Device:R_US R7
U 1 1 5E4B64E0
P 2150 1400
F 0 "R7" V 2050 1400 50  0000 C CNN
F 1 "R_US" V 2250 1400 50  0001 C CNN
F 2 "" V 2190 1390 50  0001 C CNN
F 3 "~" H 2150 1400 50  0001 C CNN
F 4 "R" H 2150 1400 50  0001 C CNN "Spice_Primitive"
F 5 "470e3" V 2250 1400 50  0000 C CNN "Spice_Model"
F 6 "Y" H 2150 1400 50  0001 C CNN "Spice_Netlist_Enabled"
	1    2150 1400
	0    -1   1    0   
$EndComp
$Comp
L Device:R_US R8
U 1 1 5E4B64D7
P 2150 1750
F 0 "R8" V 2050 1750 50  0000 C CNN
F 1 "330k" V 2250 1750 50  0001 C CNN
F 2 "" V 2190 1740 50  0001 C CNN
F 3 "~" H 2150 1750 50  0001 C CNN
F 4 "R" H 2150 1750 50  0001 C CNN "Spice_Primitive"
F 5 "330e3" V 2250 1750 50  0000 C CNN "Spice_Model"
F 6 "Y" H 2150 1750 50  0001 C CNN "Spice_Netlist_Enabled"
	1    2150 1750
	0    -1   1    0   
$EndComp
$Comp
L Device:R_US R9
U 1 1 5E4B64CE
P 2150 2100
F 0 "R9" V 2050 2100 50  0000 C CNN
F 1 "R_US" V 2250 2100 50  0001 C CNN
F 2 "" V 2190 2090 50  0001 C CNN
F 3 "~" H 2150 2100 50  0001 C CNN
F 4 "R" H 2150 2100 50  0001 C CNN "Spice_Primitive"
F 5 "180e3" V 2250 2100 50  0000 C CNN "Spice_Model"
F 6 "Y" H 2150 2100 50  0001 C CNN "Spice_Netlist_Enabled"
	1    2150 2100
	0    -1   1    0   
$EndComp
$Comp
L Device:R_US R10
U 1 1 5E4B64C5
P 2150 2450
F 0 "R10" V 2050 2450 50  0000 C CNN
F 1 "R_US" V 2250 2450 50  0001 C CNN
F 2 "" V 2190 2440 50  0001 C CNN
F 3 "~" H 2150 2450 50  0001 C CNN
F 4 "R" H 2150 2450 50  0001 C CNN "Spice_Primitive"
F 5 "150e3" V 2250 2450 50  0000 C CNN "Spice_Model"
F 6 "Y" H 2150 2450 50  0001 C CNN "Spice_Netlist_Enabled"
	1    2150 2450
	0    -1   1    0   
$EndComp
$Comp
L Device:R_US R11
U 1 1 5E4B64BC
P 2150 2800
F 0 "R11" V 2050 2800 50  0000 C CNN
F 1 "R_US" V 2250 2800 50  0001 C CNN
F 2 "" V 2190 2790 50  0001 C CNN
F 3 "~" H 2150 2800 50  0001 C CNN
F 4 "R" H 2150 2800 50  0001 C CNN "Spice_Primitive"
F 5 "100e3" V 2250 2800 50  0000 C CNN "Spice_Model"
F 6 "Y" H 2150 2800 50  0001 C CNN "Spice_Netlist_Enabled"
	1    2150 2800
	0    -1   1    0   
$EndComp
Wire Wire Line
	1000 1400 1250 1400
Wire Wire Line
	1000 1750 1250 1750
Wire Wire Line
	1000 2100 1250 2100
Wire Wire Line
	1000 2800 1250 2800
Wire Wire Line
	1000 2450 1250 2450
Wire Wire Line
	1550 1400 1600 1400
Wire Wire Line
	1550 1750 1600 1750
Wire Wire Line
	1550 2100 1600 2100
Wire Wire Line
	1550 2450 1600 2450
Wire Wire Line
	1550 2800 1600 2800
Wire Wire Line
	1600 1250 1600 1400
Connection ~ 1600 1400
Wire Wire Line
	1600 1400 2000 1400
Wire Wire Line
	1600 1600 1600 1750
Connection ~ 1600 1750
Wire Wire Line
	1600 1750 2000 1750
Wire Wire Line
	1600 1950 1600 2100
Connection ~ 1600 2100
Wire Wire Line
	1600 2100 2000 2100
Wire Wire Line
	1600 2300 1600 2450
Connection ~ 1600 2450
Wire Wire Line
	1600 2450 2000 2450
Wire Wire Line
	1600 2650 1600 2800
Connection ~ 1600 2800
Wire Wire Line
	1600 2800 2000 2800
Text GLabel 4500 1950 2    50   Input ~ 0
A09
Text GLabel 4500 1600 2    50   Input ~ 0
A08
Text GLabel 4500 1250 2    50   Input ~ 0
A07
Text GLabel 4500 900  2    50   Input ~ 0
A06
Wire Wire Line
	5200 1050 5100 1050
Wire Wire Line
	5200 1400 5100 1400
Wire Wire Line
	5200 1750 5100 1750
Wire Wire Line
	5200 2100 5100 2100
Wire Wire Line
	5200 1050 5200 1400
Connection ~ 5200 1400
Wire Wire Line
	5200 1400 5200 1750
Connection ~ 5200 1750
Wire Wire Line
	5200 1750 5200 2100
Text GLabel 3800 2100 0    50   Input ~ 0
B2_C4
Text GLabel 3800 1750 0    50   Input ~ 0
B2_C3
Text GLabel 3800 1400 0    50   Input ~ 0
B2_C2
Text GLabel 3800 1050 0    50   Input ~ 0
B2_C1
$Comp
L Device:R_US R14
U 1 1 5E61A26E
P 4200 2100
F 0 "R14" V 4100 2100 50  0000 C CNN
F 1 "R_US" V 4300 2100 50  0001 C CNN
F 2 "" V 4240 2090 50  0001 C CNN
F 3 "~" H 4200 2100 50  0001 C CNN
F 4 "R" H 4200 2100 50  0001 C CNN "Spice_Primitive"
F 5 "560e3" V 4300 2100 50  0000 C CNN "Spice_Model"
F 6 "Y" H 4200 2100 50  0001 C CNN "Spice_Netlist_Enabled"
	1    4200 2100
	0    -1   1    0   
$EndComp
$Comp
L Device:R_US R13
U 1 1 5E61A277
P 4200 1750
F 0 "R13" V 4100 1750 50  0000 C CNN
F 1 "R_US" V 4300 1750 50  0001 C CNN
F 2 "" V 4240 1740 50  0001 C CNN
F 3 "~" H 4200 1750 50  0001 C CNN
F 4 "R" H 4200 1750 50  0001 C CNN "Spice_Primitive"
F 5 "560e3" V 4300 1750 50  0000 C CNN "Spice_Model"
F 6 "Y" H 4200 1750 50  0001 C CNN "Spice_Netlist_Enabled"
	1    4200 1750
	0    -1   1    0   
$EndComp
$Comp
L Device:R_US R12
U 1 1 5E61A280
P 4200 1400
F 0 "R12" V 4100 1400 50  0000 C CNN
F 1 "R_US" V 4300 1400 50  0001 C CNN
F 2 "" V 4240 1390 50  0001 C CNN
F 3 "~" H 4200 1400 50  0001 C CNN
F 4 "R" H 4200 1400 50  0001 C CNN "Spice_Primitive"
F 5 "560e3" V 4300 1400 50  0000 C CNN "Spice_Model"
F 6 "Y" H 4200 1400 50  0001 C CNN "Spice_Netlist_Enabled"
	1    4200 1400
	0    -1   1    0   
$EndComp
$Comp
L Device:R_US R15
U 1 1 5E61A292
P 4950 1050
F 0 "R15" V 4850 1050 50  0000 C CNN
F 1 "R_US" V 5050 1050 50  0001 C CNN
F 2 "" V 4990 1040 50  0001 C CNN
F 3 "~" H 4950 1050 50  0001 C CNN
F 4 "R" H 4950 1050 50  0001 C CNN "Spice_Primitive"
F 5 "56e3" V 5050 1050 50  0000 C CNN "Spice_Model"
F 6 "Y" H 4950 1050 50  0001 C CNN "Spice_Netlist_Enabled"
	1    4950 1050
	0    -1   1    0   
$EndComp
$Comp
L Device:R_US R16
U 1 1 5E61A29B
P 4950 1400
F 0 "R16" V 4850 1400 50  0000 C CNN
F 1 "R_US" V 5050 1400 50  0001 C CNN
F 2 "" V 4990 1390 50  0001 C CNN
F 3 "~" H 4950 1400 50  0001 C CNN
F 4 "R" H 4950 1400 50  0001 C CNN "Spice_Primitive"
F 5 "470e3" V 5050 1400 50  0000 C CNN "Spice_Model"
F 6 "Y" H 4950 1400 50  0001 C CNN "Spice_Netlist_Enabled"
	1    4950 1400
	0    -1   1    0   
$EndComp
$Comp
L Device:R_US R17
U 1 1 5E61A2A4
P 4950 1750
F 0 "R17" V 4850 1750 50  0000 C CNN
F 1 "330k" V 5050 1750 50  0001 C CNN
F 2 "" V 4990 1740 50  0001 C CNN
F 3 "~" H 4950 1750 50  0001 C CNN
F 4 "R" H 4950 1750 50  0001 C CNN "Spice_Primitive"
F 5 "330e3" V 5050 1750 50  0000 C CNN "Spice_Model"
F 6 "Y" H 4950 1750 50  0001 C CNN "Spice_Netlist_Enabled"
	1    4950 1750
	0    -1   1    0   
$EndComp
$Comp
L Device:R_US R18
U 1 1 5E61A2AD
P 4950 2100
F 0 "R18" V 4850 2100 50  0000 C CNN
F 1 "R_US" V 5050 2100 50  0001 C CNN
F 2 "" V 4990 2090 50  0001 C CNN
F 3 "~" H 4950 2100 50  0001 C CNN
F 4 "R" H 4950 2100 50  0001 C CNN "Spice_Primitive"
F 5 "180e3" V 5050 2100 50  0000 C CNN "Spice_Model"
F 6 "Y" H 4950 2100 50  0001 C CNN "Spice_Netlist_Enabled"
	1    4950 2100
	0    -1   1    0   
$EndComp
Wire Wire Line
	3800 1400 4050 1400
Wire Wire Line
	3800 1750 4050 1750
Wire Wire Line
	3800 2100 4050 2100
Wire Wire Line
	4350 1400 4400 1400
Wire Wire Line
	4350 1750 4400 1750
Wire Wire Line
	4350 2100 4400 2100
Wire Wire Line
	3800 1050 4400 1050
Wire Wire Line
	4500 900  4400 900 
Wire Wire Line
	4400 900  4400 1050
Connection ~ 4400 1050
Wire Wire Line
	4400 1050 4800 1050
Wire Wire Line
	4500 1250 4400 1250
Wire Wire Line
	4400 1250 4400 1400
Wire Wire Line
	4500 1600 4400 1600
Wire Wire Line
	4500 1950 4400 1950
Connection ~ 4400 1400
Wire Wire Line
	4400 1400 4800 1400
Wire Wire Line
	4400 1600 4400 1750
Connection ~ 4400 1750
Wire Wire Line
	4400 1750 4800 1750
Wire Wire Line
	4400 1950 4400 2100
Connection ~ 4400 2100
Wire Wire Line
	4400 2100 4800 2100
Wire Wire Line
	5200 2100 5200 2250
Connection ~ 5200 2100
Wire Wire Line
	8550 4550 8250 4550
Wire Wire Line
	8550 4650 8250 4650
Wire Wire Line
	8550 4850 8250 4850
Wire Wire Line
	8550 4950 8250 4950
Wire Wire Line
	8550 5150 8250 5150
Wire Wire Line
	8550 5250 8250 5250
Wire Wire Line
	8550 5350 8250 5350
Wire Wire Line
	8550 5450 8250 5450
Wire Wire Line
	8550 5550 8250 5550
Text GLabel 8250 4550 0    50   Input ~ 0
A06
Text GLabel 8250 4650 0    50   Input ~ 0
A07
Text GLabel 8250 4850 0    50   Input ~ 0
A08
Text GLabel 10250 1600 2    50   Input ~ 0
A15
Text GLabel 10250 1250 2    50   Input ~ 0
A14
Text GLabel 10250 900  2    50   Input ~ 0
A13
Wire Wire Line
	10950 1050 10850 1050
Wire Wire Line
	10950 1400 10850 1400
Wire Wire Line
	10950 1750 10850 1750
Wire Wire Line
	10950 1050 10950 1400
Text GLabel 9550 1750 0    50   Input ~ 0
B4_C3
Text GLabel 9550 1400 0    50   Input ~ 0
B4_C2
Text GLabel 9550 1050 0    50   Input ~ 0
B4_C1
$Comp
L Device:R_US R25
U 1 1 5E6517F5
P 9950 1750
F 0 "R25" V 9850 1750 50  0000 C CNN
F 1 "R_US" V 10050 1750 50  0001 C CNN
F 2 "" V 9990 1740 50  0001 C CNN
F 3 "~" H 9950 1750 50  0001 C CNN
F 4 "R" H 9950 1750 50  0001 C CNN "Spice_Primitive"
F 5 "560e3" V 10050 1750 50  0000 C CNN "Spice_Model"
F 6 "Y" H 9950 1750 50  0001 C CNN "Spice_Netlist_Enabled"
	1    9950 1750
	0    -1   1    0   
$EndComp
$Comp
L Device:R_US R24
U 1 1 5E6517FE
P 9950 1400
F 0 "R24" V 9850 1400 50  0000 C CNN
F 1 "R_US" V 10050 1400 50  0001 C CNN
F 2 "" V 9990 1390 50  0001 C CNN
F 3 "~" H 9950 1400 50  0001 C CNN
F 4 "R" H 9950 1400 50  0001 C CNN "Spice_Primitive"
F 5 "560e3" V 10050 1400 50  0000 C CNN "Spice_Model"
F 6 "Y" H 9950 1400 50  0001 C CNN "Spice_Netlist_Enabled"
	1    9950 1400
	0    -1   1    0   
$EndComp
$Comp
L Device:R_US R26
U 1 1 5E651807
P 10700 1050
F 0 "R26" V 10600 1050 50  0000 C CNN
F 1 "R_US" V 10800 1050 50  0001 C CNN
F 2 "" V 10740 1040 50  0001 C CNN
F 3 "~" H 10700 1050 50  0001 C CNN
F 4 "R" H 10700 1050 50  0001 C CNN "Spice_Primitive"
F 5 "56e3" V 10800 1050 50  0000 C CNN "Spice_Model"
F 6 "Y" H 10700 1050 50  0001 C CNN "Spice_Netlist_Enabled"
	1    10700 1050
	0    -1   1    0   
$EndComp
$Comp
L Device:R_US R27
U 1 1 5E651810
P 10700 1400
F 0 "R27" V 10600 1400 50  0000 C CNN
F 1 "R_US" V 10800 1400 50  0001 C CNN
F 2 "" V 10740 1390 50  0001 C CNN
F 3 "~" H 10700 1400 50  0001 C CNN
F 4 "R" H 10700 1400 50  0001 C CNN "Spice_Primitive"
F 5 "470e3" V 10800 1400 50  0000 C CNN "Spice_Model"
F 6 "Y" H 10700 1400 50  0001 C CNN "Spice_Netlist_Enabled"
	1    10700 1400
	0    -1   1    0   
$EndComp
$Comp
L Device:R_US R28
U 1 1 5E651819
P 10700 1750
F 0 "R28" V 10600 1750 50  0000 C CNN
F 1 "330k" V 10800 1750 50  0001 C CNN
F 2 "" V 10740 1740 50  0001 C CNN
F 3 "~" H 10700 1750 50  0001 C CNN
F 4 "R" H 10700 1750 50  0001 C CNN "Spice_Primitive"
F 5 "330e3" V 10800 1750 50  0000 C CNN "Spice_Model"
F 6 "Y" H 10700 1750 50  0001 C CNN "Spice_Netlist_Enabled"
	1    10700 1750
	0    -1   1    0   
$EndComp
Wire Wire Line
	9550 1400 9800 1400
Wire Wire Line
	9550 1750 9800 1750
Wire Wire Line
	10100 1400 10150 1400
Wire Wire Line
	10100 1750 10150 1750
Wire Wire Line
	9550 1050 10150 1050
Wire Wire Line
	10250 900  10150 900 
Wire Wire Line
	10150 900  10150 1050
Connection ~ 10150 1050
Wire Wire Line
	10150 1050 10550 1050
Wire Wire Line
	10250 1250 10150 1250
Wire Wire Line
	10150 1250 10150 1400
Wire Wire Line
	10250 1600 10150 1600
Connection ~ 10150 1400
Wire Wire Line
	10150 1400 10550 1400
Wire Wire Line
	10150 1600 10150 1750
Connection ~ 10150 1750
Wire Wire Line
	10150 1750 10550 1750
Wire Wire Line
	10950 1400 10950 1750
Connection ~ 10950 1400
Text GLabel 8250 5150 0    50   Input ~ 0
A11
Text GLabel 8250 5250 0    50   Input ~ 0
A12
Text GLabel 8250 5350 0    50   Input ~ 0
A13
Text GLabel 8250 5450 0    50   Input ~ 0
A14
Text GLabel 8250 5550 0    50   Input ~ 0
A15
Text GLabel 8250 4950 0    50   Input ~ 0
A09
$Comp
L Connector_Generic:Conn_01x07 J1
U 1 1 5E6CB73B
P 1800 4350
F 0 "J1" H 1800 3850 50  0000 C CNN
F 1 "JST_7PIN_FEMALE" H 1550 3950 50  0000 C CNN
F 2 "" H 1800 4350 50  0001 C CNN
F 3 "~" H 1800 4350 50  0001 C CNN
F 4 "J" H 1800 4350 50  0001 C CNN "Spice_Primitive"
F 5 "JST_7PIN_FEMALE" H 1800 4350 50  0001 C CNN "Spice_Model"
F 6 "N" H 1800 4350 50  0001 C CNN "Spice_Netlist_Enabled"
	1    1800 4350
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x05 J2
U 1 1 5E6CD89C
P 2800 4250
F 0 "J2" H 2800 3850 50  0000 C CNN
F 1 "JST_5PIN_FEMALE" H 2550 3950 50  0000 C CNN
F 2 "" H 2800 4250 50  0001 C CNN
F 3 "~" H 2800 4250 50  0001 C CNN
F 4 "J" H 2800 4250 50  0001 C CNN "Spice_Primitive"
F 5 "JST_5PIN_FEMALE" H 2800 4250 50  0001 C CNN "Spice_Model"
F 6 "N" H 2800 4250 50  0001 C CNN "Spice_Netlist_Enabled"
	1    2800 4250
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J3
U 1 1 5E6CE49D
P 3750 4250
F 0 "J3" H 3750 3850 50  0000 C CNN
F 1 "JST_4PIN_FEMALE" H 3500 3950 50  0000 C CNN
F 2 "" H 3750 4250 50  0001 C CNN
F 3 "~" H 3750 4250 50  0001 C CNN
F 4 "J" H 3750 4250 50  0001 C CNN "Spice_Primitive"
F 5 "JST_4PIN_FEMALE" H 3750 4250 50  0001 C CNN "Spice_Model"
F 6 "N" H 3750 4250 50  0001 C CNN "Spice_Netlist_Enabled"
	1    3750 4250
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J4
U 1 1 5E6E1880
P 4750 4250
F 0 "J4" H 4750 3850 50  0000 C CNN
F 1 "JST_4PIN_FEMALE" H 4500 3950 50  0000 C CNN
F 2 "" H 4750 4250 50  0001 C CNN
F 3 "~" H 4750 4250 50  0001 C CNN
F 4 "J" H 4750 4250 50  0001 C CNN "Spice_Primitive"
F 5 "JST_4PIN_FEMALE" H 4750 4250 50  0001 C CNN "Spice_Model"
F 6 "N" H 4750 4250 50  0001 C CNN "Spice_Netlist_Enabled"
	1    4750 4250
	-1   0    0    1   
$EndComp
Wire Notes Line
	5300 650  3450 650 
Wire Notes Line
	3450 650  3450 2450
Wire Notes Line
	3450 2450 5300 2450
Wire Notes Line
	5300 2450 5300 650 
Text GLabel 7400 1600 2    50   Input ~ 0
A12
Text GLabel 7400 1250 2    50   Input ~ 0
A11
Wire Wire Line
	8100 1400 8000 1400
Wire Wire Line
	8100 1750 8000 1750
Wire Wire Line
	8100 1400 8100 1750
Text GLabel 6700 1750 0    50   Input ~ 0
B3_C3
Text GLabel 6700 1400 0    50   Input ~ 0
B3_C2
$Comp
L Device:R_US R20
U 1 1 5E64BD86
P 7100 1750
F 0 "R20" V 7000 1750 50  0000 C CNN
F 1 "R_US" V 7200 1750 50  0001 C CNN
F 2 "" V 7140 1740 50  0001 C CNN
F 3 "~" H 7100 1750 50  0001 C CNN
F 4 "R" H 7100 1750 50  0001 C CNN "Spice_Primitive"
F 5 "560e3" V 7200 1750 50  0000 C CNN "Spice_Model"
F 6 "Y" H 7100 1750 50  0001 C CNN "Spice_Netlist_Enabled"
	1    7100 1750
	0    -1   1    0   
$EndComp
$Comp
L Device:R_US R19
U 1 1 5E64BD8F
P 7100 1400
F 0 "R19" V 7000 1400 50  0000 C CNN
F 1 "R_US" V 7200 1400 50  0001 C CNN
F 2 "" V 7140 1390 50  0001 C CNN
F 3 "~" H 7100 1400 50  0001 C CNN
F 4 "R" H 7100 1400 50  0001 C CNN "Spice_Primitive"
F 5 "560e3" V 7200 1400 50  0000 C CNN "Spice_Model"
F 6 "Y" H 7100 1400 50  0001 C CNN "Spice_Netlist_Enabled"
	1    7100 1400
	0    -1   1    0   
$EndComp
$Comp
L Device:R_US R22
U 1 1 5E64BDA1
P 7850 1400
F 0 "R22" V 7750 1400 50  0000 C CNN
F 1 "R_US" V 7950 1400 50  0001 C CNN
F 2 "" V 7890 1390 50  0001 C CNN
F 3 "~" H 7850 1400 50  0001 C CNN
F 4 "R" H 7850 1400 50  0001 C CNN "Spice_Primitive"
F 5 "470e3" V 7950 1400 50  0000 C CNN "Spice_Model"
F 6 "Y" H 7850 1400 50  0001 C CNN "Spice_Netlist_Enabled"
	1    7850 1400
	0    -1   1    0   
$EndComp
$Comp
L Device:R_US R23
U 1 1 5E64BDAA
P 7850 1750
F 0 "R23" V 7750 1750 50  0000 C CNN
F 1 "330k" V 7950 1750 50  0001 C CNN
F 2 "" V 7890 1740 50  0001 C CNN
F 3 "~" H 7850 1750 50  0001 C CNN
F 4 "R" H 7850 1750 50  0001 C CNN "Spice_Primitive"
F 5 "330e3" V 7950 1750 50  0000 C CNN "Spice_Model"
F 6 "Y" H 7850 1750 50  0001 C CNN "Spice_Netlist_Enabled"
	1    7850 1750
	0    -1   1    0   
$EndComp
Wire Wire Line
	6700 1400 6950 1400
Wire Wire Line
	6700 1750 6950 1750
Wire Wire Line
	7250 1400 7300 1400
Wire Wire Line
	7250 1750 7300 1750
Wire Wire Line
	7400 1250 7300 1250
Wire Wire Line
	7300 1250 7300 1400
Wire Wire Line
	7400 1600 7300 1600
Connection ~ 7300 1400
Wire Wire Line
	7300 1400 7700 1400
Wire Wire Line
	7300 1600 7300 1750
Connection ~ 7300 1750
Wire Wire Line
	7300 1750 7700 1750
Wire Wire Line
	8100 1750 8100 1900
Connection ~ 8100 1750
Wire Notes Line
	8200 650  6350 650 
Wire Notes Line
	6350 650  6350 2100
Wire Notes Line
	6350 2100 8200 2100
Wire Notes Line
	8200 650  8200 2100
Wire Notes Line
	11050 650  9200 650 
Wire Notes Line
	9200 650  9200 2100
Wire Notes Line
	11050 650  11050 2100
Wire Notes Line
	9200 2100 11050 2100
Text Notes 1050 750  0    50   ~ 10
6s Battery Voltage Divider
Text Notes 3850 750  0    50   ~ 10
4s Battery Voltage Divider
Text Notes 6650 750  0    50   ~ 10
3s Battery Voltage Divider (1/2)
Text Notes 9500 750  0    50   ~ 10
3s Battery Voltage Divider (2/2)
Wire Wire Line
	2350 6400 2350 6250
Wire Wire Line
	1900 6250 2350 6250
Wire Wire Line
	1450 7150 1450 7000
Wire Wire Line
	1450 7150 1900 7150
Wire Wire Line
	1900 6250 1900 7150
Wire Wire Line
	2350 7150 2800 7150
Wire Wire Line
	2800 6250 2800 7150
Wire Wire Line
	3250 6400 3250 6250
Wire Wire Line
	2800 6250 3250 6250
Wire Wire Line
	4150 6400 4150 6250
Wire Wire Line
	3700 6250 4150 6250
Wire Wire Line
	3250 7150 3250 7000
Wire Wire Line
	3700 6250 3700 7150
Wire Wire Line
	4150 7150 4150 7000
Wire Wire Line
	4600 6250 4600 7150
Wire Wire Line
	5050 6400 5050 6250
Wire Wire Line
	5950 6400 5950 6250
Wire Wire Line
	5500 6250 5950 6250
Wire Wire Line
	5050 7150 5050 7000
Wire Wire Line
	5500 6250 5500 7150
Text GLabel 5750 6100 0    50   Input ~ 0
B1_C1
Wire Wire Line
	5750 6100 5950 6100
Wire Wire Line
	5950 6100 5950 6250
Text GLabel 4850 6100 0    50   Input ~ 0
B1_C2
Wire Wire Line
	4850 6100 5050 6100
Wire Wire Line
	5050 6100 5050 6250
Text GLabel 3950 6100 0    50   Input ~ 0
B1_C3
Wire Wire Line
	3950 6100 4150 6100
Wire Wire Line
	4150 6100 4150 6250
Connection ~ 5050 6250
Wire Wire Line
	4600 6250 5050 6250
Connection ~ 4150 6250
Text GLabel 3050 6100 0    50   Input ~ 0
B1_C4
Wire Wire Line
	3050 6100 3250 6100
Wire Wire Line
	3250 6100 3250 6250
Text GLabel 2150 6100 0    50   Input ~ 0
B1_C5
Wire Wire Line
	2150 6100 2350 6100
Wire Wire Line
	2350 6100 2350 6250
Text GLabel 1250 6100 0    50   Input ~ 0
B1_C6
Wire Wire Line
	1450 6100 1450 6400
Connection ~ 2350 6250
Connection ~ 3250 6250
$Comp
L pspice:0 #GND07
U 1 1 5E7D6434
P 5950 7250
AR Path="/5E7D6434" Ref="#GND07"  Part="1" 
AR Path="/5E5E9ACC/5E7D6434" Ref="#GND?"  Part="1" 
F 0 "#GND07" H 5950 7150 50  0001 C CNN
F 1 "0" H 5950 7150 50  0000 C CNN
F 2 "" H 5950 7250 50  0001 C CNN
F 3 "~" H 5950 7250 50  0001 C CNN
	1    5950 7250
	1    0    0    -1  
$EndComp
$Comp
L pspice:VSOURCE V1
U 1 1 5E7D643A
P 1450 6700
AR Path="/5E7D643A" Ref="V1"  Part="1" 
AR Path="/5E5E9ACC/5E7D643A" Ref="V?"  Part="1" 
F 0 "V1" H 1678 6746 50  0000 L CNN
F 1 "3.7" H 1678 6655 50  0000 L CNN
F 2 "" H 1450 6700 50  0001 C CNN
F 3 "~" H 1450 6700 50  0001 C CNN
F 4 "V" H 1450 6700 50  0001 C CNN "Spice_Primitive"
F 5 "pulse(3.0 4.2 1 1 1 1 3)" H 1450 6700 50  0001 C CNN "Spice_Model"
F 6 "Y" H 1450 6700 50  0001 C CNN "Spice_Netlist_Enabled"
	1    1450 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 7000 2350 7150
Wire Wire Line
	5950 7000 5950 7250
Wire Wire Line
	3250 7150 3700 7150
Wire Wire Line
	4150 7150 4600 7150
Wire Wire Line
	5050 7150 5500 7150
Wire Wire Line
	1250 6100 1450 6100
Text GLabel 5750 5950 0    50   Input ~ 0
B2_C1
Wire Wire Line
	5750 5950 5950 5950
Wire Wire Line
	5950 5950 5950 6100
Text GLabel 4850 5950 0    50   Input ~ 0
B2_C2
Wire Wire Line
	4850 5950 5050 5950
Text GLabel 3950 5950 0    50   Input ~ 0
B2_C3
Wire Wire Line
	3950 5950 4150 5950
Text GLabel 3050 5950 0    50   Input ~ 0
B2_C4
Wire Wire Line
	3050 5950 3250 5950
Connection ~ 5950 6100
Connection ~ 5950 6250
Wire Wire Line
	3250 5950 3250 6100
Connection ~ 3250 6100
Wire Wire Line
	4150 5950 4150 6100
Connection ~ 4150 6100
Wire Wire Line
	5050 5950 5050 6100
Connection ~ 5050 6100
Text GLabel 5750 5800 0    50   Input ~ 0
B3_C1
Wire Wire Line
	5750 5800 5950 5800
Wire Wire Line
	5950 5800 5950 5950
Text GLabel 4850 5800 0    50   Input ~ 0
B3_C2
Wire Wire Line
	4850 5800 5050 5800
Text GLabel 3950 5800 0    50   Input ~ 0
B3_C3
Wire Wire Line
	3950 5800 4150 5800
Wire Wire Line
	4150 5800 4150 5950
Wire Wire Line
	5050 5800 5050 5950
Connection ~ 4150 5950
Connection ~ 5050 5950
Connection ~ 5950 5950
Text GLabel 5750 5650 0    50   Input ~ 0
B4_C1
Wire Wire Line
	5750 5650 5950 5650
Wire Wire Line
	5950 5650 5950 5800
Text GLabel 4850 5650 0    50   Input ~ 0
B4_C2
Wire Wire Line
	4850 5650 5050 5650
Text GLabel 3950 5650 0    50   Input ~ 0
B4_C3
Wire Wire Line
	3950 5650 4150 5650
Wire Wire Line
	4150 5650 4150 5800
Wire Wire Line
	5050 5650 5050 5800
Connection ~ 4150 5800
Connection ~ 5050 5800
Connection ~ 5950 5800
Text GLabel 2150 4550 2    50   Input ~ 0
B1_C6
Text GLabel 2150 4450 2    50   Input ~ 0
B1_C5
Text GLabel 2150 4350 2    50   Input ~ 0
B1_C4
Text GLabel 2150 4250 2    50   Input ~ 0
B1_C3
Text GLabel 2150 4150 2    50   Input ~ 0
B1_C2
Text GLabel 2150 4050 2    50   Input ~ 0
B1_C1
Wire Wire Line
	2150 4050 2000 4050
Wire Wire Line
	2000 4150 2150 4150
Wire Wire Line
	2150 4250 2000 4250
Wire Wire Line
	2000 4350 2150 4350
Wire Wire Line
	2150 4450 2000 4450
Wire Wire Line
	2000 4550 2150 4550
Wire Wire Line
	2000 4650 2150 4650
Wire Wire Line
	2150 4650 2150 4800
Text GLabel 3150 4350 2    50   Input ~ 0
B2_C4
Text GLabel 3150 4250 2    50   Input ~ 0
B2_C3
Text GLabel 3150 4150 2    50   Input ~ 0
B2_C2
Text GLabel 3150 4050 2    50   Input ~ 0
B2_C1
Wire Wire Line
	3150 4050 3000 4050
Wire Wire Line
	3000 4150 3150 4150
Wire Wire Line
	3150 4250 3000 4250
Wire Wire Line
	3000 4350 3150 4350
Wire Wire Line
	3150 4450 3000 4450
Wire Wire Line
	4100 4050 3950 4050
Wire Wire Line
	3950 4150 4100 4150
Wire Wire Line
	4100 4250 3950 4250
Wire Wire Line
	3950 4350 4100 4350
Wire Wire Line
	4100 4350 4100 4500
Text GLabel 4100 4250 2    50   Input ~ 0
B3_C3
Text GLabel 4100 4150 2    50   Input ~ 0
B3_C2
Text GLabel 4100 4050 2    50   Input ~ 0
B3_C1
Wire Wire Line
	4950 4350 5100 4350
Wire Wire Line
	5100 4350 5100 4500
Wire Wire Line
	5100 4050 4950 4050
Wire Wire Line
	4950 4150 5100 4150
Wire Wire Line
	5100 4250 4950 4250
Text GLabel 5100 4250 2    50   Input ~ 0
B4_C3
Text GLabel 5100 4150 2    50   Input ~ 0
B4_C2
Text GLabel 5100 4050 2    50   Input ~ 0
B4_C1
$Comp
L pspice:0 #GND06
U 1 1 5E9918BE
P 5200 2250
F 0 "#GND06" H 5200 2150 50  0001 C CNN
F 1 "0" H 5200 2150 50  0001 C CNN
F 2 "" H 5200 2250 50  0001 C CNN
F 3 "~" H 5200 2250 50  0001 C CNN
F 4 "B2_GND" H 5250 2150 50  0000 C CNN "Name"
	1    5200 2250
	-1   0    0    -1  
$EndComp
$Comp
L pspice:0 #GND08
U 1 1 5E991FA1
P 8100 1900
F 0 "#GND08" H 8100 1800 50  0001 C CNN
F 1 "0" H 8100 1800 50  0001 C CNN
F 2 "" H 8100 1900 50  0001 C CNN
F 3 "~" H 8100 1900 50  0001 C CNN
F 4 "B3_GND" H 8150 1800 50  0000 C CNN "Name"
	1    8100 1900
	-1   0    0    -1  
$EndComp
$Comp
L pspice:0 #GND01
U 1 1 5E9929DD
P 2150 4800
F 0 "#GND01" H 2150 4700 50  0001 C CNN
F 1 "0" H 2150 4700 50  0001 C CNN
F 2 "" H 2150 4800 50  0001 C CNN
F 3 "~" H 2150 4800 50  0001 C CNN
F 4 "B1_GND" H 2150 4700 50  0000 C CNN "Name"
	1    2150 4800
	-1   0    0    -1  
$EndComp
$Comp
L pspice:0 #GND03
U 1 1 5E993603
P 3150 4600
F 0 "#GND03" H 3150 4500 50  0001 C CNN
F 1 "0" H 3150 4500 50  0001 C CNN
F 2 "" H 3150 4600 50  0001 C CNN
F 3 "~" H 3150 4600 50  0001 C CNN
F 4 "B2_GND" H 3150 4500 50  0000 C CNN "Name"
	1    3150 4600
	-1   0    0    -1  
$EndComp
$Comp
L pspice:0 #GND04
U 1 1 5E9A0DBB
P 4100 4500
F 0 "#GND04" H 4100 4400 50  0001 C CNN
F 1 "0" H 4100 4400 50  0001 C CNN
F 2 "" H 4100 4500 50  0001 C CNN
F 3 "~" H 4100 4500 50  0001 C CNN
F 4 "B3_GND" H 4100 4400 50  0000 C CNN "Name"
	1    4100 4500
	-1   0    0    -1  
$EndComp
$Comp
L pspice:0 #GND05
U 1 1 5E9A1398
P 5100 4500
F 0 "#GND05" H 5100 4400 50  0001 C CNN
F 1 "0" H 5100 4400 50  0001 C CNN
F 2 "" H 5100 4500 50  0001 C CNN
F 3 "~" H 5100 4500 50  0001 C CNN
F 4 "B4_GND" H 5100 4400 50  0000 C CNN "Name"
	1    5100 4500
	-1   0    0    -1  
$EndComp
$Comp
L pspice:VSOURCE V2
U 1 1 5E9BD74F
P 2350 6700
AR Path="/5E9BD74F" Ref="V2"  Part="1" 
AR Path="/5E5E9ACC/5E9BD74F" Ref="V?"  Part="1" 
F 0 "V2" H 2578 6746 50  0000 L CNN
F 1 "3.7" H 2578 6655 50  0000 L CNN
F 2 "" H 2350 6700 50  0001 C CNN
F 3 "~" H 2350 6700 50  0001 C CNN
F 4 "V" H 2350 6700 50  0001 C CNN "Spice_Primitive"
F 5 "pulse(3.0 4.2 1 1 1 1 3)" H 2350 6700 50  0001 C CNN "Spice_Model"
F 6 "Y" H 2350 6700 50  0001 C CNN "Spice_Netlist_Enabled"
	1    2350 6700
	1    0    0    -1  
$EndComp
$Comp
L pspice:VSOURCE V3
U 1 1 5E9BEA5F
P 3250 6700
AR Path="/5E9BEA5F" Ref="V3"  Part="1" 
AR Path="/5E5E9ACC/5E9BEA5F" Ref="V?"  Part="1" 
F 0 "V3" H 3478 6746 50  0000 L CNN
F 1 "3.7" H 3478 6655 50  0000 L CNN
F 2 "" H 3250 6700 50  0001 C CNN
F 3 "~" H 3250 6700 50  0001 C CNN
F 4 "V" H 3250 6700 50  0001 C CNN "Spice_Primitive"
F 5 "pulse(3.0 4.2 1 1 1 1 3)" H 3250 6700 50  0001 C CNN "Spice_Model"
F 6 "Y" H 3250 6700 50  0001 C CNN "Spice_Netlist_Enabled"
	1    3250 6700
	1    0    0    -1  
$EndComp
$Comp
L pspice:VSOURCE V4
U 1 1 5E9BF210
P 4150 6700
AR Path="/5E9BF210" Ref="V4"  Part="1" 
AR Path="/5E5E9ACC/5E9BF210" Ref="V?"  Part="1" 
F 0 "V4" H 4378 6746 50  0000 L CNN
F 1 "3.7" H 4378 6655 50  0000 L CNN
F 2 "" H 4150 6700 50  0001 C CNN
F 3 "~" H 4150 6700 50  0001 C CNN
F 4 "V" H 4150 6700 50  0001 C CNN "Spice_Primitive"
F 5 "pulse(3.0 4.2 1 1 1 1 3)" H 4150 6700 50  0001 C CNN "Spice_Model"
F 6 "Y" H 4150 6700 50  0001 C CNN "Spice_Netlist_Enabled"
	1    4150 6700
	1    0    0    -1  
$EndComp
$Comp
L pspice:VSOURCE V5
U 1 1 5E9BF775
P 5050 6700
AR Path="/5E9BF775" Ref="V5"  Part="1" 
AR Path="/5E5E9ACC/5E9BF775" Ref="V?"  Part="1" 
F 0 "V5" H 5278 6746 50  0000 L CNN
F 1 "3.7" H 5278 6655 50  0000 L CNN
F 2 "" H 5050 6700 50  0001 C CNN
F 3 "~" H 5050 6700 50  0001 C CNN
F 4 "V" H 5050 6700 50  0001 C CNN "Spice_Primitive"
F 5 "pulse(3.0 4.2 1 1 1 1 3)" H 5050 6700 50  0001 C CNN "Spice_Model"
F 6 "Y" H 5050 6700 50  0001 C CNN "Spice_Netlist_Enabled"
	1    5050 6700
	1    0    0    -1  
$EndComp
$Comp
L pspice:VSOURCE V6
U 1 1 5E9BFBC2
P 5950 6700
AR Path="/5E9BFBC2" Ref="V6"  Part="1" 
AR Path="/5E5E9ACC/5E9BFBC2" Ref="V?"  Part="1" 
F 0 "V6" H 6178 6746 50  0000 L CNN
F 1 "3.7" H 6178 6655 50  0000 L CNN
F 2 "" H 5950 6700 50  0001 C CNN
F 3 "~" H 5950 6700 50  0001 C CNN
F 4 "V" H 5950 6700 50  0001 C CNN "Spice_Primitive"
F 5 "pulse(3.0 4.2 1 1 1 1 3)" H 5950 6700 50  0001 C CNN "Spice_Model"
F 6 "Y" H 5950 6700 50  0001 C CNN "Spice_Netlist_Enabled"
	1    5950 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 5050 8550 5050
Wire Wire Line
	3150 4450 3150 4600
NoConn ~ 8550 3250
NoConn ~ 8550 3350
NoConn ~ 8550 3450
NoConn ~ 8550 3550
NoConn ~ 8550 3650
NoConn ~ 9650 3050
NoConn ~ 9650 3150
NoConn ~ 9650 3250
NoConn ~ 9650 3350
NoConn ~ 8550 3750
Wire Wire Line
	2400 2800 2300 2800
Wire Wire Line
	2400 2800 2400 2950
Connection ~ 2400 2800
$Comp
L pspice:0 #GND02
U 1 1 5EF02F21
P 2400 2950
F 0 "#GND02" H 2400 2850 50  0001 C CNN
F 1 "0" H 2400 2850 50  0001 C CNN
F 2 "" H 2400 2950 50  0001 C CNN
F 3 "~" H 2400 2950 50  0001 C CNN
F 4 "B2_GND" H 2450 2850 50  0000 C CNN "Name"
	1    2400 2950
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2300 1400 2400 1400
Wire Wire Line
	2400 1400 2400 1750
Wire Wire Line
	2300 1750 2400 1750
Connection ~ 2400 1750
Wire Wire Line
	2400 1750 2400 2100
Wire Wire Line
	2300 2100 2400 2100
Connection ~ 2400 2100
Wire Wire Line
	2400 2100 2400 2450
Wire Wire Line
	2300 2450 2400 2450
Connection ~ 2400 2450
Wire Wire Line
	2400 2450 2400 2800
Wire Wire Line
	8550 3950 8250 3950
Wire Wire Line
	8550 4050 8250 4050
Wire Wire Line
	8550 4250 8250 4250
Text GLabel 8250 4250 0    50   Input ~ 0
A03
Text GLabel 8250 4050 0    50   Input ~ 0
A01
Text GLabel 8250 4150 0    50   Input ~ 0
A02
Wire Wire Line
	8250 4150 8550 4150
Wire Wire Line
	8550 4350 8250 4350
Wire Wire Line
	8550 4450 8250 4450
Text GLabel 8250 4350 0    50   Input ~ 0
A04
Text GLabel 8250 4450 0    50   Input ~ 0
A05
Text GLabel 1700 1950 2    50   Input ~ 0
A03
Text GLabel 1700 1250 2    50   Input ~ 0
A01
Text GLabel 1700 1600 2    50   Input ~ 0
A02
Text GLabel 1700 2300 2    50   Input ~ 0
A04
Text GLabel 1700 2650 2    50   Input ~ 0
A05
Wire Wire Line
	1700 1250 1600 1250
Wire Wire Line
	1700 1600 1600 1600
Wire Wire Line
	1700 1950 1600 1950
Wire Wire Line
	1700 2300 1600 2300
Wire Wire Line
	1700 2650 1600 2650
Wire Notes Line
	2500 650  650  650 
Wire Notes Line
	650  3150 2500 3150
Wire Notes Line
	650  650  650  3150
Wire Notes Line
	2500 650  2500 3150
NoConn ~ 9650 3450
NoConn ~ 9650 3550
NoConn ~ 9650 3650
NoConn ~ 9650 3750
NoConn ~ 9650 3850
NoConn ~ 9650 4050
NoConn ~ 9650 4150
NoConn ~ 9650 4250
NoConn ~ 9650 4350
NoConn ~ 9650 4450
NoConn ~ 9650 4550
NoConn ~ 9650 4650
NoConn ~ 9650 4750
NoConn ~ 9650 4950
NoConn ~ 9650 5050
NoConn ~ 9650 5150
NoConn ~ 9650 5250
NoConn ~ 9650 5350
NoConn ~ 9650 5450
NoConn ~ 9650 5550
NoConn ~ 9650 5650
Wire Wire Line
	10950 1750 10950 1900
Connection ~ 10950 1750
$Comp
L pspice:0 #GND09
U 1 1 5F1BE80E
P 10950 1900
F 0 "#GND09" H 10950 1800 50  0001 C CNN
F 1 "0" H 10950 1800 50  0001 C CNN
F 2 "" H 10950 1900 50  0001 C CNN
F 3 "~" H 10950 1900 50  0001 C CNN
F 4 "B4_GND" H 11000 1800 50  0000 C CNN "Name"
	1    10950 1900
	-1   0    0    -1  
$EndComp
Wire Notes Line
	1600 3600 5500 3600
Wire Notes Line
	1600 5000 5500 5000
Wire Notes Line
	1600 3600 1600 5000
Wire Notes Line
	5500 3600 5500 5000
Text Notes 3050 3700 0    50   ~ 10
Battery Connection Ports (JST)
Wire Notes Line
	6350 5350 6350 7450
Wire Notes Line
	6350 7450 900  7450
Wire Notes Line
	900  7450 900  5350
Wire Notes Line
	900  5350 6350 5350
Text Notes 3250 5450 0    50   ~ 10
Simulated Battery
Wire Notes Line
	7950 5850 9800 5850
Wire Notes Line
	9800 5850 9800 2600
Wire Notes Line
	9800 2600 7950 2600
Wire Notes Line
	7950 2600 7950 5850
Text Notes 8450 2700 0    50   ~ 10
Arduino MEGA2560v3
Text GLabel 8250 5050 0    50   Input ~ 0
A10
Text GLabel 8250 3950 0    50   Input ~ 0
A00
Text GLabel 7400 900  2    50   Input ~ 0
A10
Wire Wire Line
	8100 1050 8000 1050
Wire Wire Line
	8100 1050 8100 1400
Text GLabel 6700 1050 0    50   Input ~ 0
B3_C1
$Comp
L Device:R_US R21
U 1 1 5F4A604D
P 7850 1050
F 0 "R21" V 7750 1050 50  0000 C CNN
F 1 "R_US" V 7950 1050 50  0001 C CNN
F 2 "" V 7890 1040 50  0001 C CNN
F 3 "~" H 7850 1050 50  0001 C CNN
F 4 "R" H 7850 1050 50  0001 C CNN "Spice_Primitive"
F 5 "56e3" V 7950 1050 50  0000 C CNN "Spice_Model"
F 6 "Y" H 7850 1050 50  0001 C CNN "Spice_Netlist_Enabled"
	1    7850 1050
	0    -1   1    0   
$EndComp
Wire Wire Line
	6700 1050 7300 1050
Wire Wire Line
	7400 900  7300 900 
Wire Wire Line
	7300 900  7300 1050
Connection ~ 7300 1050
Wire Wire Line
	7300 1050 7700 1050
Text GLabel 1700 900  2    50   Input ~ 0
A00
Wire Wire Line
	2400 1050 2300 1050
Wire Wire Line
	2400 1050 2400 1400
Text GLabel 1000 1050 0    50   Input ~ 0
B2_C1
$Comp
L Device:R_US R6
U 1 1 5F4C11C7
P 2150 1050
F 0 "R6" V 2050 1050 50  0000 C CNN
F 1 "R_US" V 2250 1050 50  0001 C CNN
F 2 "" V 2190 1040 50  0001 C CNN
F 3 "~" H 2150 1050 50  0001 C CNN
F 4 "R" H 2150 1050 50  0001 C CNN "Spice_Primitive"
F 5 "56e3" V 2250 1050 50  0000 C CNN "Spice_Model"
F 6 "Y" H 2150 1050 50  0001 C CNN "Spice_Netlist_Enabled"
	1    2150 1050
	0    -1   1    0   
$EndComp
Wire Wire Line
	1000 1050 1600 1050
Wire Wire Line
	1700 900  1600 900 
Wire Wire Line
	1600 900  1600 1050
Connection ~ 1600 1050
Wire Wire Line
	1600 1050 2000 1050
$EndSCHEMATC
