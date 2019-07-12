EESchema Schematic File Version 4
LIBS:IsolatedConverterTripleOutputPSU-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Triple Output Isolated Power Supply (Regulated)"
Date "2019-05-11"
Rev "B"
Comp ""
Comment1 "Output Current: 250mA (+/-12V), 1200mA (5V)"
Comment2 "Output Voltage: +12V, -12V, COM, 5V"
Comment3 "Input Voltage: 12V"
Comment4 ""
$EndDescr
$Comp
L Device:D_Schottky D1
U 1 1 5CD20F82
P 1650 2900
F 0 "D1" H 1650 2684 50  0000 C CNN
F 1 "D_Schottky" H 1650 2775 50  0000 C CNN
F 2 "Diode_THT:D_DO-15_P2.54mm_Vertical_AnodeUp" H 1650 2900 50  0001 C CNN
F 3 "~" H 1650 2900 50  0001 C CNN
	1    1650 2900
	-1   0    0    1   
$EndComp
$Comp
L power:GNDS #PWR0102
U 1 1 5CD21457
P 1400 3800
F 0 "#PWR0102" H 1400 3550 50  0001 C CNN
F 1 "GNDS" H 1405 3627 50  0000 C CNN
F 2 "" H 1400 3800 50  0001 C CNN
F 3 "" H 1400 3800 50  0001 C CNN
	1    1400 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 3000 1400 3000
Wire Wire Line
	1400 3000 1400 3800
Wire Wire Line
	5650 3200 5500 3200
$Comp
L power:GNDS #PWR0103
U 1 1 5CD21BE2
P 5300 3900
F 0 "#PWR0103" H 5300 3650 50  0001 C CNN
F 1 "GNDS" H 5305 3727 50  0000 C CNN
F 2 "" H 5300 3900 50  0001 C CNN
F 3 "" H 5300 3900 50  0001 C CNN
	1    5300 3900
	1    0    0    -1  
$EndComp
NoConn ~ 5650 2600
NoConn ~ 6650 2600
Wire Wire Line
	6650 3000 8400 3000
Wire Wire Line
	9400 3000 9400 3900
Wire Wire Line
	10650 3800 9600 3800
Wire Wire Line
	9600 3800 9600 2500
Wire Wire Line
	9800 4500 10650 4500
Text Label 10000 3900 0    50   ~ 0
COM
Text Label 10000 3800 0    50   ~ 0
+12V
Text Label 10000 4000 0    50   ~ 0
-12V
Text Label 10000 4500 0    50   ~ 0
+5V
Text Notes 10250 4500 0    50   ~ 0
400mA
Text Notes 10250 3800 0    50   ~ 0
250mA
Text Notes 10250 3900 0    50   ~ 0
250mA
Wire Wire Line
	2400 3200 2400 2900
$Comp
L power:GNDS #PWR0107
U 1 1 5CD3095B
P 2400 3900
F 0 "#PWR0107" H 2400 3650 50  0001 C CNN
F 1 "GNDS" H 2405 3727 50  0000 C CNN
F 2 "" H 2400 3900 50  0001 C CNN
F 3 "" H 2400 3900 50  0001 C CNN
	1    2400 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 3500 2400 3900
Wire Wire Line
	2400 2900 2900 2900
Connection ~ 2400 2900
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 5CD481ED
P 950 3000
F 0 "J1" H 870 2675 50  0000 C CNN
F 1 "Conn_01x02" H 870 2766 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 950 3000 50  0001 C CNN
F 3 "~" H 950 3000 50  0001 C CNN
	1    950  3000
	-1   0    0    1   
$EndComp
$Comp
L Device:CP C3
U 1 1 5CD2D2F7
P 2400 3350
F 0 "C3" H 2518 3396 50  0000 L CNN
F 1 "10uF" H 2518 3305 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 2438 3200 50  0001 C CNN
F 3 "~" H 2400 3350 50  0001 C CNN
	1    2400 3350
	1    0    0    -1  
$EndComp
$Comp
L DCConverters:RS6-1212D U1
U 1 1 5CD67656
P 6150 2900
F 0 "U1" H 6150 3465 50  0000 C CNN
F 1 "RS6-1212D" H 6150 3374 50  0000 C CNN
F 2 "ITX1212S:ITX1212S" H 6150 2900 50  0001 C CNN
F 3 "https://recom-power.com/pdf/Econoline/RS6.pdf" H 6150 2900 50  0001 C CNN
	1    6150 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 3900 10650 3900
Wire Wire Line
	10650 4000 8900 4000
Wire Wire Line
	5300 3200 5300 3900
$Comp
L power:GNDS #PWR0101
U 1 1 5CD6FCD9
P 5300 5900
F 0 "#PWR0101" H 5300 5650 50  0001 C CNN
F 1 "GNDS" H 5305 5727 50  0000 C CNN
F 2 "" H 5300 5900 50  0001 C CNN
F 3 "" H 5300 5900 50  0001 C CNN
	1    5300 5900
	1    0    0    -1  
$EndComp
NoConn ~ 5650 4900
NoConn ~ 6650 4900
Wire Wire Line
	2500 5500 2500 5200
$Comp
L power:GNDS #PWR0104
U 1 1 5CD6FCE3
P 2500 5900
F 0 "#PWR0104" H 2500 5650 50  0001 C CNN
F 1 "GNDS" H 2505 5727 50  0000 C CNN
F 2 "" H 2500 5900 50  0001 C CNN
F 3 "" H 2500 5900 50  0001 C CNN
	1    2500 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 5800 2500 5900
$Comp
L pspice:INDUCTOR L2
U 1 1 5CD6FCEA
P 3000 5200
F 0 "L2" H 3000 5415 50  0000 C CNN
F 1 "1mH" H 3000 5324 50  0000 C CNN
F 2 "Inductor_THT:L_Radial_D12.0mm_P5.00mm_Fastron_11P" H 3000 5200 50  0001 C CNN
F 3 "" H 3000 5200 50  0001 C CNN
	1    3000 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 5200 2750 5200
Connection ~ 2500 5200
Wire Wire Line
	1900 5200 2500 5200
$Comp
L Device:CP C1
U 1 1 5CD6FCF3
P 2500 5650
F 0 "C1" H 2618 5696 50  0000 L CNN
F 1 "10uF" H 2618 5605 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 2538 5500 50  0001 C CNN
F 3 "~" H 2500 5650 50  0001 C CNN
	1    2500 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 5500 5300 5900
$Comp
L DCConverters:RS6-1205S U2
U 1 1 5CD731AB
P 6150 5200
F 0 "U2" H 6150 5765 50  0000 C CNN
F 1 "RS6-1205S" H 6150 5674 50  0000 C CNN
F 2 "ITX1212S:ITX1212S" H 6150 5200 50  0001 C CNN
F 3 "https://recom-power.com/pdf/Econoline/RS6.pdf" H 6150 5200 50  0001 C CNN
	1    6150 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	9800 4500 9800 5100
$Comp
L power:GNDS #PWR0105
U 1 1 5CD74AE7
P 9800 5900
F 0 "#PWR0105" H 9800 5650 50  0001 C CNN
F 1 "GNDS" H 9805 5727 50  0000 C CNN
F 2 "" H 9800 5900 50  0001 C CNN
F 3 "" H 9800 5900 50  0001 C CNN
	1    9800 5900
	1    0    0    -1  
$EndComp
NoConn ~ 6650 5500
Wire Wire Line
	1800 2900 1900 2900
Wire Wire Line
	1900 2900 1900 5200
Connection ~ 1900 2900
$Comp
L Device:L L5
U 1 1 5CF2DAF7
P 8050 2500
F 0 "L5" V 8240 2500 50  0000 C CNN
F 1 "10mH" V 8149 2500 50  0000 C CNN
F 2 "Inductor_THT:L_Radial_D8.7mm_P5.00mm_Fastron_07HCP" H 8050 2500 50  0001 C CNN
F 3 "~" H 8050 2500 50  0001 C CNN
	1    8050 2500
	0    -1   -1   0   
$EndComp
$Comp
L Device:L L6
U 1 1 5CF2E3A2
P 8050 3500
F 0 "L6" V 8240 3500 50  0000 C CNN
F 1 "10mH" V 8149 3500 50  0000 C CNN
F 2 "Inductor_THT:L_Radial_D8.7mm_P5.00mm_Fastron_07HCP" H 8050 3500 50  0001 C CNN
F 3 "~" H 8050 3500 50  0001 C CNN
	1    8050 3500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9600 2500 8900 2500
Wire Wire Line
	8400 2500 8400 2600
Connection ~ 8400 2500
Wire Wire Line
	8400 2500 8200 2500
Wire Wire Line
	8400 2900 8400 3000
Connection ~ 8400 3000
Wire Wire Line
	8400 3000 8900 3000
Wire Wire Line
	8400 3400 8400 3500
Wire Wire Line
	8400 3500 8200 3500
Connection ~ 8400 3500
Wire Wire Line
	8400 3500 8400 4000
Wire Wire Line
	7900 2500 7700 2500
Wire Wire Line
	7700 2500 7700 2800
Wire Wire Line
	6650 3200 6800 3200
Wire Wire Line
	7700 3200 7700 3500
Wire Wire Line
	7700 3500 7900 3500
Wire Wire Line
	8400 3000 8400 3100
Wire Wire Line
	7700 5300 7700 5600
Wire Wire Line
	7700 5600 8400 5600
Wire Wire Line
	9800 5600 9800 5900
$Comp
L Device:C C7
U 1 1 5CF35D04
P 8400 5350
F 0 "C7" H 8515 5396 50  0000 L CNN
F 1 "220uF" H 8515 5305 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D8.0mm_P5.00mm" H 8438 5200 50  0001 C CNN
F 3 "~" H 8400 5350 50  0001 C CNN
	1    8400 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 5500 8400 5600
Connection ~ 8400 5600
Wire Wire Line
	8400 5600 8900 5600
Wire Wire Line
	8400 5100 8400 5200
Wire Wire Line
	8400 5100 8900 5100
$Comp
L Device:L L7
U 1 1 5CF38C88
P 8050 5100
F 0 "L7" V 8240 5100 50  0000 C CNN
F 1 "10uH" V 8149 5100 50  0000 C CNN
F 2 "Inductor_THT:L_Radial_D8.7mm_P5.00mm_Fastron_07HCP" H 8050 5100 50  0001 C CNN
F 3 "~" H 8050 5100 50  0001 C CNN
	1    8050 5100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8200 5100 8400 5100
Connection ~ 8400 5100
Text Notes 7200 1850 0    50   ~ 0
FreqCutoff should be 10% of converter freq \n(200KHz).\n\nSee datasheet in component.\n\nFc = \n\n1 / (2π * SQRT(4.7uF * 1uH)) \n\n                 = 23.2KHz
Wire Wire Line
	1900 2900 2400 2900
Wire Wire Line
	1150 2900 1500 2900
Wire Notes Line
	7100 700  7100 6000
Wire Notes Line
	9100 700  9100 5950
Text Notes 7200 950  0    100  ~ 0
OUTPUT FILTER
Wire Wire Line
	4000 3200 4000 2900
$Comp
L power:GNDS #PWR0106
U 1 1 5CF591CA
P 4000 3900
F 0 "#PWR0106" H 4000 3650 50  0001 C CNN
F 1 "GNDS" H 4005 3727 50  0000 C CNN
F 2 "" H 4000 3900 50  0001 C CNN
F 3 "" H 4000 3900 50  0001 C CNN
	1    4000 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 3500 4000 3900
$Comp
L pspice:INDUCTOR L3
U 1 1 5CF591D1
P 4500 2900
F 0 "L3" H 4500 3200 50  0000 C CNN
F 1 "220uH" H 4500 3100 50  0000 C CNN
F 2 "Inductor_THT:L_Radial_D8.7mm_P5.00mm_Fastron_07HCP" H 4500 2900 50  0001 C CNN
F 3 "" H 4500 2900 50  0001 C CNN
	1    4500 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 2900 4250 2900
Connection ~ 4000 2900
$Comp
L Device:CP C2
U 1 1 5CF591D9
P 4000 3350
F 0 "C2" H 4118 3396 50  0000 L CNN
F 1 "10uF" H 4118 3305 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 4038 3200 50  0001 C CNN
F 3 "~" H 4000 3350 50  0001 C CNN
	1    4000 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 2900 4000 2900
Wire Wire Line
	4000 5500 4000 5200
$Comp
L power:GNDS #PWR0108
U 1 1 5CF59EB5
P 4000 5900
F 0 "#PWR0108" H 4000 5650 50  0001 C CNN
F 1 "GNDS" H 4005 5727 50  0000 C CNN
F 2 "" H 4000 5900 50  0001 C CNN
F 3 "" H 4000 5900 50  0001 C CNN
	1    4000 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 5800 4000 5900
$Comp
L pspice:INDUCTOR L4
U 1 1 5CF59EBC
P 4500 5200
F 0 "L4" H 4500 5415 50  0000 C CNN
F 1 "220uH" H 4500 5324 50  0000 C CNN
F 2 "Inductor_THT:L_Radial_D8.7mm_P5.00mm_Fastron_07HCP" H 4500 5200 50  0001 C CNN
F 3 "" H 4500 5200 50  0001 C CNN
	1    4500 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 5200 4250 5200
Connection ~ 4000 5200
$Comp
L Device:CP C4
U 1 1 5CF59EC4
P 4000 5650
F 0 "C4" H 4118 5696 50  0000 L CNN
F 1 "10uF" H 4118 5605 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 4038 5500 50  0001 C CNN
F 3 "~" H 4000 5650 50  0001 C CNN
	1    4000 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 5200 4000 5200
Wire Wire Line
	4750 2900 5500 2900
Text Notes 2350 950  0    100  ~ 0
INRUSH LIMIT
Text Notes 3700 950  0    100  ~ 0
INPUT FILTER
Wire Notes Line
	5200 700  5200 6000
Wire Notes Line
	3600 6000 3600 700 
Wire Notes Line
	2200 700  2200 6000
Text Notes 3700 1450 0    50   ~ 0
Fc = \n\n1 / ( 2π * SQRT(10uF * 100uH) ) \n               \n                           = 5KHz  
Text Notes 5400 950  0    100  ~ 0
DC-DC CONVERTER
$Comp
L Connector:TestPoint TP1
U 1 1 5CF6FD19
P 4000 2900
F 0 "TP1" H 4050 3150 50  0000 R CNN
F 1 "TestPoint" H 4450 3000 50  0001 R CNN
F 2 "" H 4200 2900 50  0001 C CNN
F 3 "~" H 4200 2900 50  0001 C CNN
	1    4000 2900
	-1   0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP3
U 1 1 5CF70026
P 7400 2700
F 0 "TP3" H 7450 2950 50  0000 R CNN
F 1 "TestPoint" H 7850 2800 50  0001 R CNN
F 2 "" H 7600 2700 50  0001 C CNN
F 3 "~" H 7600 2700 50  0001 C CNN
	1    7400 2700
	-1   0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP4
U 1 1 5CF71338
P 7400 3300
F 0 "TP4" H 7450 3550 50  0000 R CNN
F 1 "TestPoint" H 7850 3400 50  0001 R CNN
F 2 "" H 7600 3300 50  0001 C CNN
F 3 "~" H 7600 3300 50  0001 C CNN
	1    7400 3300
	1    0    0    1   
$EndComp
Wire Wire Line
	6650 2800 6800 2800
Wire Wire Line
	7400 3300 7400 3200
Connection ~ 7400 3200
Wire Wire Line
	7400 3200 7700 3200
Wire Wire Line
	7400 2700 7400 2800
Connection ~ 7400 2800
Wire Wire Line
	7400 2800 7700 2800
$Comp
L Connector:TestPoint TP5
U 1 1 5CF75AA5
P 7400 5000
F 0 "TP5" H 7450 5250 50  0000 R CNN
F 1 "TestPoint" H 7850 5100 50  0001 R CNN
F 2 "" H 7600 5000 50  0001 C CNN
F 3 "~" H 7600 5000 50  0001 C CNN
	1    7400 5000
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7400 5000 7400 5100
$Comp
L Connector:TestPoint TP2
U 1 1 5CF770BA
P 4000 5200
F 0 "TP2" H 4050 5450 50  0000 R CNN
F 1 "TestPoint" H 4450 5300 50  0001 R CNN
F 2 "" H 4200 5200 50  0001 C CNN
F 3 "~" H 4200 5200 50  0001 C CNN
	1    4000 5200
	-1   0    0    -1  
$EndComp
Connection ~ 7400 5100
Wire Wire Line
	7400 5100 7900 5100
$Comp
L Connector:TestPoint TP6
U 1 1 5CF8A716
P 8900 2400
F 0 "TP6" H 8950 2650 50  0000 R CNN
F 1 "TestPoint" H 9350 2500 50  0001 R CNN
F 2 "" H 9100 2400 50  0001 C CNN
F 3 "~" H 9100 2400 50  0001 C CNN
	1    8900 2400
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8900 2400 8900 2500
Connection ~ 8900 2500
Wire Wire Line
	8900 2500 8400 2500
$Comp
L Connector:TestPoint TP7
U 1 1 5CF8BC5A
P 8900 2900
F 0 "TP7" H 8950 3150 50  0000 R CNN
F 1 "TestPoint" H 9350 3000 50  0001 R CNN
F 2 "" H 9100 2900 50  0001 C CNN
F 3 "~" H 9100 2900 50  0001 C CNN
	1    8900 2900
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8900 2900 8900 3000
Connection ~ 8900 3000
Wire Wire Line
	8900 3000 9400 3000
$Comp
L Connector:TestPoint TP8
U 1 1 5CF8D28A
P 8900 3900
F 0 "TP8" H 8950 4150 50  0000 R CNN
F 1 "TestPoint" H 9350 4000 50  0001 R CNN
F 2 "" H 9100 3900 50  0001 C CNN
F 3 "~" H 9100 3900 50  0001 C CNN
	1    8900 3900
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8900 3900 8900 4000
Connection ~ 8900 4000
Wire Wire Line
	8900 4000 8400 4000
$Comp
L Connector:TestPoint TP9
U 1 1 5CF8E9C2
P 8900 5000
F 0 "TP9" H 8950 5250 50  0000 R CNN
F 1 "TestPoint" H 9350 5100 50  0001 R CNN
F 2 "" H 9100 5000 50  0001 C CNN
F 3 "~" H 9100 5000 50  0001 C CNN
	1    8900 5000
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8900 5000 8900 5100
Connection ~ 8900 5100
Wire Wire Line
	8900 5100 9800 5100
$Comp
L Connector:TestPoint TP10
U 1 1 5CF901DF
P 8900 5500
F 0 "TP10" H 8950 5750 50  0000 R CNN
F 1 "TestPoint" H 9350 5600 50  0001 R CNN
F 2 "" H 9100 5500 50  0001 C CNN
F 3 "~" H 9100 5500 50  0001 C CNN
	1    8900 5500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8900 5500 8900 5600
Connection ~ 8900 5600
Wire Wire Line
	8900 5600 9500 5600
$Comp
L Connector_Generic:Conn_01x08 J2
U 1 1 5CF316FD
P 10850 4100
F 0 "J2" H 10930 4092 50  0000 L CNN
F 1 "Conn_01x08" H 10930 4003 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical" H 10850 4100 50  0001 C CNN
F 3 "~" H 10850 4100 50  0001 C CNN
	1    10850 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	10650 4400 9500 4400
Wire Wire Line
	9500 4400 9500 5600
Connection ~ 9500 5600
Wire Wire Line
	9500 5600 9800 5600
NoConn ~ 10650 4100
NoConn ~ 10650 4200
NoConn ~ 10650 4300
$Comp
L Device:C C9
U 1 1 5CF49441
P 6150 3700
F 0 "C9" V 5901 3700 50  0000 C CNN
F 1 "100p" V 5990 3700 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D5.0mm_W2.5mm_P5.00mm" H 6188 3550 50  0001 C CNN
F 3 "~" H 6150 3700 50  0001 C CNN
	1    6150 3700
	0    1    1    0   
$EndComp
$Comp
L Device:C C8
U 1 1 5CF494BE
P 6150 1900
F 0 "C8" V 5901 1900 50  0000 C CNN
F 1 "47p" V 5990 1900 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D5.0mm_W2.5mm_P5.00mm" H 6188 1750 50  0001 C CNN
F 3 "~" H 6150 1900 50  0001 C CNN
	1    6150 1900
	0    1    1    0   
$EndComp
Wire Wire Line
	6000 1900 5500 1900
Wire Wire Line
	5500 1900 5500 2900
Connection ~ 5500 2900
Wire Wire Line
	5500 2900 5650 2900
Wire Wire Line
	6300 1900 6800 1900
Wire Wire Line
	6800 1900 6800 2800
Connection ~ 6800 2800
Wire Wire Line
	6800 2800 7400 2800
Wire Wire Line
	6000 3700 5500 3700
Wire Wire Line
	5500 3700 5500 3200
Connection ~ 5500 3200
Wire Wire Line
	5500 3200 5300 3200
Wire Wire Line
	6300 3700 6800 3700
Wire Wire Line
	6800 3700 6800 3200
Connection ~ 6800 3200
Wire Wire Line
	6800 3200 7400 3200
Wire Wire Line
	4750 5200 5650 5200
Wire Wire Line
	6650 5100 7400 5100
Wire Wire Line
	6650 5300 7700 5300
Wire Wire Line
	5300 5500 5650 5500
$Comp
L Device:L_Core_Iron_Coupled L1
U 1 1 5CF548F1
P 3100 3000
F 0 "L1" H 3100 3400 50  0000 C CNN
F 1 "1mH" H 3100 3300 50  0000 C CNN
F 2 "Inductor_THT:Choke_Schaffner_RN212-04-12.5x18.0mm" H 3100 3000 50  0001 C CNN
F 3 "~" H 3100 3000 50  0001 C CNN
	1    3100 3000
	1    0    0    -1  
$EndComp
$Comp
L power:GNDS #PWR0109
U 1 1 5CF5B596
P 2800 3900
F 0 "#PWR0109" H 2800 3650 50  0001 C CNN
F 1 "GNDS" H 2805 3727 50  0000 C CNN
F 2 "" H 2800 3900 50  0001 C CNN
F 3 "" H 2800 3900 50  0001 C CNN
	1    2800 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 3100 2800 3900
Wire Wire Line
	2800 3100 2900 3100
$Comp
L power:GNDS #PWR0110
U 1 1 5CF62471
P 3400 3900
F 0 "#PWR0110" H 3400 3650 50  0001 C CNN
F 1 "GNDS" H 3405 3727 50  0000 C CNN
F 2 "" H 3400 3900 50  0001 C CNN
F 3 "" H 3400 3900 50  0001 C CNN
	1    3400 3900
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3400 3100 3400 3900
Wire Wire Line
	3400 3100 3300 3100
$Comp
L Device:CP C5
U 1 1 5CF70D83
P 8400 2750
F 0 "C5" H 8518 2796 50  0000 L CNN
F 1 "220uF" H 8518 2705 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D8.0mm_P5.00mm" H 8438 2600 50  0001 C CNN
F 3 "~" H 8400 2750 50  0001 C CNN
	1    8400 2750
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C6
U 1 1 5CF70DE8
P 8400 3250
F 0 "C6" H 8518 3296 50  0000 L CNN
F 1 "220uF" H 8518 3205 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D8.0mm_P5.00mm" H 8438 3100 50  0001 C CNN
F 3 "~" H 8400 3250 50  0001 C CNN
	1    8400 3250
	1    0    0    -1  
$EndComp
$EndSCHEMATC
