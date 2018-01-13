#include "CMotors.h"
#include "CCommon.h"

#define PIN_LEFT1 12
#define PIN_LEFT2 13
#define PIN_RIGHT1 10
#define PIN_RIGHT2 11
#define PIN_ENA 5
#define PIN_ENB 6
#define SPEED   51

CMotors motors(PIN_LEFT1, PIN_LEFT2, PIN_RIGHT1, PIN_RIGHT2, PIN_ENA, PIN_ENB;
int m_iSpeed;

void setup()
{
	m_iSpeed = SPEED;
	motors.SetSpeedMode(Slow);

	Serial.begin(9600);
	Serial.println("Debugging Motors module");
}

void loop()
{
	String sCommand;

	//read from keyboard
	sCommand = CCommon.ReadKeyboard();

	//execute received command
	if (sCommand.length() > 0)
	{
		motors.ProcessMotors(127, m_iSpeed);
		if (m_iSpeed > 255)
			m_iSpeed = 12;
		else
			m_iSpeed += 12;
	}
}
