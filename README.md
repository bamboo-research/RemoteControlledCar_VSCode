# RemoteControlledCar build with Arduino Uno/Nano and communication via Bluetooth

Software for Arduino Uno-based remote controlled car together with a Arduino Nano-based remote controlling and intercommunication via Bluetooth modules.

### Hardware components used for Remote Controlled Car

- Arduino [Uno](https://store.arduino.cc/arduino-uno-rev3) or compatible
- Battery or powerbank [ 5V,  +1450 mAh ] to power-up Arduino and its components (bluetooth module and speaker)
- Battery or powerbank [ 12V, +4000 mAh ] to power-up motors
- Bluetooth HC-06 slave module
- L298N Driver to control motors
- Buzzer / piezo speaker
- 4 DC motors + wheels
- Optional dip switch to turn on/off the car
- Car structure, up to your imagination :-)

### Hardware components used for Remote Controller

- Arduino [Nano](https://store.arduino.cc/arduino-nano) or compatible
- Battery or powerbank [ 5V,  +1450 mAh ]
- Bluetooth HC-05 master/slave module
- Joystick analog 2-Axis with button
- Three switch [buttons](https://www.arduino.cc/en/Tutorial/Switch)
- Optional dip switch to turn on/off the controller
- Controller structure, also up to your imagination

### Software structure

The software is splitted into [Abstraction Layers](https://en.wikipedia.org/wiki/Abstraction_layer) so the responsability of each layer are very limited and will make easier the growth and maintenance of the project in a Architectural point of view. Combined with a objected-oriented language such as C++ accepted by Arduino, makes the implementation closer to this approach.

### Libraries functionalities -> TODO: move to Wiki section

#### Bluetooth library

Communicates with the bluetooth (BT) module [HC-05 or HC-06] via [SoftwareSerial](https://www.arduino.cc/en/Reference/SoftwareSerial). List of functions:
- Begin(long lBauds): starts the communication with the BT module
- SendATCommandHC05(EATCommand command, String sValue): sends AT commands to the HC-05 module. Set KEY pin to HIGH or press the physical button in the module to enter AT mode. Use together with HardwareSerial to debug the responses sent by the module.
- SendATCommandHC06(EATCommand command, String sValue): sends AT commands to the HC-06 module. Use together with HardwareSerial to debug the responses sent by the module.
- DirectReceive(): Reads from BT module without any processing.
- Receive(): Reads from BT module when message starts INI_STR_CMD or INI_BYT_CMD character and reads until it founds the END_CMD
- Send(String sMessage): Sends to the BT module without processing, onlyt adding LF or CR + LF when needed.
- SendCommand(String sMessage): Sends to the BT module with INI_STR_CMD at the start and END_CMD at the end of the message.
- SendCommand(byte byteX, byte byteY): Sends to the BT module with INI_BYT_CMD at the start and END_CMD at the end of the message.
- CommandType(String sCommand): distinguishes if the received message is with INI_STR_CMD or with INI_BYT_CMD.
- ProcessArrayBytesCommand(String sCommand): Converts the message with INI_BYT_CMD into array of bytes.
- ProcessStringCommand(String sCommand): Converts the message with INI_STR_CMD into a String.

#### Joystick library
Reads the axis values from the Joystick. List of functions:
- 

TODO: electrical schematics

TODO: photos car and controller prototypes