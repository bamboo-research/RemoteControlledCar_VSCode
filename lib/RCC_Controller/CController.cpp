/*
Name:		CController.c
Created:	09/04/2016 12:15:51
Author:		Haiqiang Xu
Version:	1.0
*/

#include "CController.h"

#pragma region Public methods

void CController::setup()
{
	m_bluetooth->Begin(9600);
	m_iCurrentSpeed = 0;
	m_iCurrentMovement = 0;
	pinMode(iInButtonX, INPUT_PULLUP);
	pinMode(iInButtonA, INPUT_PULLUP);
	pinMode(iInButtonB, INPUT_PULLUP);
	pinMode(iOutLed, OUTPUT);			//activates Led output when a button press is detected
}

void CController::loop()
{
	m_sButtons = "";

	//read from buttons and send through Bluetooth
	if (digitalRead(iInButtonX) == LOW)
		m_sButtons += "x";
	if (digitalRead(iInButtonA) == LOW)
		m_sButtons += "a";
	if (digitalRead(iInButtonB) == LOW)
		m_sButtons += "b";
	if (m_joystick->ReadButton() == LOW)
		m_sButtons += "j";
	if (m_sButtons.length() > 0)
	{
		m_bluetooth->Send(" ");		//WORKAROUND: send dummy value to ¿wake up? bluetooth
		m_bluetooth->SendCommand(m_sButtons);
		digitalWrite(iOutLed, HIGH);
		while ( digitalRead(iInButtonX) == LOW ||
				digitalRead(iInButtonA) == LOW ||
				digitalRead(iInButtonB) == LOW ||
				m_joystick->ReadButton() == LOW )	//wait while buttons are pressed instead of setting a fixed delay
		{
			delay(30);
		}
	}
	else
	{
		digitalWrite(iOutLed, LOW);
	}

	//read from joystick and send through Bluetooth
	m_iX = m_joystick->ReadAxisX();
	m_iY = m_joystick->ReadAxisY();
	m_motors->ProcessMotors((byte)m_iX, (byte)m_iY);
	if (abs(m_motors->GetCurrentSpeed() - m_iCurrentSpeed) > 3 ||
		m_motors->GetCurrentMovement() != m_iCurrentMovement)
	{
		m_iCurrentSpeed = m_motors->GetCurrentSpeed();
		m_iCurrentMovement = m_motors->GetCurrentMovement();

		m_bluetooth->Send(" ");		//WORKAROUND: send dummy value to ¿wake up? bluetooth
		m_bluetooth->SendCommand(m_iX, m_iY);
		Common.Sleep();				//sleep between transmissions
	}
}

#pragma endregion

#pragma region Private methods

#pragma endregion