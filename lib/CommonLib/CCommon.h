#include <arduino.h>
#include <LowPower.h>

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

    static void PowerDown()
    {
        // Allow wake up interrupt when pin 2 detects change voltage.
        // Interrupt 0 corresponds I/O pin 2 and Interrupt 1 corresponds I/O pin 3 on Uno/Nano.
        attachInterrupt(0, WakeUp, CHANGE);
        
        // Enter power down state with ADC and BOD module disabled. Wake up when interrupt detected
        LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); 
    };

    static void Sleep()
    {
        LowPower.powerDown(SLEEP_120MS, ADC_OFF, BOD_OFF);
    };
private:
    // Disable creating instances of this object
    CCommon() { };

   	static void WakeUp()
    {
        // Just a handler for the pin interrupt.
        // Disable external interrupt on wake up pin.
        detachInterrupt(0); 
    };
};

//instance for use in external libraries to access directly to static methods
extern CCommon Common;