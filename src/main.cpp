#include "main.h"

#ifdef TEST_CAR
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
#endif

#ifdef TEST_CONTROLLER
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
#endif

#ifdef RCC_CONTROLLER
    #include "CController.h"
    CController* m_Controller;

    void setup() {
        process();
        m_Controller = new CController();
        m_Controller->setup();
    }

    void loop() {
        // put your main code here, to run repeatedly:
        m_Controller->loop();
    }
#endif

#ifdef RCC_ABLE
    #include "CAble.h"
    CAble* m_CarAble;

    void setup() {
        process();
        m_CarAble = new CAble();
        m_CarAble->setup();
    }

    void loop() {
        // put your main code here, to run repeatedly:
        m_CarAble->loop();
    }
#endif
