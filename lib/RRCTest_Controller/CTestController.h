#include "CBluetooth.h"
#include "CJoystick.h"
#include "CMotors.h"

class CTestController
{
public:
    // Constructors
    CTestController(int iPinRx, int iPinTx, EBluetoothAdapter adapter)
    {

    };

    // Public methods
    void TestBluetooth();
    void TestJoystick();
    void TestMotors();
    
private:
    // Fields

    // Private methods
};