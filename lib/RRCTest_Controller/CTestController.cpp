#include "CTestController.h"

#pragma region Public methods

void CTestController::setup()
{
    m_sMsgToShow = "";

    //setup the 3 buttons of CController and embedded led to monitor all the buttons of the CController (including the Joystick one)
    pinMode(iInButtonX, INPUT_PULLUP);
    pinMode(iInButtonA, INPUT_PULLUP);
    pinMode(iInButtonB, INPUT_PULLUP);
    pinMode(iOutLed, OUTPUT);
}

void CTestController::loop()
{
    //Test Bluetooth
    m_sMsgToShow = "";
    m_sBtMsg = m_bluetooth->Receive();
	if (m_sBtMsg.length() > 0)
        m_sMsgToShow = "BT rcv-> " + m_sBtMsg;
	m_sBtMsg = Common.ReadKeyboard();
	if (m_sBtMsg.length() > 0)
    {
	    m_bluetooth->Send(m_sBtMsg);
		m_sMsgToShow += "BT snd-> " + m_sBtMsg;
    }
    Serial.println(m_sMsgToShow);

    //Test Joystick. TODO: only show when change in axes is detected
    m_sMsgToShow = "";
    m_iX = joystick->ReadAxisX();
	m_iY = joystick->ReadAxisY();
	m_iButton = joystick->ReadButton();
	m_sMsgToShow = "Joy-> X: " + String(m_iX) + ", Y: " + String(m_iY);
	if (m_iButton == HIGH)
		m_sMsgToShow += "Button: HIGH";
	else
		m_sMsgToShow += "Button: LOW";
    Serial.println(m_sMsgToShow);

	delay(150);

    //Test Motors   //TODO:decide if can be tested on CController
}

#pragma endregion

// Private methods
