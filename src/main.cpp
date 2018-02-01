#include "main.h"
#include "CAble.h"

CAble* m_car;

void setup() {
	process();
    m_car = new CAble();
    m_car->setup();
}

void loop() {
    // put your main code here, to run repeatedly:
    m_car->loop();
}
