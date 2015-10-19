/**
 * @file HC06.h
 *
 * Declares the HC-06 class.
 */
#ifndef _HC06_h
#define _HC06_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <SoftwareSerial.h>

class BT_HC06
{

public:
	
	//line up with ValidBauds[] indexes, values line up with commands
	enum enumBaudRates : uint8_t
	{
		BAUD_1200 = 1,
		BAUD_2400,
		BAUD_4800,
		BAUD_9600,
		BAUD_19200,
		BAUD_38400,
		BAUD_57600,
		BAUD_115200,
		BAUD_230400,
		BAUD_460800,
		BAUD_921600,
		BAUD_1382400
	};

private:

	//valid HC-06 baud rates (starts at 1 to line up with selections), 0 = invalid
	const int32_t ValidBauds[13] = { 0, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600, 1382400 };
	
	SoftwareSerial& HC06Serial;

	String Pin;
	String Baud;

	String sendCommand(String command);
	unsigned long findConnectedBaud();
	bool testConnection();
	bool setName(String name);
	bool setPin(uint16_t pin);
	bool setBaud(enumBaudRates baud);

public:
	/**
	 * Constructor.
	 *
	 * @param [in,out] sw_serial The software serial port to be used
	 */
	BT_HC06(SoftwareSerial& sw_serial) : HC06Serial(sw_serial) {}

	/**
	 * Configures.
	 *
	 * @param name Bluetooth Device Name (20 Characters Maximum)
	 * @param pin  Bluetooth Device PIN (4 numeric characters)
	 * @param baud Baud rate of Bluetooth Serial Device
	 *
	 * @return true if it succeeds, false if it fails.
	 */
	bool configure(String name, uint16_t pin, enumBaudRates baud = BAUD_9600);
	

};


#endif

