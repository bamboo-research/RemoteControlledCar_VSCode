#include "CBluetooth.h"
#include "CCommon.h"

#define PIN_RX 2
#define PIN_TX 3

CBluetooth m_bluetooth(PIN_RX, PIN_TX, HC_06);
String m_sValue;

void setup()
{
	Serial.begin(9600);
	Serial.println("Debugging Bluetooth module");
}

void loop()
{
    //TODO: create new CBluetooth unit testing class
	//Read and send bluetooth after read of keyboard
	m_sValue = m_bluetooth.Receive();
	if (m_sValue.length() > 0)
		Serial.println("BT-> " + m_sValue);
	m_sValue = Common.ReadKeyboard();
	m_bluetooth.Send(m_sValue);
	if (m_sValue.length() > 0)
		Serial.println("-> " + m_sValue);
}