#include "main.h"
#include "CTestCar.h"

CTestCar* m_testCar;

void setup() {
	process();
    m_testCar = new CTestCar();
    m_testCar->setup();
}

void loop() {
    // put your main code here, to run repeatedly:
    m_testCar->loop();
}
