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
        m_joystick = new CJoystick(iInAxisX, iInAxisY, iInButton);
        m_motors = new CMotors();
    };

    // Public methods
    void setup();
    void loop();
    
private:
    // Fields
    CBluetooth* m_bluetooth;
    CJoystick* m_joystick;
    CMotors* m_motors;
    String m_sBtMsg;        //bluetooth messages
    int m_iX, m_iY;
    int m_iPrevX, m_iPrevY; //axes
    int m_iButton;
    int m_iPrevButton;      //joystick button
    int m_iCurrentSpeed, m_iCurrentMovement;    //motors
    String m_sMsgToShow;

    // Private methods
};