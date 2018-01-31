#include <arduino.h>

class CCommon
{
public:
    static String ReadKeyboard()
    {
        String stringValue = "";
        do
        {
            if (Serial.available() > 0)
            {
                stringValue += (char)Serial.read();
            }
            delay(3);	//delay to allow buffer to fill
        } while (Serial.available());

        return stringValue;
    };
private:
    // Disable creating instances of this object
    CCommon() { };
};

//instance for use in external libraries to access directly to static methods
extern CCommon Common;