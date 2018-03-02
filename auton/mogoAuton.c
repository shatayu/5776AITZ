task autonManager2() {
	waitUntil(autostack_state.stacked == true);
	nb_lift_PID(2000, 127, 125000);
}

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
	mogoAndCones();
	startTask(autonManager2);
	// drive back, rotate
	bl_drive(1610, 3000, -127); // tune this distance
	bl_drive_rotate(450, 3000, -127 * direction);
	b_vbar(20);

	// align the robot with the 20pt zone using the stago

	b_drive(-80, -80); // tune speed
	waitUntil(stagoAlign20(1));
	// IF ULTRASONIC DOESN'T WORK THEN USE ENCODERS
	// bl_drive(1000, 4000, -80); // tune distance

	stopTask(nb_vbar_PID_task);
	bl_drive_rotate(920, 5000, -80 * 1); // tune speed/angle
	stopTask(autonManager);
	scoreOn20();
}
