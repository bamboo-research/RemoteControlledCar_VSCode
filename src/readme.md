## TODO List

### Bluetooth:
- [x] Protection against non requested pairment
- [x] Remove delays and unnecessary DUMMY messages
	
### Joystick:
- [x] Check button output
- [ ] Allow diferent quadrants so (X,Y) should be processed respect different (0, 0)

### Motors:
- [ ] Make move simultaneously both axes but at different speed to make the car change direction instead of only moving one axis to change direction.

### RRC_Controller:
- [x] Extra buttons to activate features
- [x] Avoid unnecessary comm transmission
	- [x] Calculate motor direction on Controller part and not in Car part
- [ ] Change speed/movement in progress when SpeedMode (button) is changed

### RRC_Car:
- [ ] Display or LED blinking for error show
- [ ] ¿Laser beam?
- [ ] Aerodynamics (wings):
	- [ ] Frontal
	- [ ] Rear
- [x] Motors:
	- [x] Axis left - right
	- [x] Limit to 6V per motor to avoid over-voltage -> limit by SW

### Common Software:
- [x] Check power consumption by replacing Delay() with LowPower library functions to save power
- [x] [Discarded] Implement ProtoThreading to avoid for example in RRCar, not allowing other operations when playing CMelodies or not allowing change range speed through button when car is in move -> NOT viable due to limitation in ArduinoThread as it only changes between threads/methods when it finishes, doesn't solve the problem when you have a Delay()/Sleep() in the current method and you don't want to block other processes when waiting for the current one.
- [x] Add a timeout after X minutes in Idle mode -> add input into some interrupt to wake it up, if not possible then use Arduino's embbeded Reset button
- [ ] Implement an alternative to process other processes while the current execution is in Delay()/Sleep()