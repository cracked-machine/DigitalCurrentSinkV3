EESchema Schematic File Version 4
LIBS:ExternRegulatedConverter-cache
EELAYER 29 0
EELAYER END
$Descr A3 11693 16535 portrait
encoding utf-8
Sheet 1 2
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
L Device:CP C7
U 1 1 5CFB7E2E
P 6525 5425
F 0 "C7" H 6643 5471 50  0000 L CNN
F 1 "330nF" H 6643 5380 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6563 5275 50  0001 C CNN
F 3 "~" H 6525 5425 50  0001 C CNN
	1    6525 5425
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C11
U 1 1 5CFB7E87
P 7775 5425
F 0 "C11" H 7893 5471 50  0000 L CNN
F 1 "100nF" H 7893 5380 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7813 5275 50  0001 C CNN
F 3 "~" H 7775 5425 50  0001 C CNN
	1    7775 5425
	1    0    0    -1  
$EndComp
Wire Wire Line
	6525 5275 6525 5175
Wire Wire Line
	6525 5175 6850 5175
Wire Wire Line
	7450 5175 7775 5175
Wire Wire Line
	7775 5175 7775 5275
Wire Wire Line
	7775 5575 7775 5675
Wire Wire Line
	7150 5475 7150 5675
Connection ~ 7150 5675
Wire Wire Line
	7150 5675 7775 5675
Wire Wire Line
	6525 5575 6525 5675
Connection ~ 6525 5675
Wire Wire Line
	6525 5675 7150 5675
Wire Wire Line
	7150 5875 7150 5675
$Comp
L Device:CP C8
U 1 1 5CFB7FF7
P 6525 5925
F 0 "C8" H 6643 5971 50  0000 L CNN
F 1 "2.2uF" H 6643 5880 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_4x5.7" H 6563 5775 50  0001 C CNN
F 3 "~" H 6525 5925 50  0001 C CNN
	1    6525 5925
	1    0    0    -1  
$EndComp
Wire Wire Line
	6525 5675 6525 5775
Wire Wire Line
	6525 6075 6525 6175
Wire Wire Line
	6525 6175 6850 6175
$Comp
L Device:CP C12
U 1 1 5CFB8234
P 7775 5925
F 0 "C12" H 7893 5971 50  0000 L CNN
F 1 "1uF" H 7893 5880 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_4x5.7" H 7813 5775 50  0001 C CNN
F 3 "~" H 7775 5925 50  0001 C CNN
	1    7775 5925
	1    0    0    -1  
$EndComp
Wire Wire Line
	7775 5675 7775 5775
Connection ~ 7775 5675
Wire Wire Line
	7775 6075 7775 6175
Wire Wire Line
	7775 6175 7450 6175
Wire Wire Line
	6150 5475 6150 5175
Wire Wire Line
	6150 5175 6525 5175
Connection ~ 6525 5175
Wire Wire Line
	6150 5875 6150 6175
Wire Wire Line
	6150 6175 6525 6175
Connection ~ 6525 6175
$Comp
L Device:C C3
U 1 1 5CFB93CF
P 5025 4725
F 0 "C3" V 4875 4725 50  0000 C CNN
F 1 "33p" V 5175 4725 50  0000 C CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 5063 4575 50  0001 C CNN
F 3 "~" H 5025 4725 50  0001 C CNN
	1    5025 4725
	0    1    1    0   
$EndComp
Wire Wire Line
	4875 4725 4250 4725
Wire Wire Line
	4250 4725 4250 5375
Wire Wire Line
	4250 5475 4525 5475
Wire Wire Line
	5175 4725 5800 4725
Wire Wire Line
	5800 4725 5800 5475
Wire Wire Line
	5800 5475 6150 5475
$Comp
L Device:C C4
U 1 1 5CFBA757
P 5025 6475
F 0 "C4" V 4875 6475 50  0000 C CNN
F 1 "220p" V 5175 6475 50  0000 C CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 5063 6325 50  0001 C CNN
F 3 "~" H 5025 6475 50  0001 C CNN
	1    5025 6475
	0    1    1    0   
$EndComp
Wire Wire Line
	4875 6475 4250 6475
Wire Wire Line
	4250 6475 4250 5875
Wire Wire Line
	4250 5675 4525 5675
Wire Wire Line
	5175 6475 5800 6475
Wire Wire Line
	5800 5875 6150 5875
Wire Wire Line
	2750 5475 2750 5375
Wire Wire Line
	2750 5875 2750 5775
NoConn ~ 4525 5875
$Comp
L power:VCOM #PWR019
U 1 1 5D031D5D
P 8275 5675
F 0 "#PWR019" H 8275 5525 50  0001 C CNN
F 1 "VCOM" V 8175 5675 50  0000 C CNN
F 2 "" H 8275 5675 50  0001 C CNN
F 3 "" H 8275 5675 50  0001 C CNN
	1    8275 5675
	0    1    1    0   
$EndComp
Wire Wire Line
	8275 5675 7775 5675
$Comp
L power:-12V #PWR020
U 1 1 5D03E54A
P 8275 6325
F 0 "#PWR020" H 8275 6425 50  0001 C CNN
F 1 "-12V" H 8290 6498 50  0000 C CNN
F 2 "" H 8275 6325 50  0001 C CNN
F 3 "" H 8275 6325 50  0001 C CNN
	1    8275 6325
	-1   0    0    1   
$EndComp
Wire Wire Line
	8275 6325 8275 6175
Wire Wire Line
	8275 6175 7775 6175
Connection ~ 7775 6175
$Comp
L power:+12V #PWR018
U 1 1 5D040FC9
P 8275 5050
F 0 "#PWR018" H 8275 4900 50  0001 C CNN
F 1 "+12V" H 8290 5223 50  0000 C CNN
F 2 "" H 8275 5050 50  0001 C CNN
F 3 "" H 8275 5050 50  0001 C CNN
	1    8275 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8275 5050 8275 5175
Wire Wire Line
	8275 5175 7775 5175
Connection ~ 7775 5175
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 5D04F0FF
P 2575 2125
F 0 "J1" H 2495 1800 50  0000 C CNN
F 1 "15VDC" H 2495 1891 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Horizontal" H 2575 2125 50  0001 C CNN
F 3 "~" H 2575 2125 50  0001 C CNN
	1    2575 2125
	-1   0    0    1   
$EndComp
Wire Wire Line
	3725 2125 3725 2425
$Comp
L power:GNDS #PWR06
U 1 1 5D051DA0
P 3725 2425
F 0 "#PWR06" H 3725 2175 50  0001 C CNN
F 1 "GNDS" H 3730 2252 50  0000 C CNN
F 2 "" H 3725 2425 50  0001 C CNN
F 3 "" H 3725 2425 50  0001 C CNN
	1    3725 2425
	1    0    0    -1  
$EndComp
Wire Wire Line
	3725 2125 2775 2125
$Comp
L power:+12V #PWR09
U 1 1 5D05AB98
P 5000 1525
F 0 "#PWR09" H 5000 1375 50  0001 C CNN
F 1 "+12V" H 5015 1698 50  0000 C CNN
F 2 "" H 5000 1525 50  0001 C CNN
F 3 "" H 5000 1525 50  0001 C CNN
	1    5000 1525
	1    0    0    -1  
$EndComp
$Comp
L power:VCOM #PWR08
U 1 1 5D05AD07
P 4900 1825
F 0 "#PWR08" H 4900 1675 50  0001 C CNN
F 1 "VCOM" V 4900 2025 50  0000 L CNN
F 2 "" H 4900 1825 50  0001 C CNN
F 3 "" H 4900 1825 50  0001 C CNN
	1    4900 1825
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5000 1525 5000 1725
Wire Wire Line
	5000 1725 5800 1725
Wire Wire Line
	5800 1825 4900 1825
$Comp
L power:-12V #PWR010
U 1 1 5D067A7E
P 5000 2525
F 0 "#PWR010" H 5000 2625 50  0001 C CNN
F 1 "-12V" H 5015 2698 50  0000 C CNN
F 2 "" H 5000 2525 50  0001 C CNN
F 3 "" H 5000 2525 50  0001 C CNN
	1    5000 2525
	-1   0    0    1   
$EndComp
Wire Wire Line
	5000 2525 5000 1925
Wire Wire Line
	5000 1925 5800 1925
$Comp
L power:+5V #PWR011
U 1 1 5D074863
P 5600 1475
F 0 "#PWR011" H 5600 1325 50  0001 C CNN
F 1 "+5V" H 5615 1648 50  0000 C CNN
F 2 "" H 5600 1475 50  0001 C CNN
F 3 "" H 5600 1475 50  0001 C CNN
	1    5600 1475
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 1525 5300 2025
Wire Wire Line
	5300 2025 5800 2025
Wire Wire Line
	5300 2525 5300 2125
Wire Wire Line
	5300 2125 5800 2125
$Comp
L Device:D_Schottky D1
U 1 1 5D0895FB
P 3275 2025
F 0 "D1" H 3275 1809 50  0000 C CNN
F 1 "BYS12-90-E3/TR" H 3275 1900 50  0000 C CNN
F 2 "Diode_SMD:D_SMA_Handsoldering" H 3275 2025 50  0001 C CNN
F 3 "https://www.vishay.com/docs/88950/bys12-90.pdf" H 3275 2025 50  0001 C CNN
	1    3275 2025
	-1   0    0    1   
$EndComp
Wire Wire Line
	2775 2025 3125 2025
Wire Wire Line
	3425 2025 3725 2025
$Comp
L Mechanical:Heatsink HS1
U 1 1 5D0BDB36
P 9600 5650
F 0 "HS1" H 9742 5771 50  0000 L CNN
F 1 "SK 480/50 SA" H 9742 5680 50  0000 L CNN
F 2 "FischerElektronikHeatsinks:SK512_SK480_50MM" H 9612 5650 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/0f3d/0900766b80f3d603.pdf" H 9612 5650 50  0001 C CNN
F 4 "SK 480/50 SA" H 9600 5650 50  0001 C CNN "Mfr. No:"
F 5 "Fischer Elektronik" H 9600 5650 50  0001 C CNN "Mfr:"
F 6 "722-6874" H 9600 5650 50  0001 C CNN "RSComponentsNo"
	1    9600 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 5375 2450 5275
Wire Wire Line
	2450 5875 2450 5975
$Comp
L power:GNDS #PWR02
U 1 1 5D1167E0
P 2450 5975
F 0 "#PWR02" H 2450 5725 50  0001 C CNN
F 1 "GNDS" H 2455 5802 50  0000 C CNN
F 2 "" H 2450 5975 50  0001 C CNN
F 3 "" H 2450 5975 50  0001 C CNN
	1    2450 5975
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x07 J2
U 1 1 5D1271C3
P 6000 2025
F 0 "J2" H 6080 2067 50  0000 L CNN
F 1 "Conn_01x07" H 6080 1976 50  0001 L CNN
F 2 "Connector_Molex:Molex_KK-254_AE-6410-07A_1x07_P2.54mm_Vertical" H 6000 2025 50  0001 C CNN
F 3 "~" H 6000 2025 50  0001 C CNN
	1    6000 2025
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 2325 5600 2325
Wire Wire Line
	5600 2325 5600 2525
Wire Wire Line
	5800 2225 5600 2225
Wire Wire Line
	5600 2225 5600 1475
$Sheet
S 1725 14600 1850 800 
U 5D48EF64
F0 "PowerFlags" 50
F1 "PowerFlags.sch" 50
$EndSheet
Wire Wire Line
	5525 5475 5800 5475
Wire Wire Line
	5525 5675 6525 5675
Wire Wire Line
	5525 5875 5800 5875
$Comp
L Regulator_Linear:LM7812_TO220 U2
U 1 1 5D8AD9F3
P 7150 5175
F 0 "U2" H 7150 5414 50  0000 C CNN
F 1 "LM7812_TO220" H 7150 5325 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 7150 5400 50  0001 C CIN
F 3 "http://www.fairchildsemi.com/ds/LM/LM7805.pdf" H 7150 5125 50  0001 C CNN
	1    7150 5175
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LM7912_TO220 U3
U 1 1 5D8B3C95
P 7150 6175
F 0 "U3" H 7150 6026 50  0000 C CNN
F 1 "LM7912_TO220" H 7150 5937 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 7150 5975 50  0001 C CIN
F 3 "http://www.fairchildsemi.com/ds/LM/LM7905.pdf" H 7150 6175 50  0001 C CNN
	1    7150 6175
	1    0    0    -1  
$EndComp
Wire Wire Line
	5375 8625 5825 8625
Wire Wire Line
	5825 8625 5825 8925
$Comp
L power:GNDS #PWR017
U 1 1 5D8CCD07
P 7775 9050
F 0 "#PWR017" H 7775 8800 50  0001 C CNN
F 1 "GNDS" H 7780 8877 50  0000 C CNN
F 2 "" H 7775 9050 50  0001 C CNN
F 3 "" H 7775 9050 50  0001 C CNN
	1    7775 9050
	1    0    0    -1  
$EndComp
NoConn ~ 4375 8825
$Comp
L Device:C C1
U 1 1 5CFBC0DA
P 2750 5625
F 0 "C1" H 2865 5671 50  0000 L CNN
F 1 "4.7uF" H 2865 5580 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_4x5.7" H 2788 5475 50  0001 C CNN
F 3 "~" H 2750 5625 50  0001 C CNN
	1    2750 5625
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5D957D1D
P 4450 13000
F 0 "C2" H 4565 13046 50  0000 L CNN
F 1 "330nF" H 4565 12955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4488 12850 50  0001 C CNN
F 3 "~" H 4450 13000 50  0001 C CNN
	1    4450 13000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 12850 4450 12200
Wire Wire Line
	4450 13700 4450 13150
Wire Wire Line
	4450 12200 3900 12200
Wire Wire Line
	3900 12200 3900 11825
Wire Wire Line
	6475 13700 6475 13875
$Comp
L power:GNDS #PWR015
U 1 1 5D957D2C
P 6475 13875
F 0 "#PWR015" H 6475 13625 50  0001 C CNN
F 1 "GNDS" H 6480 13702 50  0000 C CNN
F 2 "" H 6475 13875 50  0001 C CNN
F 3 "" H 6475 13875 50  0001 C CNN
	1    6475 13875
	1    0    0    -1  
$EndComp
Connection ~ 4450 12200
Wire Wire Line
	5900 13150 5900 13700
Wire Wire Line
	5900 12200 5900 12850
Wire Wire Line
	2700 8750 2700 8975
$Comp
L power:GNDS #PWR04
U 1 1 5D990A90
P 2700 8975
F 0 "#PWR04" H 2700 8725 50  0001 C CNN
F 1 "GNDS" H 2705 8802 50  0000 C CNN
F 2 "" H 2700 8975 50  0001 C CNN
F 3 "" H 2700 8975 50  0001 C CNN
	1    2700 8975
	1    0    0    -1  
$EndComp
$Comp
L power:+15V #PWR013
U 1 1 5D9B4E3F
P 5300 1525
F 0 "#PWR013" H 5300 1375 50  0001 C CNN
F 1 "+15V" H 5315 1696 50  0000 C CNN
F 2 "" H 5300 1525 50  0001 C CNN
F 3 "" H 5300 1525 50  0001 C CNN
	1    5300 1525
	1    0    0    -1  
$EndComp
Text Notes 6325 2650 0    50   ~ 0
Pin Assignments:\n———————————\n1. Analog +12V\n2. Isolated GND\n3. Analog -12V\n4. Fan +15V\n5. Common GND\n6. Digital +5V\n7. Common GND\n\nPSU Module Nominal Current Usage:               65mA\n\nPSU Current Requirements:\n——————————————————\n\nA) Analog +/-12V   —>   CurrentSinkModule:   30mA\nB) Digital +5V       —>   ControlModule:       100mA\nC) +15V Fans        —>   Fans (x4):           150mA (700mA)
$Comp
L power:GNDS #PWR014
U 1 1 5D9BBD9E
P 5600 2525
F 0 "#PWR014" H 5600 2275 50  0001 C CNN
F 1 "GNDS" H 5605 2352 50  0000 C CNN
F 2 "" H 5600 2525 50  0001 C CNN
F 3 "" H 5600 2525 50  0001 C CNN
	1    5600 2525
	1    0    0    -1  
$EndComp
$Comp
L power:GNDS #PWR012
U 1 1 5D9BC201
P 5300 2525
F 0 "#PWR012" H 5300 2275 50  0001 C CNN
F 1 "GNDS" H 5305 2352 50  0000 C CNN
F 2 "" H 5300 2525 50  0001 C CNN
F 3 "" H 5300 2525 50  0001 C CNN
	1    5300 2525
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C5
U 1 1 5DA4B104
P 5900 13000
F 0 "C5" H 6017 13045 50  0000 L CNN
F 1 "100nF" H 6017 12956 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_4x5.7" H 5938 12850 50  0001 C CNN
F 3 "~" H 5900 13000 50  0001 C CNN
	1    5900 13000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 8300 3050 8300
Wire Wire Line
	2700 8300 2700 8125
Text Notes 1175 1075 0    100  ~ 0
Input/Output Connectors
Text Notes 1175 7625 0    100  ~ 0
B) Microcontroller PSU
Text Notes 1200 3925 0    100  ~ 0
A) Analog PSU
Text Notes 1150 10300 0    100  ~ 0
C) Fan PSU
$Comp
L Device:C C6
U 1 1 5D94D325
P 6250 8700
F 0 "C6" H 6365 8746 50  0000 L CNN
F 1 "330nF" H 6365 8655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6288 8550 50  0001 C CNN
F 3 "~" H 6250 8700 50  0001 C CNN
	1    6250 8700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 8550 6250 8425
Wire Wire Line
	6250 8925 6250 8850
Wire Wire Line
	5825 8925 6250 8925
Wire Wire Line
	6250 8425 6525 8425
Connection ~ 6250 8425
Wire Wire Line
	6825 8725 6825 8925
Wire Wire Line
	6250 8925 6825 8925
Connection ~ 6250 8925
Connection ~ 6825 8925
Wire Wire Line
	7325 8925 7775 8925
Wire Wire Line
	6825 8925 7325 8925
Connection ~ 7325 8925
Wire Wire Line
	7325 8850 7325 8925
Wire Wire Line
	7325 8425 7775 8425
Wire Wire Line
	7125 8425 7325 8425
Connection ~ 7325 8425
Wire Wire Line
	7325 8425 7325 8550
$Comp
L Device:C C10
U 1 1 5D94D361
P 7325 8700
F 0 "C10" H 7175 8825 50  0000 L CNN
F 1 "100nF" H 7050 8575 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7363 8550 50  0001 C CNN
F 3 "~" H 7325 8700 50  0001 C CNN
	1    7325 8700
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LM7805_TO220 U5
U 1 1 5D9569CB
P 6825 8425
F 0 "U5" H 6825 8667 50  0000 C CNN
F 1 "LM7805_TO220" H 6825 8576 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 6825 8650 50  0001 C CIN
F 3 "http://www.fairchildsemi.com/ds/LM/LM7805.pdf" H 6825 8375 50  0001 C CNN
	1    6825 8425
	1    0    0    -1  
$EndComp
Wire Wire Line
	5375 8425 6250 8425
Wire Wire Line
	7775 8925 7775 9050
Wire Wire Line
	3725 2025 3725 1625
$Comp
L power:+24V #PWR05
U 1 1 5D98D346
P 3725 1625
F 0 "#PWR05" H 3725 1475 50  0001 C CNN
F 1 "+24V" H 3740 1798 50  0000 C CNN
F 2 "" H 3725 1625 50  0001 C CNN
F 3 "" H 3725 1625 50  0001 C CNN
	1    3725 1625
	1    0    0    -1  
$EndComp
$Comp
L power:+24V #PWR01
U 1 1 5D98ED14
P 2450 5275
F 0 "#PWR01" H 2450 5125 50  0001 C CNN
F 1 "+24V" H 2465 5448 50  0000 C CNN
F 2 "" H 2450 5275 50  0001 C CNN
F 3 "" H 2450 5275 50  0001 C CNN
	1    2450 5275
	1    0    0    -1  
$EndComp
$Comp
L power:+24V #PWR07
U 1 1 5D98F63B
P 3900 11825
F 0 "#PWR07" H 3900 11675 50  0001 C CNN
F 1 "+24V" H 3915 11998 50  0000 C CNN
F 2 "" H 3900 11825 50  0001 C CNN
F 3 "" H 3900 11825 50  0001 C CNN
	1    3900 11825
	1    0    0    -1  
$EndComp
$Comp
L power:+24V #PWR03
U 1 1 5D990438
P 2700 8125
F 0 "#PWR03" H 2700 7975 50  0001 C CNN
F 1 "+24V" H 2715 8298 50  0000 C CNN
F 2 "" H 2700 8125 50  0001 C CNN
F 3 "" H 2700 8125 50  0001 C CNN
	1    2700 8125
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 5375 2450 5375
Wire Wire Line
	2450 5875 2750 5875
Connection ~ 2750 5875
Text Notes 4800 6075 0    50   ~ 0
Unregulated
Text Notes 4650 9025 0    50   ~ 0
Unregulated
Text Label 5875 5475 0    50   ~ 0
+15VA
Text Label 5875 5875 0    50   ~ 0
-15VA
Connection ~ 2750 5375
Connection ~ 4250 5375
Wire Wire Line
	4250 5375 4250 5475
Connection ~ 4250 5875
Wire Wire Line
	4250 5875 4250 5675
Wire Wire Line
	2750 5875 4250 5875
$Comp
L power:+5V #PWR016
U 1 1 5DA2C964
P 7775 8350
F 0 "#PWR016" H 7775 8200 50  0001 C CNN
F 1 "+5V" H 7790 8523 50  0000 C CNN
F 2 "" H 7775 8350 50  0001 C CNN
F 3 "" H 7775 8350 50  0001 C CNN
	1    7775 8350
	1    0    0    -1  
$EndComp
Wire Wire Line
	7775 8350 7775 8425
Text Notes 3075 11275 0    50   ~ 0
Thermal Spec:\n——————————\nAmb:       30C\n7818:      5K/W\n7815:      3K/W\nSK481:     5.5K/W\n
Wire Wire Line
	4450 12200 4875 12200
Wire Notes Line
	10900 3450 1225 3450
Wire Notes Line
	10875 7100 1200 7100
Wire Notes Line
	10875 9750 1200 9750
$Comp
L Regulator_Linear:LM7818_TO220 U6
U 1 1 5DB04640
P 5175 12200
F 0 "U6" H 5175 12442 50  0000 C CNN
F 1 "L7818CV" H 5175 12351 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 5175 12425 50  0001 C CIN
F 3 "https://docs-emea.rs-online.com/webdocs/1282/0900766b81282455.pdf" H 5175 12150 50  0001 C CNN
F 4 "STMicroelectronics" H 5175 12200 50  0001 C CNN "Mfr:"
F 5 "793-1352" H 5175 12200 50  0001 C CNN "RSComponentsNo"
	1    5175 12200
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LM7815_TO220 U7
U 1 1 5DB0595F
P 7750 12200
F 0 "U7" H 7750 12442 50  0000 C CNN
F 1 "L78M15ABV" H 7750 12351 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 7750 12425 50  0001 C CIN
F 3 "https://docs-emea.rs-online.com/webdocs/0dbd/0900766b80dbd968.pdf" H 7750 12150 50  0001 C CNN
F 4 "STMicroelectronics" H 7750 12200 50  0001 C CNN "Mfr:"
F 5 "686-9776" H 7750 12200 50  0001 C CNN "RSComponentsNo"
	1    7750 12200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 13700 5175 13700
Wire Wire Line
	5475 12200 5900 12200
Wire Wire Line
	5175 12500 5175 13700
Connection ~ 5175 13700
Wire Wire Line
	5175 13700 5900 13700
Connection ~ 5900 12200
Connection ~ 5900 13700
Wire Wire Line
	5900 13700 6475 13700
Wire Wire Line
	5900 12200 7050 12200
Wire Wire Line
	8450 13150 8450 13700
Wire Wire Line
	8450 12200 8450 12850
$Comp
L Device:CP C13
U 1 1 5DB3868E
P 8450 13000
F 0 "C13" H 8567 13045 50  0000 L CNN
F 1 "1uF" H 8567 12956 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_4x5.7" H 8488 12850 50  0001 C CNN
F 3 "~" H 8450 13000 50  0001 C CNN
	1    8450 13000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 12200 8450 12200
Wire Wire Line
	7750 12500 7750 13700
Connection ~ 7750 13700
Wire Wire Line
	7750 13700 8450 13700
$Comp
L Device:C C9
U 1 1 5DB43C49
P 7050 13000
F 0 "C9" H 7165 13046 50  0000 L CNN
F 1 "330nF" H 7165 12955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7088 12850 50  0001 C CNN
F 3 "~" H 7050 13000 50  0001 C CNN
	1    7050 13000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 12850 7050 12200
Wire Wire Line
	7050 13700 7050 13150
Connection ~ 7050 12200
Wire Wire Line
	7050 12200 7450 12200
Connection ~ 7050 13700
Wire Wire Line
	7050 13700 7750 13700
Connection ~ 8450 12200
Connection ~ 8450 13700
Connection ~ 6475 13700
Wire Wire Line
	6475 13700 7050 13700
Wire Wire Line
	8450 13700 9125 13700
Wire Wire Line
	8450 12200 9125 12200
Text Notes 9175 13275 0    50   ~ 0
Inductive Load\nProtection
$Comp
L Device:D D2
U 1 1 5D8561FF
P 9125 12975
F 0 "D2" V 9075 13125 50  0000 C CNN
F 1 "ES2G" V 9150 13150 50  0000 C CNN
F 2 "Diode_SMD:D_SMA_Handsoldering" H 9125 12975 50  0001 C CNN
F 3 "https://www.vishay.com/docs/88588/es2f.pdf" H 9125 12975 50  0001 C CNN
	1    9125 12975
	0    1    1    0   
$EndComp
Wire Wire Line
	9125 13125 9125 13700
Wire Wire Line
	9125 12825 9125 12200
Connection ~ 9125 12200
Wire Wire Line
	9125 12200 9675 12200
$Comp
L power:+15V #PWR021
U 1 1 5D47C9B7
P 9675 11800
F 0 "#PWR021" H 9675 11650 50  0001 C CNN
F 1 "+15V" H 9690 11971 50  0000 C CNN
F 2 "" H 9675 11800 50  0001 C CNN
F 3 "" H 9675 11800 50  0001 C CNN
	1    9675 11800
	1    0    0    -1  
$EndComp
Wire Wire Line
	9675 12200 9675 11800
$Comp
L Mechanical:Heatsink HS2
U 1 1 5DBBB007
P 5175 11700
F 0 "HS2" H 5317 11821 50  0000 L CNN
F 1 "SK 481/50 SA" H 5317 11730 50  0000 L CNN
F 2 "FischerElektronikHeatsinks:SK481_SK480_25MM" H 5187 11700 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/0f3d/0900766b80f3d603.pdf" H 5187 11700 50  0001 C CNN
F 4 "SK 481/50 SA" H 5175 11700 50  0001 C CNN "Mfr. No:"
F 5 "Fischer Elektronik" H 5175 11700 50  0001 C CNN "Mfr:"
F 6 "722-6864" H 5175 11700 50  0001 C CNN "RSComponentsNo"
F 7 "5.5K/W" H 5175 11700 50  0001 C CNN "Type"
	1    5175 11700
	1    0    0    -1  
$EndComp
Text Notes 9125 5825 0    50   ~ 0
Shared Between Analog/MCU regulators
$Comp
L DCConverters:ISE2409A-H U1
U 1 1 5DC160B0
P 4875 8625
F 0 "U1" H 4875 9090 50  0000 C CNN
F 1 "ISE2409A-H" H 4875 8999 50  0000 C CNN
F 2 "XPower_Converter_DCDC:ISE" H 4875 8725 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/150c/0900766b8150c3ee.pdf" H 4875 8725 50  0001 C CNN
F 4 "122-7381" H 4875 8625 50  0001 C CNN "RSComponentsNo"
	1    4875 8625
	1    0    0    -1  
$EndComp
$Comp
L DCConverters:R2D-2415 U4
U 1 1 5DC2BDC2
P 5025 5675
F 0 "U4" H 5025 6140 50  0000 C CNN
F 1 "R2D-2415" H 5025 6049 50  0000 C CNN
F 2 "RS6:R2D" H 5025 5775 50  0001 C CNN
F 3 "" H 5025 5775 50  0001 C CNN
	1    5025 5675
	1    0    0    -1  
$EndComp
Connection ~ 5800 5475
Connection ~ 5800 5875
Wire Wire Line
	5800 5875 5800 6475
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5DC7594A
P 4450 12200
F 0 "#FLG0101" H 4450 12275 50  0001 C CNN
F 1 "PWR_FLAG" H 4450 12373 50  0000 C CNN
F 2 "" H 4450 12200 50  0001 C CNN
F 3 "~" H 4450 12200 50  0001 C CNN
	1    4450 12200
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5DC76491
P 6250 8425
F 0 "#FLG0102" H 6250 8500 50  0001 C CNN
F 1 "PWR_FLAG" H 6250 8598 50  0000 C CNN
F 2 "" H 6250 8425 50  0001 C CNN
F 3 "~" H 6250 8425 50  0001 C CNN
	1    6250 8425
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C14
U 1 1 5DC76FBC
P 3050 8525
F 0 "C14" H 3168 8571 50  0000 L CNN
F 1 "4.7uF" H 3168 8480 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_4x5.7" H 3088 8375 50  0001 C CNN
F 3 "~" H 3050 8525 50  0001 C CNN
	1    3050 8525
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 8300 3050 8375
Wire Wire Line
	3050 8675 3050 8750
Wire Wire Line
	4375 8625 4200 8625
Wire Wire Line
	4200 8625 4200 8750
Wire Wire Line
	4200 8300 4200 8425
Wire Wire Line
	4200 8425 4375 8425
Connection ~ 3050 8300
Connection ~ 3050 8750
Wire Wire Line
	3050 8750 2700 8750
Wire Wire Line
	3050 8750 4200 8750
Wire Wire Line
	3050 8300 4200 8300
Wire Wire Line
	2750 5375 4250 5375
Text Label 5625 8425 0    50   ~ 0
+9V
Text Label 6450 12200 0    50   ~ 0
+18V
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 5DCC8D1F
P 6525 6175
F 0 "#FLG0103" H 6525 6250 50  0001 C CNN
F 1 "PWR_FLAG" H 6525 6348 50  0000 C CNN
F 2 "" H 6525 6175 50  0001 C CNN
F 3 "~" H 6525 6175 50  0001 C CNN
	1    6525 6175
	-1   0    0    1   
$EndComp
$Comp
L Mechanical:Heatsink HS3
U 1 1 5D88ED7E
P 7750 11700
F 0 "HS3" H 7892 11821 50  0000 L CNN
F 1 "SK 481/50 SA" H 7892 11730 50  0000 L CNN
F 2 "FischerElektronikHeatsinks:SK481_SK480_25MM" H 7762 11700 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/0f3d/0900766b80f3d603.pdf" H 7762 11700 50  0001 C CNN
F 4 "SK 481/50 SA" H 7750 11700 50  0001 C CNN "Mfr. No:"
F 5 "Fischer Elektronik" H 7750 11700 50  0001 C CNN "Mfr:"
F 6 "722-6864" H 7750 11700 50  0001 C CNN "RSComponentsNo"
F 7 "5.5K/W" H 7750 11700 50  0001 C CNN "Type"
	1    7750 11700
	1    0    0    -1  
$EndComp
Text Notes 4550 11300 0    50   ~ 0
U6 JC Power Dissipation: (24V-18V) * 0.7A = 4.2W \nU6 JC Temp: 5 * 4.2 = 21 degC \n\nHS2 Temp = 4.2 * 5.5 = 23.1 degC\n\nTotal U6 Temp = 30 + 21C + 23.1 = 74 degC
Text Notes 7150 11300 0    50   ~ 0
U7 JC Power Dissipation: (18V-15V) * 0.7A = 2.1W \nU7 JC Temp: 3 * 2.1 = 6.3 degC\n  \nHS3 Temp = 2.1 * 5.5 = 11.5 degC\n\nTotal U7 Temp = 30 + 6.3C + 11.5 = 47.8 degC
$Comp
L power:PWR_FLAG #FLG0104
U 1 1 5D9F43DD
P 6525 5175
F 0 "#FLG0104" H 6525 5250 50  0001 C CNN
F 1 "PWR_FLAG" H 6525 5348 50  0000 C CNN
F 2 "" H 6525 5175 50  0001 C CNN
F 3 "~" H 6525 5175 50  0001 C CNN
	1    6525 5175
	1    0    0    -1  
$EndComp
$EndSCHEMATC
