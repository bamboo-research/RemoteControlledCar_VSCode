#include "CJoystick.h"

// Public methods
int CJoystick::ReadAxisX()
{
	return CalculateValueDirection(AxisX);
}

int CJoystick::ReadAxisY()
{
	return CalculateValueDirection(AxisY);
}

int CJoystick::ReadButton()
{
	return digitalRead(m_iPinButton);
}

// Private methods
int CJoystick::CalculateValueDirection(EAxis axis)
{
	int iPinNumber, iValue;

	// Analog inputs	   range: 0 - 1023 (0V - 5V)
	// Analog outpus (PWM) range: 0 - 255  (0V - 5V)
	// calculate axis value
	iPinNumber = (axis == AxisX) ? m_iPinAxisX : m_iPinAxisY;
	iValue = map(analogRead(iPinNumber), 0, 1023, 0, 255);

	// calculate Direction
	if (iValue >= 0 && iValue < 30)
	{
		if (axis == AxisX)
			m_DirectionX = Left;
		else
			m_DirectionY = Up;
	}
	else if (iValue > 225 && iValue <= 255)
	{
		if (axis == AxisX)
			m_DirectionX = Right;
		else
			m_DirectionY = Down;
	}
	else
	{
		if (axis == AxisX)
			m_DirectionX = None;
		else
			m_DirectionY = None;
	}

	return iValue;
}
