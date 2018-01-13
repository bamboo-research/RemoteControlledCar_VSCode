#include "CMelodies.h"
#include "CCommon.h"

#define PIN_OUT 13
#define DELAY   100

CMelodies melodies(PIN_OUT);

void setup()
{
	Serial.begin(9600);
	Serial.println("Debugging Melodies module");
}

void loop()
{
	String sValue = CCommon.ReadKeyboard();
	if (sValue.length() > 0)
	{
		if (sValue == "0")
			melodies.PlayMelody(Fanfarria);
		else if (sValue == "1")
			melodies.PlayMelody(DogPower);
		else if (sValue == "2")
			melodies.PlayMelody(ThirdPhase);
		else if (sValue == "3")
			melodies.PlayMelody(R2D2);
		else if (sValue == "4")
			melodies.PlayMelody(Ohhh);
		else if (sValue == "5")
			melodies.PlayMelody(Uhoh);

		Serial.println(sValue);
		delay(DELAY);
	}
}
