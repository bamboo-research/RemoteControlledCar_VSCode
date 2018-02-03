#include "CTestCar.h"

#pragma region Public methods

void CTestCar::setup()
{
    m_bluetooth->Begin(9600);
	pinMode(iOutLed1, OUTPUT);
}

void CTestCar::loop()
{
    //read from Bluetooth module and check it has minimum length
	m_sReadValue = m_bluetooth->Receive();
    if (m_sReadValue.length() <= 2)
	{
		return;
	}
    Serial.println("BT->" + m_sReadValue);

    //process received command
	for (int i = 0; i < m_sReadValue.length(); i++)
	{
		m_char = m_sReadValue[i];
		m_sCmd += m_char;				//concatenate chars until '#' end command is detected
		if (m_char == '#')
		{
			if (m_bluetooth->CommandType(m_sCmd) == ArrayBytes)
			{
				//process joystick values and move motors
                m_intValues = m_bluetooth->ProcessArrayBytesCommand(m_sCmd);
                m_motors->ProcessMotors((byte)m_intValues[0], (byte)m_intValues[1]);

                //NOTE: by printing the pointer to array values, seems that affects these values
                //NOTE2: in fact, printing anything before calling ProcessMotors is provoking VERY strange behaviors in the variables
                //Serial.println("ArrayBytes command: " + String(m_intValues[0]) + "," + String(m_intValues[1]));
                //Serial.println("Joystick command: " + m_sCmd);
                Serial.println("Motor movement: " + m_motors->GetCurrMovString());
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

// Private methods
void CTestCar::ProcessButtons(String sCommand)
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

	Serial.println("Button command: " + sCommand);
}