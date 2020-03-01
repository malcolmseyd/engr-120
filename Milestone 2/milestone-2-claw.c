#pragma config(Sensor, in1,    motor_angle,         sensorPotentiometer)
#pragma config(Sensor, dgtl1,  button1,        sensorTouch)
#pragma config(Sensor, dgtl2,  button2,        sensorTouch)
#pragma config(Motor,  port1,           motor1,        tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int CLOSED_POS = 1830;
int OPEN_POS   = 1520;

const int SPEED = 25;

// Speed
//static int MAX  = 127;
//static int ACC  = 5;

// Accuracy
static int MAX   = 25;
static int ACC   = 1;


bool button1_pushed = false;
bool button1_released_yet = true;

bool button2_pushed = false;
bool button2_released_yet = true;


// This function implements a lock when the button is pressed.
// button#_enabled cannot be 'true' until the sensor is realeased again.
void updateSensors() {
	if(SensorValue(button1) && !button1_pushed && button1_released_yet) {
		button1_pushed = true;
		button1_released_yet = false;
	} else if (SensorValue(button1) == 0) {
		button1_pushed = false;
		button1_released_yet = true;
	}

	if(SensorValue(button2) && !button2_pushed && button2_released_yet) {
		button2_pushed = true;
		button2_released_yet = false;
	} else if (SensorValue(button2) == 0) {
		button2_pushed = false;
		button2_released_yet = true;
	}
}

/**********************************************************
** bool set_motor( int target )
** Runs motor to try and hit target angle
** Inputs:
**   target  - target reading from potentiometer.
** Output:
**    true   - motor has reached desired position
**    false  - motor has not hit target position
**
** Sets motor output.
** Reads motor from port motor_angle
**********************************************************/
bool set_motor( int target )
{
	int position = SensorValue[motor_angle];
	//writeDebugStream("%d\n", SensorValue[motor_angle]);

	// How far off the mark are we?
	int delta = target - position;

	// Our potentiometer is on backwards lol
	//delta *= -1;

	// If the motor is over the speed limit, scale it down.
	if ( delta > MAX ) {
	  delta = MAX;
  }
  else if ( delta < -MAX ) {
		delta = -MAX;
  }

  // Set the motor speed
  if(-ACC <= delta && delta <= ACC){
  	// If we're within the desired accuracy, stop the motor
  	motor[motor1] = 0;
  	return(true);

  } else {
    // Otherwise, set the motor speed to the distance away
    // Scale our speed down as we get closer
  	motor[motor1] = delta;
  	return(false);
  }


	// Return true, indicating we are at target position.
	return(true);

}

task main()
{
	motor[motor1] = 0;

	//* Preset Mode
	while(1) {
		updateSensors();
		wait1Msec(25)

		if (button1_pushed){
			button1_pushed = false;
			while(!set_motor(OPEN_POS));
		} else if (button2_pushed) {
			button2_pushed = false;
			while(!set_motor(CLOSED_POS));
		}
	}//*/

	//* Manual mode
	while (1) {
		if (SensorValue[button1]){
			motor[motor1] = SPEED;
		} else if (SensorValue[button2]) {
			motor[motor1] = -SPEED;
		} else {
			motor[motor1] = 0;
		}
	}//*/
}