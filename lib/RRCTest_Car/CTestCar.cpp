#include "CTestCar.h"

#pragma region Public methods

void CTestCar::setup()
{
    m_CarAble->setup();
}

void CTestCar::loop()
{
	m_CarAble->loop();

    //read from Bluetooth module and check it has minimum length
	m_sReadValue = m_CarAble->GetReadValue();
    if (m_sReadValue.length() <= 2)
	{
		return;
	}
    Serial.println("BT->" + m_sReadValue);

    //process received command
	Serial.println(m_CarAble->GetLastCommand());
}

#pragma endregion

// Private methods
