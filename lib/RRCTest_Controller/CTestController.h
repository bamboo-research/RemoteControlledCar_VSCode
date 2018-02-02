#include "CController.h"

class CTestController
{
public:
    // Constructors
    CTestController()
    {
        //init HardwareSerial to monitor and debug Arduino RX / TX and its activity
        Serial.begin(9600);
        Serial.println("Debugging CController");

        m_bluetooth = new CBluetooth(iOutRx, iOutTx, HC_05);
        joystick = new CJoystick(iInAxisX, iInAxisY, iInButton);
    };

    // Public methods
    void setup();
    void loop();
    
private:
    // Fields
    CBluetooth* m_bluetooth;
    CJoystick* joystick;
    String m_sBtMsg;
    int m_iX, m_iY;
    int m_iButton;
    String m_sMsgToShow;

    // Private methods
};