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
        // Allow wake up interrupt when input pin detects LOW signal. Seems that FALLING/RISING/CHANGE signals doesn't work to wake-up arduino from PowerDown
        // Interrupt 0 corresponds I/O pin 2 and Interrupt 1 corresponds I/O pin 3 on Uno/Nano.
        attachInterrupt(1, WakeUp, LOW);
        
        // Enter power down state with ADC and BOD module disabled. Wake up when interrupt detected
        LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
        //delay(75); // allows the arduino to fully wake up.
    };

    static void Sleep(period_t period)
    {
        //NOTE: Nano transmits garbage characters to PC through HardwareSerial if USART0 is OFF
        LowPower.idle(period, ADC_ON, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_ON, TWI_OFF);
    };

    static void Sleep(int iPeriod)
    {
        period_t period;
        switch (iPeriod)
        {
            case 15:
                period = SLEEP_15MS;
                break;
            case 30:
                period = SLEEP_30MS;
                break;
            case 60:
                period = SLEEP_60MS;
                break;
            case 120:
                period = SLEEP_120MS;
                break;
            case 250:
                period = SLEEP_250MS;
                break;
            case 500:
                period = SLEEP_500MS;
                break;
            case 1000:
                period = SLEEP_1S;
                break;
            case 2000:
                period = SLEEP_2S;
                break;
            case 4000:
                period = SLEEP_4S;
                break;
            case 8000:
                period = SLEEP_8S;
                break;
            default:
                period = SLEEP_250MS;   //default period
                break;
        }
        LowPower.idle(period, ADC_ON, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_ON, TWI_OFF);
    };
private:
    // Disable creating instances of this object
    CCommon() { };

   	static void WakeUp()
    {
        // Just a handler for the pin interrupt.
        // Disable external interrupt on wake up pin.
        detachInterrupt(1);
    };
};

//instance for use in external libraries to access directly to static methods
extern CCommon Common;