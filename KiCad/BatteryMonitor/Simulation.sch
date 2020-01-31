EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	4350 4650 4350 4500
Wire Wire Line
	3900 4500 4350 4500
Wire Wire Line
	3450 5400 3450 5250
Wire Wire Line
	3450 5400 3900 5400
Wire Wire Line
	3900 4500 3900 5400
Wire Wire Line
	4350 5400 4800 5400
Wire Wire Line
	4800 4500 4800 5400
Wire Wire Line
	5250 4650 5250 4500
Wire Wire Line
	4800 4500 5250 4500
Wire Wire Line
	6150 4650 6150 4500
Wire Wire Line
	5700 4500 6150 4500
Wire Wire Line
	5250 5400 5250 5250
Wire Wire Line
	5700 4500 5700 5400
Wire Wire Line
	6150 5400 6150 5250
Wire Wire Line
	6600 4500 6600 5400
Wire Wire Line
	7050 4650 7050 4500
Wire Wire Line
	7950 4650 7950 4500
Wire Wire Line
	7500 4500 7950 4500
Wire Wire Line
	7050 5400 7050 5250
Wire Wire Line
	7500 4500 7500 5400
Text GLabel 7750 4350 0    50   Input ~ 0
B1_C1
Wire Wire Line
	7750 4350 7950 4350
Wire Wire Line
	7950 4350 7950 4500
Text GLabel 6850 4350 0    50   Input ~ 0
B1_C2
Wire Wire Line
	6850 4350 7050 4350
Wire Wire Line
	7050 4350 7050 4500
Text GLabel 5950 4350 0    50   Input ~ 0
B1_C3
Wire Wire Line
	5950 4350 6150 4350
Wire Wire Line
	6150 4350 6150 4500
Connection ~ 7050 4500
Wire Wire Line
	6600 4500 7050 4500
Connection ~ 6150 4500
Text GLabel 5050 4350 0    50   Input ~ 0
B1_C4
Wire Wire Line
	5050 4350 5250 4350
Wire Wire Line
	5250 4350 5250 4500
Text GLabel 4150 4350 0    50   Input ~ 0
B1_C5
Wire Wire Line
	4150 4350 4350 4350
Wire Wire Line
	4350 4350 4350 4500
Text GLabel 3250 4350 0    50   Input ~ 0
B1_C6
Wire Wire Line
	3450 4350 3450 4650
Connection ~ 4350 4500
Connection ~ 5250 4500
$Comp
L pspice:0 #GND?
U 1 1 5E5EF726
P 7950 5500
AR Path="/5E5EF726" Ref="#GND?"  Part="1" 
AR Path="/5E5E9ACC/5E5EF726" Ref="#GND04"  Part="1" 
F 0 "#GND04" H 7950 5400 50  0001 C CNN
F 1 "0" H 7950 5400 50  0000 C CNN
F 2 "" H 7950 5500 50  0001 C CNN
F 3 "~" H 7950 5500 50  0001 C CNN
	1    7950 5500
	1    0    0    -1  
$EndComp
$Comp
L pspice:VSOURCE V?
U 1 1 5E5EF72C
P 3450 4950
AR Path="/5E5EF72C" Ref="V?"  Part="1" 
AR Path="/5E5E9ACC/5E5EF72C" Ref="V1"  Part="1" 
F 0 "V1" H 3678 4996 50  0000 L CNN
F 1 "3.7" H 3678 4905 50  0000 L CNN
F 2 "" H 3450 4950 50  0001 C CNN
F 3 "~" H 3450 4950 50  0001 C CNN
	1    3450 4950
	1    0    0    -1  
$EndComp
$Comp
L pspice:VSOURCE V?
U 1 1 5E5EF732
P 4350 4950
AR Path="/5E5EF732" Ref="V?"  Part="1" 
AR Path="/5E5E9ACC/5E5EF732" Ref="V2"  Part="1" 
F 0 "V2" H 4578 4996 50  0000 L CNN
F 1 "3.7" H 4578 4905 50  0000 L CNN
F 2 "" H 4350 4950 50  0001 C CNN
F 3 "~" H 4350 4950 50  0001 C CNN
	1    4350 4950
	1    0    0    -1  
$EndComp
$Comp
L pspice:VSOURCE V?
U 1 1 5E5EF738
P 5250 4950
AR Path="/5E5EF738" Ref="V?"  Part="1" 
AR Path="/5E5E9ACC/5E5EF738" Ref="V3"  Part="1" 
F 0 "V3" H 5478 4996 50  0000 L CNN
F 1 "3.7" H 5478 4905 50  0000 L CNN
F 2 "" H 5250 4950 50  0001 C CNN
F 3 "~" H 5250 4950 50  0001 C CNN
	1    5250 4950
	1    0    0    -1  
$EndComp
$Comp
L pspice:VSOURCE V?
U 1 1 5E5EF73E
P 6150 4950
AR Path="/5E5EF73E" Ref="V?"  Part="1" 
AR Path="/5E5E9ACC/5E5EF73E" Ref="V4"  Part="1" 
F 0 "V4" H 6378 4996 50  0000 L CNN
F 1 "3.7" H 6378 4905 50  0000 L CNN
F 2 "" H 6150 4950 50  0001 C CNN
F 3 "~" H 6150 4950 50  0001 C CNN
	1    6150 4950
	1    0    0    -1  
$EndComp
$Comp
L pspice:VSOURCE V?
U 1 1 5E5EF744
P 7050 4950
AR Path="/5E5EF744" Ref="V?"  Part="1" 
AR Path="/5E5E9ACC/5E5EF744" Ref="V5"  Part="1" 
F 0 "V5" H 7278 4996 50  0000 L CNN
F 1 "3.7" H 7278 4905 50  0000 L CNN
F 2 "" H 7050 4950 50  0001 C CNN
F 3 "~" H 7050 4950 50  0001 C CNN
	1    7050 4950
	1    0    0    -1  
$EndComp
$Comp
L pspice:VSOURCE V?
U 1 1 5E5EF74A
P 7950 4950
AR Path="/5E5EF74A" Ref="V?"  Part="1" 
AR Path="/5E5E9ACC/5E5EF74A" Ref="V6"  Part="1" 
F 0 "V6" H 8178 4996 50  0000 L CNN
F 1 "3.7" H 8178 4905 50  0000 L CNN
F 2 "" H 7950 4950 50  0001 C CNN
F 3 "~" H 7950 4950 50  0001 C CNN
	1    7950 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 5250 4350 5400
Text Notes 650  800  0    50   ~ 0
.tran 1u 1m\n
Wire Wire Line
	7950 5250 7950 5500
Wire Wire Line
	5250 5400 5700 5400
Wire Wire Line
	6150 5400 6600 5400
Wire Wire Line
	7050 5400 7500 5400
Wire Wire Line
	3250 4350 3450 4350
Text GLabel 7750 4200 0    50   Input ~ 0
B2_C1
Wire Wire Line
	7750 4200 7950 4200
Wire Wire Line
	7950 4200 7950 4350
Text GLabel 6850 4200 0    50   Input ~ 0
B2_C2
Wire Wire Line
	6850 4200 7050 4200
Text GLabel 5950 4200 0    50   Input ~ 0
B2_C3
Wire Wire Line
	5950 4200 6150 4200
Text GLabel 5050 4200 0    50   Input ~ 0
B2_C4
Wire Wire Line
	5050 4200 5250 4200
Connection ~ 7950 4350
Connection ~ 7950 4500
Wire Wire Line
	5250 4200 5250 4350
Connection ~ 5250 4350
Wire Wire Line
	6150 4200 6150 4350
Connection ~ 6150 4350
Wire Wire Line
	7050 4200 7050 4350
Connection ~ 7050 4350
Text GLabel 7750 4050 0    50   Input ~ 0
B3_C1
Wire Wire Line
	7750 4050 7950 4050
Wire Wire Line
	7950 4050 7950 4200
Text GLabel 6850 4050 0    50   Input ~ 0
B3_C2
Wire Wire Line
	6850 4050 7050 4050
Text GLabel 5950 4050 0    50   Input ~ 0
B3_C3
Wire Wire Line
	5950 4050 6150 4050
Wire Wire Line
	6150 4050 6150 4200
Wire Wire Line
	7050 4050 7050 4200
Connection ~ 6150 4200
Connection ~ 7050 4200
Connection ~ 7950 4200
Text GLabel 7750 3900 0    50   Input ~ 0
B4_C1
Wire Wire Line
	7750 3900 7950 3900
Wire Wire Line
	7950 3900 7950 4050
Text GLabel 6850 3900 0    50   Input ~ 0
B4_C2
Wire Wire Line
	6850 3900 7050 3900
Text GLabel 5950 3900 0    50   Input ~ 0
B4_C3
Wire Wire Line
	5950 3900 6150 3900
Wire Wire Line
	6150 3900 6150 4050
Wire Wire Line
	7050 3900 7050 4050
Connection ~ 6150 4050
Connection ~ 7050 4050
Connection ~ 7950 4050
$EndSCHEMATC
