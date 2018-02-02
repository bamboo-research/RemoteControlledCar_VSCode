#include <arduino.h>

class CJoystick
{
	public:
		// Contructors
		CJoystick(int iPinAxisX, int iPinAxisY, int iPinButton)
		{
			m_iPinAxisX = iPinAxisX;
			m_iPinAxisY = iPinAxisY;
			m_iPinButton = iPinButton;

			pinMode(iPinButton, INPUT_PULLUP);
		};

		// Public methods
		int ReadAxisX();
		int ReadAxisY();
		int ReadButton();

	private:
		// Fields
		int m_iPinAxisX, m_iPinAxisY;
		int m_iPinButton;

		// Private methods
};
