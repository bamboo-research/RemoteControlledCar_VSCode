/*
Name:		RRLCar_Able.ino
Created:	09/04/2016 12:15:51
Author:		Haiqiang Xu
Version:	1.0
*/

#include "CBluetooth.h"
#include "CMotors.h"
#include "CMelodies.h"
#include "main.h"

///#define DEBUG = true;

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

CBluetooth m_bluetooth(iOutRx, iOutTx, HC_06);	//RX, TX, EBluetoothAdapter
CMotors m_motors(iOutLeft1, iOutLeft2, iOutRight1, iOutRight2, iOutEna, iOutEnb); //NOTE: pinENA and pinENB must be PWM pins!!!!!
CMelodies m_melodies(iOutSpeaker);

String m_sReadValue;
int* m_byteValues;

void setup() {
    // put your setup code here, to run once:
    m_bluetooth.Begin(9600);
	pinMode(iOutLed1, OUTPUT);

#ifdef DEBUG
	Serial.begin(9600);
	Serial.println("Debugging car Akai");
#endif
}

void loop() {
    // put your main code here, to run repeatedly:
    	char c;
	String sCommand;

	//read from Bluetooth module
	m_sReadValue = m_bluetooth.Receive();
#ifdef DEBUG
	if (m_sReadValue.length() > 0)
		Serial.println("BT->" + m_sReadValue);
#endif
	if (m_sReadValue.length() <= 2)	//filter those messages without a minimum length
	{
		return;
	}

	//process received command
	for (int i = 0; i < m_sReadValue.length(); i++)
	{
		c = m_sReadValue[i];
		sCommand += c;				//concatenate chars until '#' end command is detected
		if (c == '#')
		{
			if (m_bluetooth.CommandType(sCommand) == ArrayBytes)
			{
				ProcessJoystick(sCommand);
			}
			else if (m_bluetooth.CommandType(sCommand) == StringCommand)
			{
				ProcessButtons(sCommand);
			}
			sCommand = "";
		}
	}
}

void ProcessJoystick(String sCommand)
{
	//process joystick values
	m_byteValues = m_bluetooth.ProcessArrayBytesCommand(sCommand);

#ifdef DEBUG
	//NOTE: by printing the pointer to array values, seems that affects these values
	//NOTE2: in fact, printing anything before calling ProcessMotors is provoking VERY strange behaviors in the variables
	//Serial.println("ArrayBytes command: " + String(m_byteValues[0]) + "," + String(m_byteValues[1]));
	//Serial.println("Joystick command: " + sCommand);
#endif

	//move motors accordingly
	m_motors.ProcessMotors((byte)m_byteValues[0], (byte)m_byteValues[1]);
#ifdef DEBUG
	Serial.println("Motor movement: " + m_motors.GetCurrMovString());
#endif
}

void ProcessButtons(String sCommand)
{
	//process buttons values
	sCommand = m_bluetooth.ProcessStringCommand(sCommand);

	if (sCommand == "j")
	{
		//switch-on LED
		if (digitalRead(iOutLed1) == LOW)
			digitalWrite(iOutLed1, HIGH);
		else
			digitalWrite(iOutLed1, LOW);
	}
	else if (sCommand == "x")
	{
		m_melodies.PlayMelody(Fanfarria);
	}
	else if (sCommand == "a")
	{
		m_melodies.PlayMelody(DogPower);
	}
	else if (sCommand == "h")
	{
		m_melodies.PlayMelody(R2D2);
	}
	else if (sCommand == "b")
	{
		int iSpeedMode = m_motors.GetSpeedMode();
		if (iSpeedMode == Slow)
			m_motors.SetSpeedMode(Normal);
		else if (iSpeedMode == Normal)
			m_motors.SetSpeedMode(Fast);
		else if (iSpeedMode == Fast)
			m_motors.SetSpeedMode(Turbo);
		else
			m_motors.SetSpeedMode(Slow);

		//make a sound to confirm SpeedMode
		iSpeedMode = m_motors.GetSpeedMode();
		for (int i = 0; i < iSpeedMode; i++)
		{
			digitalWrite(iOutSpeaker, HIGH);
			delay(50);
			digitalWrite(iOutSpeaker, LOW);
			delay(50);
		}
	}
	else
	{
		//Process command from Smartphone/Tablet
		m_motors.ProcessMotors(sCommand);
	}

#ifdef DEBUG
	Serial.println("Button command: " + sCommand);
#endif
}