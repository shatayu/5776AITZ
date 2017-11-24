void moveDrive(int left, int right) {
	motor[LDrive] = left;
	motor[RDrive] = right;
}

void autonDrive(int target, int timeout, int power) {
	SensorValue[REncoder] = 0;

	int timer = 0;
	while (abs(SensorValue[REncoder]) < target && timer < timeout) {
		moveDrive(power, power);
		wait1Msec(20);
		timer += 20;
	}

	moveDrive(0, 0);
}

void autonBrake(int direction) {
	moveDrive(-direction * 30, -direction * 30);
	wait1Msec(50);
	moveDrive(0, 0);
}

void calibrate() {
 //Completely clear out any previous sensor readings by setting the port to "sensorNone"
 SensorType[in5] = sensorNone;
 wait1Msec(1000);
 //Reconfigure Analog Port 5 as a Gyro sensor and allow time for ROBOTC to calibrate it
 SensorType[in5] = sensorGyro;
 wait1Msec(2000);
}

void autonRotate(int target, int timeout, int power, int direction) {
	int timer = 0;
	int BRAKE_SPEED = 30;

	SensorValue[Gyro] = 0;

	while (target - abs(SensorValue[Gyro]) > 300 && timer < timeout) {
		moveDrive(direction * power, -direction * power);
		wait1Msec(20);
		timer += 20;
	}

	while (target - abs(SensorValue[Gyro]) > 20 && timer < timeout) {
		moveDrive(direction * power * 0.4, -direction * power * 0.4);
		wait1Msec(20);
		timer += 20;
	}

	moveDrive(-direction * BRAKE_SPEED, direction * BRAKE_SPEED);
	wait1Msec(100);
	moveDrive(0, 0);
}
