#include "CTestController.h"

#pragma region Public methods

void CTestController::setup()
{
    m_iPrevX = m_iPrevY = m_iPrevButton = 0;
    m_iCurrentSpeed = 0;
	m_iCurrentMovement = 0;

    //setup the 3 buttons of CController and embedded led to monitor all the buttons of the CController (including the Joystick one)
    pinMode(iInButtonX, INPUT_PULLUP);
    pinMode(iInButtonA, INPUT_PULLUP);
    pinMode(iInButtonB, INPUT_PULLUP);
    pinMode(iOutLed, OUTPUT);
}

void CTestController::loop()
{
    //TODO: Test Bluetooth, right now can'tsend AT commands, improve it 
    m_sMsgToShow = "";
	m_sBtMsg = Common.ReadKeyboard();       //read keyboard from serial terminal
	if (m_sBtMsg.length() > 0)
    {
	    m_bluetooth->Send(m_sBtMsg);
	    Serial.println("BT snd -> " + m_sBtMsg);

		m_sBtMsg = m_bluetooth->Receive();
		Serial.println("BT rcv -> " + m_sBtMsg);
    }

    //Test Joystick and Motors
    m_iX = m_joystick->ReadAxisX();
	m_iY = m_joystick->ReadAxisY();
	m_iButton = m_joystick->ReadButton();
    if (abs(m_iX - m_iPrevX) > 3 || abs(m_iY - m_iPrevY) > 3 || m_iButton != m_iPrevButton) //only show when changes in axes is detected
    {
        //update previous values
        m_iPrevX = m_iX;
        m_iPrevY = m_iY;
        m_iPrevButton = m_iButton;

        //show values in Serial Monitor
        m_sMsgToShow = "Joy-> X: " + String(m_iX) + ", Y: " + String(m_iY) + " | ";
        if (m_iButton == HIGH)
            m_sMsgToShow += "Btn: HIGH";
        else
            m_sMsgToShow += "Btn: LOW";

        //calculate if send message via BT to move motors
        m_motors->ProcessMotors((byte)m_iX, (byte)m_iY);
		if (abs(m_motors->GetCurrentSpeed() - m_iCurrentSpeed) > 3 ||
			    m_motors->GetCurrentMovement() != m_iCurrentMovement)
		{
			m_iCurrentSpeed    = m_motors->GetCurrentSpeed();
			m_iCurrentMovement = m_motors->GetCurrentMovement();

			m_bluetooth->Send(" ");		//WORKAROUND: send dummy value to ¿wake up? bluetooth
			m_bluetooth->SendCommand(m_iX, m_iY);
            m_sMsgToShow += " | BT -> send cmd [X, Y]";
		}
        Serial.println(m_sMsgToShow);
    }

    //Test 3 buttons
    if (digitalRead(iInButtonA) == LOW || digitalRead(iInButtonB) == LOW || digitalRead(iInButtonX) == LOW)
        digitalWrite(iOutLed, HIGH);
    else
        digitalWrite(iOutLed, LOW);

    //delay is to try reduce power. TODO: check http://www.gammon.com.au/power to save real power because seems delay don't save
    delay(50);
}

#pragma endregion

// Private methods
