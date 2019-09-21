EESchema Schematic File Version 4
LIBS:ControlModule-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 2
Title "System Overview"
Date "2019-04-11"
Rev "C"
Comp ""
Comment1 "Nominal Current Draw: 110mA"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 4050 1000 3900 2700
U 5D061C98
F0 "Control" 50
F1 "Control.sch" 50
F2 "VIN5" I L 4050 1350 50 
F3 "GND5" I L 4050 1800 50 
F4 "ADCSIG1" I L 4050 2250 50 
F5 "ADCSIG2" I L 4050 2800 50 
F6 "ADCGND1" I L 4050 2550 50 
F7 "ADCGND2" I L 4050 3100 50 
F8 "DACOUT1" I R 7950 2250 50 
F9 "DACOUT2" I R 7950 2800 50 
F10 "DACGND1" I R 7950 2550 50 
F11 "DACGND2" I R 7950 3100 50 
$EndSheet
Wire Wire Line
	4050 2800 2750 2800
Wire Wire Line
	2750 2250 4050 2250
$Comp
L Connector:Conn_Coaxial JADC1
U 1 1 5CC7B2F3
P 2550 2250
F 0 "JADC1" H 3000 2250 50  0000 C CNN
F 1 "SMA_RG402_Coax" H 3000 2100 50  0000 C CNN
F 2 "Connector_Coaxial:SMA_Amphenol_901-144_Vertical" H 2550 2250 50  0001 C CNN
F 3 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=1814832&DocType=Customer+Drawing&DocLang=English" H 2550 2250 50  0001 C CNN
F 4 "571-5-1814832-1" H 2550 2250 50  0001 C CNN "MouserNo"
F 5 "A97594-ND" H 2550 2250 50  0001 C CNN "DigikeyNo"
F 6 "TE Connectivity AMP Connectors" H 2550 2250 50  0001 C CNN "Mfr:"
F 7 "5-1814832-1" H 2550 2250 50  0001 C CNN "Mfr. No:"
	1    2550 2250
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2550 2550 2550 2450
$Comp
L Connector:Conn_Coaxial JADC2
U 1 1 5CC7BA18
P 2550 2800
F 0 "JADC2" H 3050 2800 50  0000 C CNN
F 1 "SMA_RG402_Coax" H 3000 2650 50  0000 C CNN
F 2 "Connector_Coaxial:SMA_Amphenol_901-144_Vertical" H 2550 2800 50  0001 C CNN
F 3 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=1814832&DocType=Customer+Drawing&DocLang=English" H 2550 2800 50  0001 C CNN
F 4 "571-5-1814832-1" H 2550 2800 50  0001 C CNN "MouserNo"
F 5 "A97594-ND" H 2550 2800 50  0001 C CNN "DigikeyNo"
F 6 "5-1814832-1" H 2550 2800 50  0001 C CNN "Mfr. No:"
	1    2550 2800
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2550 3000 2550 3100
Wire Wire Line
	7950 2800 9000 2800
Wire Wire Line
	9000 2250 7950 2250
$Comp
L Connector:Conn_Coaxial JDAC3
U 1 1 5F67ED39
P 9200 2250
F 0 "JDAC3" H 9650 2250 50  0000 C CNN
F 1 "SMA_RG402_Coax" H 9650 2100 50  0000 C CNN
F 2 "Connector_Coaxial:SMA_Amphenol_901-144_Vertical" H 9200 2250 50  0001 C CNN
F 3 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=1814832&DocType=Customer+Drawing&DocLang=English" H 9200 2250 50  0001 C CNN
F 4 "571-5-1814832-1" H 9200 2250 50  0001 C CNN "MouserNo"
F 5 "A97594-ND" H 9200 2250 50  0001 C CNN "DigikeyNo"
F 6 "5-1814832-1" H 9200 2250 50  0001 C CNN "Mfr. No:"
	1    9200 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 2550 9200 2450
$Comp
L Connector:Conn_Coaxial JDAC4
U 1 1 5F67ED41
P 9200 2800
F 0 "JDAC4" H 9700 2800 50  0000 C CNN
F 1 "SMA_RG402_Coax" H 9650 2650 50  0000 C CNN
F 2 "Connector_Coaxial:SMA_Amphenol_901-144_Vertical" H 9200 2800 50  0001 C CNN
F 3 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=1814832&DocType=Customer+Drawing&DocLang=English" H 9200 2800 50  0001 C CNN
F 4 "571-5-1814832-1" H 9200 2800 50  0001 C CNN "MouserNo"
F 5 "A97594-ND" H 9200 2800 50  0001 C CNN "DigikeyNo"
F 6 "5-1814832-1" H 9200 2800 50  0001 C CNN "Mfr. No:"
	1    9200 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 3000 9200 3100
$Comp
L Device:Jumper_NO_Small JP3
U 1 1 5F78D13A
P 8600 2550
F 0 "JP3" H 8600 2625 50  0000 C CNN
F 1 "ISOLATE" H 8600 2475 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Bridged_Pad1.0x1.5mm" H 8600 2550 50  0001 C CNN
F 3 "~" H 8600 2550 50  0001 C CNN
	1    8600 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8700 2550 9200 2550
Wire Wire Line
	8500 2550 7950 2550
$Comp
L Device:Jumper_NO_Small JP4
U 1 1 5F78D5D4
P 8600 3100
F 0 "JP4" H 8600 3175 50  0000 C CNN
F 1 "ISOLATE" H 8625 3025 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Bridged_Pad1.0x1.5mm" H 8600 3100 50  0001 C CNN
F 3 "~" H 8600 3100 50  0001 C CNN
	1    8600 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 3100 7950 3100
Wire Wire Line
	8700 3100 9200 3100
$Comp
L Device:Jumper_NO_Small JP2
U 1 1 5F78DA86
P 3200 3100
F 0 "JP2" H 3200 3175 50  0000 C CNN
F 1 "ISOLATE" H 3200 3025 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Bridged_Pad1.0x1.5mm" H 3200 3100 50  0001 C CNN
F 3 "~" H 3200 3100 50  0001 C CNN
	1    3200 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 3100 2550 3100
Wire Wire Line
	3300 3100 4050 3100
$Comp
L Device:Jumper_NO_Small JP1
U 1 1 5F78E7EE
P 3200 2550
F 0 "JP1" H 3200 2625 50  0000 C CNN
F 1 "ISOLATE" H 3200 2475 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Bridged_Pad1.0x1.5mm" H 3200 2550 50  0001 C CNN
F 3 "~" H 3200 2550 50  0001 C CNN
	1    3200 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 2550 2550 2550
Wire Wire Line
	3300 2550 4050 2550
Wire Wire Line
	2150 6200 2150 6000
Text Label 3275 6000 0    50   ~ 0
5V
NoConn ~ 2350 6200
NoConn ~ 2450 6200
NoConn ~ 2550 6200
Wire Wire Line
	4050 6500 4050 6600
Wire Wire Line
	2750 6600 4050 6600
$Comp
L Connector:TestPoint TP?
U 1 1 5E71B6B9
P 2150 5900
AR Path="/5D061C98/5E71B6B9" Ref="TP?"  Part="1" 
AR Path="/5E71B6B9" Ref="TP12"  Part="1" 
F 0 "TP12" H 2100 6125 50  0000 L CNN
F 1 "TestPoint" H 2207 5930 50  0001 L CNN
F 2 "TestPoint:TestPoint_Pad_2.0x2.0mm" H 2350 5900 50  0001 C CNN
F 3 "~" H 2350 5900 50  0001 C CNN
F 4 "855-S2751-46R" H 2150 5900 50  0001 C CNN "MouserNo"
F 5 "S2751-46R" H 2150 5900 50  0001 C CNN "Mfr. No:"
F 6 "Harwin" H 2150 5900 50  0001 C CNN "Mfr:"
	1    2150 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 5900 2150 6000
$Comp
L Connector:USB_B_Micro J_5VUSB?
U 1 1 5E71B6C1
P 2350 6500
AR Path="/5D061C98/5E71B6C1" Ref="J_5VUSB?"  Part="1" 
AR Path="/5E71B6C1" Ref="J_5VUSB1"  Part="1" 
F 0 "J_5VUSB1" V 2452 6830 50  0000 L CNN
F 1 "USB_B_Micro" V 2361 6830 50  0000 L CNN
F 2 "Connector_USB:USB_Micro-B_Amphenol_10103594-0001LF_Horizontal" H 2500 6450 50  0001 C CNN
F 3 "https://cdn.amphenol-icc.com/media/wysiwyg/files/documentation/datasheet/inputoutput/io_usb_micro.pdf" H 2500 6450 50  0001 C CNN
F 4 "609-4050-2-ND" H 2350 6500 50  0001 C CNN "DigikeyNo"
F 5 "649-10103594-0001LF" H 2350 6500 50  0001 C CNN "MouserNo"
F 6 "10103594-0001LF" H 2350 6500 50  0001 C CNN "Mfr. No:"
	1    2350 6500
	0    -1   -1   0   
$EndComp
Connection ~ 2150 6000
Wire Wire Line
	5100 5050 2350 5050
Connection ~ 4050 6500
Wire Wire Line
	5100 6500 4050 6500
Wire Wire Line
	3550 1350 3000 1350
Wire Wire Line
	4050 1800 3500 1800
Text Label 3500 1800 0    50   ~ 0
PWRGND
Text Label 5100 6500 2    50   ~ 0
PWRGND
Text Label 3000 1350 0    50   ~ 0
PWR5V
Text Label 5100 6000 2    50   ~ 0
PWR5V
Text Label 5100 5050 2    50   ~ 0
PWRGND
Text Label 5100 4950 2    50   ~ 0
PWR5V
$Comp
L Device:D_Schottky D?
U 1 1 5D67C6A2
P 3700 1350
AR Path="/5D061C98/5D67C6A2" Ref="D?"  Part="1" 
AR Path="/5D67C6A2" Ref="D1"  Part="1" 
F 0 "D1" H 3700 1200 50  0000 C CNN
F 1 "D_Schottky" H 3700 1500 50  0000 C CNN
F 2 "Diode_SMD:D_SMA_Handsoldering" H 3700 1350 50  0001 C CNN
F 3 "https://www.mouser.co.uk/datasheet/2/258/SS12FL~SS110FL(DO-221AC)-935242.pdf" H 3700 1350 50  0001 C CNN
F 4 "SS110FL-TPMSTR-ND" H 3700 1350 50  0001 C CNN "DigikeyNo"
F 5 "833-SS110FL-TP" H 3700 1350 50  0001 C CNN "MouserNo"
F 6 "SS110FL-TP" H 3700 1350 50  0001 C CNN "Mfr. No:"
	1    3700 1350
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3850 1350 4050 1350
Wire Wire Line
	2150 6000 5100 6000
Wire Wire Line
	2750 6500 4050 6500
$Comp
L Connector_Generic:Conn_01x02 JPWR1
U 1 1 5D504877
P 2150 5050
F 0 "JPWR1" H 2475 4950 50  0000 C CNN
F 1 "KK254_01x02" H 2500 5050 50  0000 C CNN
F 2 "Connector_Molex:Molex_KK-254_AE-6410-02A_1x02_P2.54mm_Vertical" H 2150 5050 50  0001 C CNN
F 3 "~" H 2150 5050 50  0001 C CNN
	1    2150 5050
	-1   0    0    1   
$EndComp
Wire Wire Line
	2350 4950 5100 4950
$EndSCHEMATC
