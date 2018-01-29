#include "main.h"
#include "CController.h"

CController *m_controller;

void setup() {
	process();
    m_controller = new CController();
    m_controller->setup();
}

void loop() {
    // put your main code here, to run repeatedly:
    m_controller->loop();
}
