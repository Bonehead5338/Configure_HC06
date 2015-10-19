/**
 * HC06.cpp
 *
 * Implements the HC-06 class.
 */
#include "HC06.h"


bool BT_HC06::configure(String name, uint16_t pin, enumBaudRates baud)
{
	Serial.println("Looking for connected HC-06 modules");

	//find connected device
	int32_t current_baud = ValidBauds[findConnectedBaud()];
	if (current_baud == 0)
	{
		Serial.println("ERROR: Failed to detect connected HC-06!");
		return false;
	}
	else
	{
		Serial.print("Found device HC-06 at ");
		Serial.print(current_baud);
		Serial.println("bps");
	}

	//set name	
	if (!setName(name))
	{
		Serial.println("ERROR: Failed to set device name! (Over 20 Characters?)");
		return false;
	}
	else
	{
		Serial.print("Device Name successfully set to ");
		Serial.println(name);
	}

	//set PIN
	if (!setPin(pin))
	{
		Serial.println("ERROR: Failed to set device PIN! (less than 9999?)");
		return false;
	}
	else
	{
		Serial.print("Device PIN successfully set to ");
		Serial.println(Pin);
	}

	//set baud if different from detected baud
	if (current_baud != ValidBauds[baud])
	{
		if (!setBaud(baud))
		{
			Serial.println("ERROR: Failed to set baud rate!");
		}
		else
		{
			
			Serial.print("Baud configured at ");
			Serial.print(ValidBauds[baud]);
			Serial.println("bps");

			//test connection at new baud		
			HC06Serial.begin(ValidBauds[baud]);

			if (!testConnection())
			{
				Serial.println("ERROR: Failed to connect at new baud rate!");
				return false;
			}
			else
			{
				Serial.println("Successfully connected at new baud rate");
			}
		}
	}
	else
	{
		Serial.print("Baud already configured correctly at ");
		Serial.print(ValidBauds[baud]);
		Serial.println("bps");
	}

	Serial.println("Configuration completed successfully.");

	return true;
}

String BT_HC06::sendCommand(String command)
{
	HC06Serial.print(command);
	return HC06Serial.readString();
}

bool BT_HC06::testConnection()
{
	return sendCommand("AT") == "OK" ? true : false;
}

unsigned long BT_HC06::findConnectedBaud()
{
	for (uint8_t i = 1; i < 12; i++)
	{
		HC06Serial.begin(ValidBauds[i]);
		if (testConnection()) return i;
	}

	return 0; //no HC-06 found
}

bool BT_HC06::setName(String name)
{
	//check for valid name
	if (name.length() > 20)
		return false;

	//return true if completed successfully
	return sendCommand("AT+NAME" + name) == "OKsetname" ? true : false;
}

bool BT_HC06::setPin(uint16_t pin)
{
	//check for valid pin
	if (pin > 9999)
		return false;

	//convert pin to zero-padded string
	char charPin[5];
	sprintf(charPin, "%04d", pin);
	Pin = charPin;

	//return true if completed successfully
	return sendCommand("AT+PIN" + Pin) == "OKsetPIN" ? true : false;
}

bool BT_HC06::setBaud(enumBaudRates baud)
{	
	//get string of baud index
	String strBaud(baud, HEX);
	String response = sendCommand("AT+BAUD" + strBaud);

	//remove all except first two characters of response
	response.remove(2);

	//return true if completed successfully
	return response == "OK" ? true : false;
}

