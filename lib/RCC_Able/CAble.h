/*
Name:		CAble.h
Created:	09/04/2016 12:15:51
Author:		Haiqiang Xu
Version:	1.0
*/

#include "CBluetooth.h"
#include "CMotors.h"
#include "CMelodies.h"

const int iOutSpeaker = 8;
const int iOutLed1 = 13;
const int iOutRx = 2;
const int iOutTx = 3;
const int iOutLeft1 = 11;
const int iOutLeft2 = 12;
const int iOutRight1 = 9;
const int iOutRight2 = 10;
const int iOutEna = 5;
const int iOutEnb = 6;

class CAble
{
public:
	// Contructors
	CAble()
	{
		m_bluetooth = new CBluetooth(iOutRx, iOutTx, HC_06);	//RX, TX, EBluetoothAdapter
		m_motors = new CMotors(iOutLeft1, iOutLeft2, iOutRight1, iOutRight2, iOutEna, iOutEnb); //NOTE: pinENA and pinENB must be PWM pins!!!!!
		m_melodies = new CMelodies(iOutSpeaker);
	};
	
	// Public methods
	void setup();
	void loop();

	// Data accessors
	String GetLastCommand()
	{
		return m_sLastCmd;
	};

	String GetReadValue()
	{
		return m_sReadValue;
	};
private:
	// Fields
	CBluetooth* m_bluetooth;
	CMotors* m_motors;
	CMelodies* m_melodies;
	String m_sReadValue;
	int* m_intValues;
	char m_char;
	String m_sCmd, m_sLastCmd;
	
	// Private methods
	static void WakeUp();
	void ProcessJoystick(String sCommand);
	void ProcessButtons(String sCommand);
};