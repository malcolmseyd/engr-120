#pragma config(Sensor, dgtl1,  button1,        sensorTouch)
#pragma config(Sensor, dgtl3,  sonar1,         sensorSONAR_mm)
#pragma config(Motor,  port9,           motorsRight,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          motorsLeft,    tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Sensor, dgtl6,  StateLED,       sensorDigitalOut)
#pragma config(Sensor, in1,    motor_angle,         sensorPotentiometer)
#pragma config(Motor,  port1,           motor1,        tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//tmotorVex393_MC29
//tmotorVex393_HBridge

// Claw stuff
static int CLOSED_POS = 1830;
static int OPEN_POS   = 1520;
static int MAX   = 25;
static int ACC   = 1;

// Drive train stuff
const int SPEEDL = 15;
const int SPEEDR = 15;

const int PLACEMENT_DIST = 70;
const int PLACEMENT_ACC = 5;

const bool ENABLED = true;


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


void blinkLED()
{
	const int BLINK_HZ = 2;

	if ( time1[T1] > 1000/2/BLINK_HZ )  {
		if (SensorValue[StateLED]){
			SensorValue[StateLED] = 0;
		}
		else {
			SensorValue[StateLED] = 1;
		}

		clearTimer(T1);
	}
}


task main()
{

	while(1){
		// Too far
		if (SensorValue(sonar1) > PLACEMENT_DIST+PLACEMENT_ACC){
			SensorValue[StateLED] = 0;
		// Just right
		} else if (SensorValue(sonar1) < PLACEMENT_DIST+PLACEMENT_ACC && SensorValue(sonar1) > PLACEMENT_DIST-PLACEMENT_ACC){
			SensorValue[StateLED] = 1;
			//while(!set_motor(OPEN_POS));
		// Too close
		} else if (SensorValue(sonar1) < PLACEMENT_DIST-20) {
			blinkLED();
		}
	}

/*
	motor[motorsLeft] = 0;
	motor[motorsRight] = 0;
	while(ENABLED){

		if(SensorValue(button1)){
			motor[motorsLeft] = SPEEDL;
			motor[motorsRight] = SPEEDR;

			// Keep going until we're close enough.
			while(SensorValue(sonar1) > SONAR_CLOSE);

			motor[motorsLeft] = 0;
			motor[motorsRight] = 0;
		}
	/*
		switch(wheel_state){
			case STOPPED:
				motor[motorsLeft] = 0;
				motor[motorsRight] = 0;

				break;

			case FORWARDS:
				motor[motorsLeft] = SPEEDL;
				motor[motorsRight] = SPEEDR;

				wheel_state = STOPPED;
				break;
		}
	}*/
	// Keep sensor values open
	while(1);
}
