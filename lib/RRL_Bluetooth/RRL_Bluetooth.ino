#include "CBluetooth.h"

#define PIN_RX 2
#define PIN_TX 3

CBluetooth bluetooth(PIN_RX, PIN_TX, HC_06);

void setup()
{
	Serial.begin(9600);
	Serial.println("Debugging Bluetooth module");
}

void loop()
{
    //TODO: create new CBluetooth unit testing class
}