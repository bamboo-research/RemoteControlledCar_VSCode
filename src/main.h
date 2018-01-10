#include <Arduino.h>

class main {
    public:
        void setup();
		void loop();
    private:
        void ProcessJoystick(String sCommand);
        void ProcessButtons(String sCommand);
};