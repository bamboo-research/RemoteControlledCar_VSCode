## TODO List

### Bluetooth:
	x Protection against non requested pairment
	x Remove delays and unnecessary DUMMY messages
	- Generic command processor
	
### Joystick:
	x Check button output
	- Allow diferent quadrants so (X,Y) should be processed respect different (0, 0)

### Motors:
	- Make move simultaneously both axes but at different speed to make the car change direction instead of
	  only moving one axis to change direction.

### RRC_Controller:
	x Extra buttons to activate features
	x Avoid unnecessary comm transmission
		x Calculate motor direction on Controller part and not in Car part
	- Change speed/movement in progress when SpeedMode (button) is changed

### RRCar:
	- Display or LED blinking for error show
	- ¿Laser beam?
	- Aerodynamics (wings):
		- Frontal
		- Rear
	x Motors:
		x Axis left - right
		x Limit to 6V per motor? -> limit by SW

### Common Software:
	x Check power consumption by replacing Delay() with LowPower library functions to save power
	- Implement ProtoThreading to avoid for example in RRCar, not allowing other operations when playing CMelodies
	  or not allowing change range speed through button when car is in move