#include "CMarquee.h"

CMarquee m_marquee(2, 3, 4);	//

void setup()
{

}

void loop()
{
	m_marquee.Start();
	delay(1000);
	m_marquee.Stop();
}
