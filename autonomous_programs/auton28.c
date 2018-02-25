task autonManager() {
	nb_lift_PID(1700, 127, 5000);
	b_vbar(20);
  wait1Msec(250);
	nb_mogo_intake(800, 127, 3000);
	b_lift(0);
}

task autonManager2() {
	waitUntil(autostack_state.stacked == true);
	nb_lift_PID(2000, 127, 125000);
}

int LEFT = 1;
int RIGHT = -1;
bool stagoAlignBack(int side) {
	bool result;
	if (side == LEFT) {
		result = (SensorValue[LUltrasonic] > 30 && SensorValue[LUltrasonic] < 75);
	} else if (side == RIGHT) {
		result = (SensorValue[RUltrasonic] > 30 && SensorValue[RUltrasonic] < 75);
	}
	return result;
}

bool stagoAlign20(int side) {
	bool result;
	if (side == LEFT) {
		result = (SensorValue[LUltrasonic] > 0 && SensorValue[LUltrasonic] < 50);
	} else if (side == RIGHT) {
		result = (SensorValue[RUltrasonic] > 0 && SensorValue[RUltrasonic] < 50);
	}
	return result;
}



// gets mogo and however any cones are programmed
void mogoAndCones() {
	b_cone_intake(30);

	// drive up to mogo
	startTask(autonManager);
	bl_drive(1350, 3000, 127);
	stopTask(autonManager)
	// intake mogo
	stopTask(nb_mogo_intake_task);
	//nb_mogo_intake(2700, 127, 3000);
	b_mogo_intake(-127);
	waitUntil(SensorValue[MogoPot] > 2600);
	b_mogo_intake(0);

	// BRING CONE DOWN ON CONE
	// once the lift is at the top come down on the stack
	stopTask(nb_vbar_PID_task);
	stopTask(nb_lift_PID_task);
	//b_lift(-127);
	//wait1Msec(400);
	//b_lift(0);

	// outtake
	b_cone_intake(-127);
	wait1Msec(200);

	// go for second cone
	abortAutostack();
	startTask(fieldReset);
	bl_drive(170, 1000, 127);
	waitUntil(autostack_state.stacked == false);
	autostack_state.maxHeight = 1800; // works 1/28
	// bring the lift down

	// come down on claw
	abortAutostack();
	b_cone_intake(127);
	b_lift(-127);
	wait1Msec(600);
	// stack
	startTask(autostackUp);
	waitUntil(autostack_state.stacked);

	// cone #3
	startTask(fieldReset);
	bl_drive(170, 1000, 127);
	waitUntil(autostack_state.stacked == false);
	autostack_state.maxHeight = 1800; // works 1/28

	// come down on claw
	abortAutostack();
	b_cone_intake(127);
	b_lift(-127);
	wait1Msec(600);
	// stack
	startTask(autostackUp);
	startTask(autonManager2);
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
	bl_drive(1670, 3000, -127);// change drive back if we don want the third cone
	bl_drive_rotate(450, 3000, -127 * direction);
	b_vbar(20);

	// align the robot with the 20pt zone using the stago
	b_drive(-127, -127);
	waitUntil(stagoAlign20(direction));
	stopTask(nb_vbar_PID_task);
	bl_drive_rotate(900, 5000, -127 * direction);
	stopTask(autonManager);
	scoreOn20();
}
