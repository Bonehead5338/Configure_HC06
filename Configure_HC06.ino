#include <SoftwareSerial.h>
#include "HC06.h"

#define RX_PIN 10
#define TX_PIN 11

//software serial
SoftwareSerial SwSerial(RX_PIN, TX_PIN);
//HC-06 device
BT_HC06 HC06(SwSerial);

//configurable items
const String BT_NAME = "BT_DEVICE";			//max 20 characters
const uint16_t BT_PIN = 1234;				//max 4 characters

/*
Valid Baud Rates:
-------------------------
BAUD_1200
BAUD_2400
BAUD_4800
BAUD_9600
BAUD_19200
BAUD_38400
BAUD_57600
BAUD_115200
BAUD_230400
BAUD_460800
BAUD_921600
BAUD_1382400
*/
 
const BT_HC06::enumBaudRates BT_BAUD = HC06.BAUD_9600;

void setup()
{
	//Start serial monitor
	Serial.begin(115200);
	Serial.println("Serial started");
	
	//configure device
	HC06.configure(BT_NAME, BT_PIN, BT_BAUD);		
}

void loop()
{
	//nothing in loop
}


