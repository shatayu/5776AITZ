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
	SensorValue[LEncoder] = 0;
	SensorValue[REncoder] = 0;

	int timer = 0;
	while (abs(SensorValue[LEncoder] + SensorValue[REncoder])/2 < target && timer < timeout) {
		moveDrive(power, power);
		wait1Msec(20);
		timer += 20;
	}

	moveDrive(0, 0);
}

/*
brakes after moving. Use if robot needs to stop
*/
void autonBrake(int direction) {
	moveDrive(-direction * 30, -direction * 30);
	wait1Msec(30);
	moveDrive(0, 0);
}


// higher sensor value := open
bool coneIntakeState; // true; open the cone, false; close the cone
bool OPEN = true;
bool CLOSED = false;

task autonConeIntake() {
	clawStall(false);
	if (coneIntakeState) {
		moveConeIntake(-50);
	} else {
		moveConeIntake(50);
	}
	wait1Msec(500); // time for claw to move
	moveConeIntake(0);


	//int openValue;
	//int closedValue;
	//int timeout = 500; // amount of time claw is allowed to reach its state
	//int power = 127;

	//int timer = 0;
	//if (coneIntakeState) { 	// open claw
	//	while (SensorValue[ConePot] < openValue && timer < timeout) {
	//		moveConeIntake(-power);
	//		wait1Msec(20);
	//		timer += 20;
	//	}
	//} else if (SensorValue[ConePot] > closedValue) { // close claw
	//	while (SensorValue[ConePot] > closedValue && timer < timeout) {
	//		moveConeIntake(power);
	//		wait1Msec(20);
	//		timer += 20;
	//	}
	//}

	//moveConeIntake(0);
}

/*
uses gyroscope to rotate
*/
void autonRotate(int target, int timeout, int power) {
	int DECEL_ANGLE = 30;
	int BRAKE_SPEED = 30;
	float k = 0.4;
	int time = 0;

	SensorValue[Gyro] = 0;
	while (abs(SensorValue[Gyro]) < (target - DECEL_ANGLE) * 10 && time < timeout) {
		moveDrive(power, -power);
		wait1Msec(20);
		time += 20;
	}

	while (abs(SensorValue[Gyro]) < target * 10 && time < timeout) {
		moveDrive(k * power, -k * power);
		wait1Msec(20);
		time += 20;
	}

	moveDrive(-sgn(power) * BRAKE_SPEED, sgn(power) * BRAKE_SPEED);
	wait1Msec(100);
	moveDrive(0, 0);
}
