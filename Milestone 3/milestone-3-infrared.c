#pragma config(Sensor, dgtl1,  button1,        sensorTouch)
#pragma config(Sensor, dgtl2,  button2,        sensorTouch)
#pragma config(Motor,  port9,           motorsRight,   tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port10,          motorsLeft,    tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Sensor, in5,    IRsensor1,      sensorReflection)
#pragma config(Sensor, dgtl6,  StateLED,       sensorDigitalOut)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
//tmotorVex393_MC29
//tmotorVex393_HBridge

const int SPEED = 50;

const int SPEEDL = SPEED;
const int SPEEDR = SPEED;

const int beacon_threshold = 15;


int monitorLight()
{
	static int minLevelIR1 = 4096;	// Minimum light level seen by IR sensor 1
	static int maxLevelIR1 = 0;			// Maximum light level seen by IR sensor 1
	static int diffLevelIR1 = 0;		// Delta between maximum and minimum seen in last 0.1 seconds

	int lightLevel1 = SensorValue[IRsensor1];

	// Check if 100 msecs have elapsed.
	if ( time1[T1] > 100 )  {

		// 100 msecs have elapsed.  Compute delta of light level.
		diffLevelIR1 = maxLevelIR1 - minLevelIR1;

		// Reset calculation for next 100 msecs.
		maxLevelIR1 = 0;
		minLevelIR1 = 4096;
		clearTimer(T1);

	} else {

		// Check for new minimum/maximum light levels.
		if ( lightLevel1 < minLevelIR1 ) {
			minLevelIR1 = lightLevel1;
		} else if ( lightLevel1 > maxLevelIR1 ) {
			maxLevelIR1 = lightLevel1;
		}
	}

	return(diffLevelIR1);
}


task main()
{
	motor[motorsLeft] = SPEEDL;
	motor[motorsRight] = -SPEEDR;

	//motor[motorsLeft] = 0;
	//motor[motorsRight] = 0;
	//*
	int max_diff = 0;
	int diff;
	while(1){
		diff = monitorLight();
		if (diff - max_diff <= -10 && diff > -4096){
			motor[motorsLeft] = 0;
			motor[motorsRight] = 0;
			break;
		}
		if (diff > max_diff && diff < 100) {
			max_diff = diff;
		}
	}//*/

	//while(1)monitorLight();

	motor[motorsLeft] = 0;
	motor[motorsRight] = 0;

	while(monitorLight());
}
