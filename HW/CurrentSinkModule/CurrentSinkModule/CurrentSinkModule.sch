EESchema Schematic File Version 4
LIBS:CurrentSinkModule-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 2
Title "Mixed Signal Board for Digital Programmable Current Sink"
Date "2019-05-12"
Rev "C"
Comp "Designed by C Sutton"
Comment1 "Nominal Current Draw (0.1Ω Power Resistors): 95mA"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	8200 3700 9400 3700
Wire Wire Line
	8200 4300 9400 4300
Wire Wire Line
	8200 1800 8800 1800
Wire Wire Line
	8200 2200 8800 2200
Wire Wire Line
	8800 1900 8700 1900
Wire Wire Line
	8700 1900 8700 2100
Wire Wire Line
	8700 2100 8800 2100
Connection ~ 8700 1900
Wire Wire Line
	8700 1900 8200 1900
Wire Wire Line
	2800 3450 2800 3650
$Comp
L Connector:Conn_Coaxial JADC1
U 1 1 5CAD35C8
P 9600 3700
F 0 "JADC1" H 9699 3676 50  0000 L CNN
F 1 "SMA_RG402_Coax" H 9699 3585 50  0000 L CNN
F 2 "Connector_Coaxial:SMA_Amphenol_901-144_Vertical" H 9600 3700 50  0001 C CNN
F 3 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=1814832&DocType=Customer+Drawing&DocLang=English" H 9600 3700 50  0001 C CNN
F 4 "A97594-ND	" H 9600 3700 50  0001 C CNN "DigikeyNo"
F 5 "571-5-1814832-1" H 9600 3700 50  0001 C CNN "MouserNo"
F 6 "5-1814832-1" H 9600 3700 50  0001 C CNN "Mfr. No:"
	1    9600 3700
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_Coaxial JADC2
U 1 1 5CAD35F2
P 9600 4300
F 0 "JADC2" H 9699 4276 50  0000 L CNN
F 1 "SMA_RG402_Coax" H 9699 4185 50  0000 L CNN
F 2 "Connector_Coaxial:SMA_Amphenol_901-144_Vertical" H 9600 4300 50  0001 C CNN
F 3 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=1814832&DocType=Customer+Drawing&DocLang=English" H 9600 4300 50  0001 C CNN
F 4 "A97594-ND	" H 9600 4300 50  0001 C CNN "DigikeyNo"
F 5 "571-5-1814832-1" H 9600 4300 50  0001 C CNN "MouserNo"
F 6 "5-1814832-1" H 9600 4300 50  0001 C CNN "Mfr. No:"
	1    9600 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	9600 3900 9600 4000
Wire Wire Line
	9600 4500 9600 4600
$Comp
L Connector_Generic:Conn_01x03 JPWR1
U 1 1 5CAE8712
P 1650 3750
F 0 "JPWR1" H 1450 3500 50  0000 L CNN
F 1 "Conn_01x03" H 1250 3400 50  0000 L CNN
F 2 "Connector_Molex:Molex_KK-254_AE-6410-03A_1x03_P2.54mm_Vertical" H 1650 3750 50  0001 C CNN
F 3 "~" H 1650 3750 50  0001 C CNN
	1    1650 3750
	-1   0    0    -1  
$EndComp
Wire Notes Line
	1450 3750 1300 3750
Wire Notes Line
	1300 3750 1300 3300
Wire Notes Line
	1250 3300 1350 3300
Wire Notes Line
	1450 3700 1450 3800
Text Notes 1000 3250 0    50   ~ 0
Ext. Power Cable
$Comp
L Device:D_Schottky D1
U 1 1 5E7E7922
P 4350 3450
F 0 "D1" H 4350 3600 50  0000 C CNN
F 1 "D_Schottky" H 4350 3700 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 4350 3450 50  0001 C CNN
F 3 "~" H 4350 3450 50  0001 C CNN
	1    4350 3450
	-1   0    0    1   
$EndComp
$Comp
L Device:D_Schottky D2
U 1 1 5E7E7971
P 4350 4050
F 0 "D2" H 4350 4300 50  0000 C CNN
F 1 "D_Schottky" H 4350 4200 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 4350 4050 50  0001 C CNN
F 3 "~" H 4350 4050 50  0001 C CNN
	1    4350 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 3450 2800 3450
Wire Wire Line
	4500 4050 5100 4050
Wire Wire Line
	4500 3450 5400 3450
Wire Wire Line
	5100 4150 5100 4050
$Comp
L Connector:TestPoint TP?
U 1 1 5E7F8F70
P 5100 4150
AR Path="/5C977310/5E7F8F70" Ref="TP?"  Part="1" 
AR Path="/5E7F8F70" Ref="TP1"  Part="1" 
F 0 "TP1" V 5100 4400 50  0000 C CNN
F 1 "TestPoint" V 5204 4224 50  0001 C CNN
F 2 "TestPoint:TestPoint_Pad_2.0x2.0mm" H 5300 4150 50  0001 C CNN
F 3 "https://cdn.harwin.com/pdfs/S2751R.pdf" H 5300 4150 50  0001 C CNN
F 4 "855-S2751-46R" H 5100 4150 50  0001 C CNN "MouserNo"
F 5 "S2751-46R" H 5100 4150 50  0001 C CNN "Mfr. No:"
F 6 "Harwin" H 5100 4150 50  0001 C CNN "Mfr:"
	1    5100 4150
	-1   0    0    1   
$EndComp
Wire Wire Line
	5400 4150 5400 3450
$Comp
L Connector:TestPoint TP?
U 1 1 5E7FA137
P 5400 4150
AR Path="/5C977310/5E7FA137" Ref="TP?"  Part="1" 
AR Path="/5E7FA137" Ref="TP2"  Part="1" 
F 0 "TP2" V 5400 4400 50  0000 C CNN
F 1 "TestPoint" V 5504 4224 50  0001 C CNN
F 2 "TestPoint:TestPoint_Pad_2.0x2.0mm" H 5600 4150 50  0001 C CNN
F 3 "https://cdn.harwin.com/pdfs/S2751R.pdf" H 5600 4150 50  0001 C CNN
F 4 "855-S2751-46R" H 5400 4150 50  0001 C CNN "MouserNo"
F 5 "S2751-46R" H 5400 4150 50  0001 C CNN "Mfr. No:"
F 6 "Harwin" H 5400 4150 50  0001 C CNN "Mfr:"
	1    5400 4150
	-1   0    0    1   
$EndComp
Connection ~ 5400 3450
Connection ~ 5100 4050
Wire Wire Line
	1850 3850 2800 3850
Wire Wire Line
	2800 4050 2800 3850
Wire Wire Line
	2800 4050 4200 4050
Wire Wire Line
	6650 5050 5450 5050
Wire Wire Line
	6650 5650 5450 5650
$Comp
L Connector:Conn_Coaxial JDAC1
U 1 1 5D09BADF
P 5250 5050
F 0 "JDAC1" H 5349 5026 50  0000 L CNN
F 1 "SMA_RG402_Coax" H 5349 4935 50  0000 L CNN
F 2 "Connector_Coaxial:SMA_Amphenol_901-144_Vertical" H 5250 5050 50  0001 C CNN
F 3 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=1814832&DocType=Customer+Drawing&DocLang=English" H 5250 5050 50  0001 C CNN
F 4 "A97594-ND	" H 5250 5050 50  0001 C CNN "DigikeyNo"
F 5 "571-5-1814832-1" H 5250 5050 50  0001 C CNN "MouserNo"
F 6 "5-1814832-1" H 5250 5050 50  0001 C CNN "Mfr. No:"
	1    5250 5050
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Conn_Coaxial JDAC2
U 1 1 5D09BAE5
P 5250 5650
F 0 "JDAC2" H 5349 5626 50  0000 L CNN
F 1 "SMA_RG402_Coax" H 5349 5535 50  0000 L CNN
F 2 "Connector_Coaxial:SMA_Amphenol_901-144_Vertical" H 5250 5650 50  0001 C CNN
F 3 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=1814832&DocType=Customer+Drawing&DocLang=English" H 5250 5650 50  0001 C CNN
F 4 "A97594-ND	" H 5250 5650 50  0001 C CNN "DigikeyNo"
F 5 "571-5-1814832-1" H 5250 5650 50  0001 C CNN "MouserNo"
F 6 "5-1814832-1" H 5250 5650 50  0001 C CNN "Mfr. No:"
	1    5250 5650
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5250 5250 5250 5350
Wire Wire Line
	5250 5850 5250 5950
$Comp
L Device:Jumper_NC_Small JP1
U 1 1 5D30EC8D
P 5950 5350
F 0 "JP1" H 5950 5562 50  0000 C CNN
F 1 "Isolation" H 5950 5471 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_Pad1.0x1.5mm" H 5950 5350 50  0001 C CNN
F 3 "~" H 5950 5350 50  0001 C CNN
	1    5950 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 5350 5850 5350
Wire Wire Line
	6050 5350 6650 5350
$Comp
L Device:Jumper_NC_Small JP2
U 1 1 5D31137D
P 5950 5950
F 0 "JP2" H 5950 6162 50  0000 C CNN
F 1 "Isolation" H 5950 6071 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_Pad1.0x1.5mm" H 5950 5950 50  0001 C CNN
F 3 "~" H 5950 5950 50  0001 C CNN
	1    5950 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 5950 5850 5950
Wire Wire Line
	6050 5950 6650 5950
$Comp
L Device:Jumper_NC_Small JP3
U 1 1 5D312C46
P 8900 4000
F 0 "JP3" H 8900 4212 50  0000 C CNN
F 1 "Isolation" H 8900 4121 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_Pad1.0x1.5mm" H 8900 4000 50  0001 C CNN
F 3 "~" H 8900 4000 50  0001 C CNN
	1    8900 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 4000 8800 4000
Wire Wire Line
	9000 4000 9600 4000
$Comp
L Device:Jumper_NC_Small JP4
U 1 1 5D31438F
P 8900 4600
F 0 "JP4" H 8900 4812 50  0000 C CNN
F 1 "Isolation" H 8900 4721 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_Pad1.0x1.5mm" H 8900 4600 50  0001 C CNN
F 3 "~" H 8900 4600 50  0001 C CNN
	1    8900 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 4600 8800 4600
Wire Wire Line
	9000 4600 9600 4600
Wire Wire Line
	5800 4150 5800 3750
$Comp
L Connector:TestPoint TP?
U 1 1 5D0D123D
P 5800 4150
AR Path="/5C977310/5D0D123D" Ref="TP?"  Part="1" 
AR Path="/5D0D123D" Ref="GND9"  Part="1" 
F 0 "GND9" V 5800 4450 50  0000 C CNN
F 1 "TestPoint" V 5904 4224 50  0001 C CNN
F 2 "TestPoint:TestPoint_Pad_2.0x2.0mm" H 6000 4150 50  0001 C CNN
F 3 "https://cdn.harwin.com/pdfs/S2751R.pdf" H 6000 4150 50  0001 C CNN
F 4 "855-S2751-46R" H 5800 4150 50  0001 C CNN "MouserNo"
F 5 "S2751-46R" H 5800 4150 50  0001 C CNN "Mfr. No:"
F 6 "Harwin" H 5800 4150 50  0001 C CNN "Mfr:"
	1    5800 4150
	-1   0    0    1   
$EndComp
Connection ~ 5800 3750
Wire Wire Line
	1850 3750 5800 3750
$Comp
L Connector_Generic:Conn_01x02 J_SUTNEG1
U 1 1 5D4C25D8
P 9000 2200
F 0 "J_SUTNEG1" H 9300 2125 50  0000 C CNN
F 1 "MolexMicroFit_01x02" H 9475 2225 50  0000 C CNN
F 2 "Connector_Molex:Molex_Micro-Fit_3.0_43045-0212_2x01_P3.00mm_Vertical" H 9000 2200 50  0001 C CNN
F 3 "~" H 9000 2200 50  0001 C CNN
	1    9000 2200
	1    0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J_SUTPOS1
U 1 1 5D4C2BC6
P 9000 1800
F 0 "J_SUTPOS1" H 9100 1800 50  0000 L CNN
F 1 "MolexMicroFit_01x02" H 9075 1700 50  0000 L CNN
F 2 "Connector_Molex:Molex_Micro-Fit_3.0_43045-0212_2x01_P3.00mm_Vertical" H 9000 1800 50  0001 C CNN
F 3 "~" H 9000 1800 50  0001 C CNN
	1    9000 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 3650 1850 3650
Wire Wire Line
	5400 3450 6650 3450
Wire Wire Line
	5800 3750 6650 3750
Wire Wire Line
	5100 4050 6650 4050
$Sheet
S 6650 1600 1550 4550
U 5C977310
F0 "CurrentSink" 50
F1 "CurrentSink.sch" 50
F2 "GND" I L 6650 3750 50 
F3 "DUT_POS" I R 8200 1800 50 
F4 "GND" I R 8200 1900 50 
F5 "DUT_NEG" I R 8200 2200 50 
F6 "ADCSIG2" I R 8200 4300 50 
F7 "ADCSIG1" I R 8200 3700 50 
F8 "ADCGND1" I R 8200 4000 50 
F9 "ADCGND2" I R 8200 4600 50 
F10 "DACSIG1" I L 6650 5050 50 
F11 "DACSIG2" I L 6650 5650 50 
F12 "DACGND1" I L 6650 5350 50 
F13 "DACGND2" I L 6650 5950 50 
F14 "+12V" I L 6650 3450 50 
F15 "-12V" I L 6650 4050 50 
$EndSheet
$EndSCHEMATC
