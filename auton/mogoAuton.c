int LEFT = 1;
int RIGHT = -1;

bool stagoAlign20(int side) {
	bool result;
	if (side == LEFT) {
		result = (SensorValue[LUltrasonic] > 0 && SensorValue[LUltrasonic] < 50);
	} else if (side == RIGHT) {
		result = (SensorValue[RUltrasonic] > 0 && SensorValue[RUltrasonic] < 50);
	}
	return result;
}

void mogoAuton(int direction) {
  zero_gyro();
	mogoAndCones(true);
	writeDebugStreamLine("The gyro value right now is %d", SensorValue[Gyro]);
	stopTask(forwardAutonHelper);
	stopTask(subsystemControl);
	stopTask(autostack_control);
	//bl_drive_rotate(SensorValue[Gyro] * 0.8, -40, 1000);
	int error = -SensorValue[Gyro];
	if (error > 150) {
		bl_drive_rotate(450 - (error - 150), 127 * direction, 3000);
	}
	error = abs(SensorValue[Gyro]);
	//drive back, rotate	stopTask(nb_vbar_PID_task);s
	bl_drive((1285/2) / cosDegrees(error/10.0), -127, 3000, false); // tune this distance
	abortAutostack();
	nb_lift_PID(900, 127, 125000);
	bl_drive((1285/2) / cosDegrees(error/10.0), -127, 3000);
	//writeDebugStreamLine("turn target is %d", 450 - error);
	bl_drive_rotate(450 - error, -127 * direction, 3000);

	// align the robot with the 20pt zone using the stago
	b_drive(-60, -60); // tune speed
	waitUntil(stagoAlign20(1));

	// IF ULTRASONIC DOESN'T WORK THEN USE ENCODERS
	// bl_drive(1000, 4000, -80); // tune distance

	stopTask(nb_vbar_PID_task);
	bl_drive_rotate(900, -127 * direction, 5000); // tune speed/angle
	scoreOn20();
}
