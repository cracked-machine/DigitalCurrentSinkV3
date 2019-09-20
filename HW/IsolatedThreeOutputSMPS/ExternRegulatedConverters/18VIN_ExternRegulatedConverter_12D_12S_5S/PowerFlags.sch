EESchema Schematic File Version 4
LIBS:ExternRegulatedConverter-cache
EELAYER 29 0
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
$Comp
L power:PWR_FLAG #FLG0107
U 1 1 5D497D1D
P 6200 3350
F 0 "#FLG0107" H 6200 3425 50  0001 C CNN
F 1 "PWR_FLAG" H 6200 3521 50  0000 C CNN
F 2 "" H 6200 3350 50  0001 C CNN
F 3 "~" H 6200 3350 50  0001 C CNN
	1    6200 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 3675 6200 3350
$Comp
L power:PWR_FLAG #FLG0106
U 1 1 5D497A82
P 5750 3350
F 0 "#FLG0106" H 5750 3425 50  0001 C CNN
F 1 "PWR_FLAG" H 5750 3521 50  0000 C CNN
F 2 "" H 5750 3350 50  0001 C CNN
F 3 "~" H 5750 3350 50  0001 C CNN
	1    5750 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 3650 5750 3350
$Comp
L power:GNDS #PWR0116
U 1 1 5D492EAD
P 5750 3650
F 0 "#PWR0116" H 5750 3400 50  0001 C CNN
F 1 "GNDS" H 5755 3479 50  0000 C CNN
F 2 "" H 5750 3650 50  0001 C CNN
F 3 "" H 5750 3650 50  0001 C CNN
	1    5750 3650
	1    0    0    -1  
$EndComp
$Comp
L power:VCOM #PWR0115
U 1 1 5D492B31
P 6200 3675
F 0 "#PWR0115" H 6200 3525 50  0001 C CNN
F 1 "VCOM" H 6218 3846 50  0000 C CNN
F 2 "" H 6200 3675 50  0001 C CNN
F 3 "" H 6200 3675 50  0001 C CNN
	1    6200 3675
	-1   0    0    1   
$EndComp
$Comp
L power:PWR_FLAG #FLG0105
U 1 1 5D491B70
P 3550 3375
F 0 "#FLG0105" H 3550 3450 50  0001 C CNN
F 1 "PWR_FLAG" H 3550 3546 50  0000 C CNN
F 2 "" H 3550 3375 50  0001 C CNN
F 3 "~" H 3550 3375 50  0001 C CNN
	1    3550 3375
	-1   0    0    1   
$EndComp
$Comp
L power:PWR_FLAG #FLG0104
U 1 1 5D49173E
P 4925 3975
F 0 "#FLG0104" H 4925 4050 50  0001 C CNN
F 1 "PWR_FLAG" H 4925 4146 50  0000 C CNN
F 2 "" H 4925 3975 50  0001 C CNN
F 3 "~" H 4925 3975 50  0001 C CNN
	1    4925 3975
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 5D49135F
P 4925 3375
F 0 "#FLG0103" H 4925 3450 50  0001 C CNN
F 1 "PWR_FLAG" H 4925 3546 50  0000 C CNN
F 2 "" H 4925 3375 50  0001 C CNN
F 3 "~" H 4925 3375 50  0001 C CNN
	1    4925 3375
	-1   0    0    1   
$EndComp
Wire Wire Line
	3550 3075 3550 3375
Wire Wire Line
	4925 4275 4925 3975
Wire Wire Line
	4925 3075 4925 3375
$Comp
L power:+5V #PWR0114
U 1 1 5D490E86
P 3550 3075
F 0 "#PWR0114" H 3550 2925 50  0001 C CNN
F 1 "+5V" H 3565 3246 50  0000 C CNN
F 2 "" H 3550 3075 50  0001 C CNN
F 3 "" H 3550 3075 50  0001 C CNN
	1    3550 3075
	1    0    0    -1  
$EndComp
$Comp
L power:-12V #PWR0113
U 1 1 5D490AFD
P 4925 4275
F 0 "#PWR0113" H 4925 4375 50  0001 C CNN
F 1 "-12V" H 4940 4446 50  0000 C CNN
F 2 "" H 4925 4275 50  0001 C CNN
F 3 "" H 4925 4275 50  0001 C CNN
	1    4925 4275
	-1   0    0    1   
$EndComp
$Comp
L power:+12V #PWR0112
U 1 1 5D48FE4E
P 4925 3075
F 0 "#PWR0112" H 4925 2925 50  0001 C CNN
F 1 "+12V" H 4940 3246 50  0000 C CNN
F 2 "" H 4925 3075 50  0001 C CNN
F 3 "" H 4925 3075 50  0001 C CNN
	1    4925 3075
	1    0    0    -1  
$EndComp
$EndSCHEMATC