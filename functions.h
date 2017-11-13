/*
calibrates gyroscope. run in pre-auton.
*/
void calibrate() {
 //Completely clear out any previous sensor readings by setting the port to "sensorNone"
 SensorType[in5] = sensorNone;
 wait1Msec(1000);
 //Reconfigure Analog Port 8 as a Gyro sensor and allow time for ROBOTC to calibrate it
 SensorType[in5] = sensorGyro;
 wait1Msec(2000);
}

/*
moves robot "target" encoder units forward with motor power "power".
If the target is not reached in "timeout" ms, stop.
Needs to be braked with autonBrake().
*/
void autonDrive(int target, int timeout, int power) {
	int tolerance = 50;
	//SensorValue[LEncoder] = 0;
	SensorValue[REncoder] = 0;

	int timer = 0;
	while (abs(SensorValue[REncoder]) < target && timer < timeout) {
		moveDrive(power, power);
		wait1Msec(20);
		timer += 20;
	}

	moveDrive(0, 0);
}

/*
brakes after moving. Use if robot needs to stop
direction: direction the robot is moving in
*/
#define FORWARD = 1;
#define BACKWARDS = -1;
void autonBrake(int direction) {
	moveDrive(-direction * 30, -direction * 30);
	wait1Msec(50);
	moveDrive(0, 0);
}


// higher sensor value := open
// true; open the cone, false; close the cone
bool OPEN = true;
bool CLOSED = false;

void autonConeIntake(bool position) {
	int time = 0;
	if (position) {
		//while (SensorValue[ConePot] < 3000 && time < 1200) {
		//	moveConeIntake(-127);
		//	wait1Msec(20);

		//	if (SensorValue[ConePot] < 500) break;
		//}
		moveConeIntake(-127);
		wait1Msec(300);
		moveConeIntake(0);
	} else {
		//while (SensorValue[ConePot] > 2000 && time < 1200) {
		//	moveConeIntake(127);
		//	wait1Msec(20);

		//	if (SensorValue[ConePot] < 500) break;
		//}
		moveConeIntake(127);
		wait1Msec(300);
		moveConeIntake(0);
	}
	moveConeIntake(0);
}

/*
uses gyroscope to rotate
*/
void autonRotate(int target, int timeout, int power, int direction) {
	int DECEL_ANGLE = 30;
	int BRAKE_SPEED = 30;
	int tolerance = 20;
	float k = 0.4;
	int time = 0;

	SensorValue[Gyro] = 0;
	while (target - abs(SensorValue[Gyro]) > tolerance) {
		moveDrive(direction * power, -direction * power);
	}

	moveDrive(-direction * BRAKE_SPEED, direction * BRAKE_SPEED);
	wait1Msec(100);
	moveDrive(0, 0);
}
