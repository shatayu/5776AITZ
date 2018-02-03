task autonManager() {
	nb_lift(1700, 127, 5000);
	b_vbar(20);
  wait1Msec(500);
	b_mogo_intake(127);
	wait1Msec(1200);
	b_mogo_intake(20);
	b_lift(0);
}

int LEFT = 1;
int RIGHT = -1;
bool stagoAlignBack(int side) {
	if (side == LEFT) {
		return (SensorValue[LUltrasonic] > 30 && SensorValue[LUltrasonic] < 75);
	} else if (side == RIGHT) {
		return (SensorValue[RUltrasonic] > 30 && SensorValue[RUltrasonic] < 75);
	}
}

bool stagoAlign20(int side) {
	if (side == LEFT) {
		return (SensorValue[LUltrasonic] > 0 && SensorValue[LUltrasonic] < 50);
	} else if (side == RIGHT) {
		return (SensorValue[RUltrasonic] > 0 && SensorValue[RUltrasonic] < 50);
	}
}

void lineAlign(bool firstSide) {

}

// gets mogo and however any cones are programmed
void mogoAndCones() {
	b_cone_intake(-20);

	// drive up to mogo
	startTask(autonManager);
	wait1Msec(300);
	bl_drive(725, 3000, 127);
	wait1Msec(250);
	nb_mogo_intake(2400, 127, 3000);
	waitUntil(SensorValue[MogoPot] > 2400);

	// BRING CONE DOWN ON CONE
	// once the lift is at the top come down on the stack
	stopTask(nb_vbar_PID_task);
	startTask(nb_lift_velocity);
	b_lift(-127);
	wait1Msec(200);
	waitUntil(lift.velocity > -200);
	b_lift(0);

	// open claw
	nb_cone_intake(OPEN);

	// go for second cone
	abortAutostack();
	startTask(fieldReset);
	bl_drive(140, 1000, 127);
	autostack_state.maxHeight = 1680; // works 1/28
	nb_cone_intake(CLOSED);
	startTask(autostackUp);

	// open claw
	/*nb_cone_intake(OPEN);

	// go for third cone
	abortAutostack();
	startTask(fieldReset);
	bl_drive(140, 1000, 127);
	autostack_state.maxHeight = 1680; // works 1/28
	nb_cone_intake(CLOSED);
	startTask(autostackUp);*/
}

void auton28(int direction) {
	mogoAndCones();
	// drive back, rotate
	bl_drive(720, 3000, -127);// change drive back if we don want the third cone
	abortAutostack();
	nb_vbar(2550, 127, 5000);
	bl_drive_rotate(450, 3000, -127 * direction);
	b_vbar(20);

	// align the robot with the 20pt zone using the stago
	b_drive(-70, -70);
	waitUntil(stagoAlign20(direction));
	stopTask(nb_vbar_PID_task);
	bl_drive_rotate(900, 5000, -127 * direction);
	stopTask(autonManager);
	b_cone_intake(127);
	wait1Msec(350);
	scoreOn20();
}
