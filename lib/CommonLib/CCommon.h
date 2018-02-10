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
        attachInterrupt(0, WakeUp, RISING);
        
        // Enter power down state with ADC and BOD module disabled. Wake up when interrupt detected
        LowPower.powerDown(SLEEP_8S, ADC_ON, BOD_OFF); 
    };

    static void Sleep(period_t period)
    {
        //Nano transmit garbage characters to PC through HardwareSerial if USART0 is OFF
        LowPower.idle(period, ADC_ON, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_ON, TWI_OFF);
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