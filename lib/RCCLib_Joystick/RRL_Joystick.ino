#include "CJoystick.h"

#define PIN_X 0
#define PIN_Y 1
#define PIN_BUTTON 8

CJoystick joystick(PIN_X, PIN_Y, PIN_BUTTON);
int m_iX, m_iY;
int m_iButton;

void setup()
{
	Serial.begin(9600);
	Serial.println("Debugging Joystick module");
}

void loop()
{
	m_iX = joystick.ReadAxisX();
	m_iY = joystick.ReadAxisY();
	m_iButton = joystick.ReadButton();
	Serial.print("X: " + String(m_iX) + ", Y: " + String(m_iY));
	if (m_iButton == HIGH)
		Serial.println("Button: HIGH");
	else
		Serial.println("Button: LOW");

	delay(150);
}
