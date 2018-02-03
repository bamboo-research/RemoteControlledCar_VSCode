#include "main.h"
#include "CTestController.h"

CTestController* m_testController;

void setup() {
	process();
    m_testController = new CTestController();
    m_testController->setup();
}

void loop() {
    // put your main code here, to run repeatedly:
    m_testController->loop();
}
