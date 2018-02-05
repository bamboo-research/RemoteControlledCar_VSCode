/*
Name:		CAble.cpp
Created:	09/04/2016 12:15:51
Author:		Haiqiang Xu
Version:	1.0
*/

#include "CAble.h"
#include "LowPower.h"


#pragma region Public methods

void CAble::setup() {
    // put your setup code here, to run once:
    m_bluetooth->Begin(9600);
	pinMode(iOutLed1, OUTPUT);
}

void CAble::loop() {
	// Save power with LowerPower. Allow wake up interrupt when pin 2 detects change voltage.
	// Interrupt 0 corresponds I/O pin 2 and Interrupt 1 corresponds I/O pin 3 on Uno/Nano.
    attachInterrupt(0, CAble::WakeUp, CHANGE);
    
    // Enter power down state with ADC and BOD module disabled. Wake up when interrupt detected
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); 

	//read from Bluetooth module once woken up
	m_sReadValue = m_bluetooth->Receive();

	//filter those messages without a minimum length
	if (m_sReadValue.length() <= 2)
	{
		return;
	}

	//process received command
	for (int i = 0; i < m_sReadValue.length(); i++)
	{
		m_char = m_sReadValue[i];
		m_sCmd += m_char;			//concatenate chars until '#' end command is detected
		if (m_char == '#')
		{
			if (m_bluetooth->CommandType(m_sCmd) == ArrayBytes)
			{
				ProcessJoystick(m_sCmd);
			}
			else if (m_bluetooth->CommandType(m_sCmd) == StringCommand)
			{
				ProcessButtons(m_sCmd);
			}
			m_sCmd = "";
		}
	}
}

#pragma endregion

#pragma region Private methods

void CAble::WakeUp()
{
    // Just a handler for the pin interrupt.
	// Disable external interrupt on wake up pin.
    detachInterrupt(0); 
}

void CAble::ProcessJoystick(String sCommand)
{
	//process joystick values
	m_intValues = m_bluetooth->ProcessArrayBytesCommand(sCommand);

	//move motors accordingly
	m_motors->ProcessMotors((byte)m_intValues[0], (byte)m_intValues[1]);

	//set m_sLastCmd -> mainly for debug
	m_sLastCmd = "Cmd: " + sCommand + " | Motor movement: " + m_motors->GetCurrMovString();
}

void CAble::ProcessButtons(String sCommand)
{
	//process buttons values
	sCommand = m_bluetooth->ProcessStringCommand(sCommand);

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
		m_melodies->PlayMelody(Fanfarria);
	}
	else if (sCommand == "a")
	{
		m_melodies->PlayMelody(DogPower);
	}
	else if (sCommand == "h")
	{
		m_melodies->PlayMelody(R2D2);
	}
	else if (sCommand == "b")
	{
		int iSpeedMode = m_motors->GetSpeedMode();
		if (iSpeedMode == Slow)
			m_motors->SetSpeedMode(Normal);
		else if (iSpeedMode == Normal)
			m_motors->SetSpeedMode(Fast);
		else if (iSpeedMode == Fast)
			m_motors->SetSpeedMode(Turbo);
		else
			m_motors->SetSpeedMode(Slow);

		//make a sound to confirm SpeedMode
		iSpeedMode = m_motors->GetSpeedMode();
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
		m_motors->ProcessMotors(sCommand);
	}

	//set m_sLastCmd -> mainly for debug
	m_sLastCmd = "Cmd: " + sCommand;
}

#pragma endregion