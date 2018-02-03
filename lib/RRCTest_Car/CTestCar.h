#include "CAble.h"

class CTestCar
{
public:
    // Constructors
    CTestCar()
    {
        //init HardwareSerial to monitor and debug Arduino RX / TX and its activity
        Serial.begin(9600);
        Serial.println("Debugging Car Able");

        m_bluetooth = new CBluetooth(iOutRx, iOutTx, HC_06);	//RX, TX, EBluetoothAdapter
		m_motors = new CMotors(iOutLeft1, iOutLeft2, iOutRight1, iOutRight2, iOutEna, iOutEnb); //NOTE: pinENA and pinENB must be PWM pins!!!!!
		m_melodies = new CMelodies(iOutSpeaker);
    };

    // Public methods
    void setup();
    void loop();
    
private:
    // Fields
    CBluetooth* m_bluetooth;
	CMotors* m_motors;
	CMelodies* m_melodies;
	String m_sReadValue;
	int* m_intValues;
    char m_char;
	String m_sCmd;

    // Private methods
    void ProcessButtons(String sCommand);
};