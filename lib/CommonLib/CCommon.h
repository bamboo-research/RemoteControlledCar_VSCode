#include <arduino.h>

class CCommon
{
public:
    String ReadKeyboard()
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
        
// private:
//     // Disable creating instances of this object
//     CCommon() { }
}

extern CCommon Common;