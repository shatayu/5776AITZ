task autonManager() {
	nb_lift(1900, 127, 5000);
  wait1Msec(500);
	b_mogo_intake(127);
	waitUntil(SensorValue[MogoPot] < 610);
	b_mogo_intake(20);
	b_lift(20);
}

bool LEFT = true;
bool RIGHT = false;
bool stagoAlign(bool side) {
	writeDebugStreamLine("%d", SensorValue[LUltrasonic]);
	return (SensorValue[LUltrasonic] > 0 && SensorValue[LUltrasonic] < 50);
}

void lineAlign(bool firstSide) {

}

void auton28(int direction) {
	b_cone_intake(-20);

	// drive up to mogo
	startTask(autonManager);
	wait1Msec(300);
	bl_drive(750, 3000, 127);
	wait1Msec(250);
	nb_mogo_intake(2450, 127, 3000);
	waitUntil(SensorValue[MogoPot] > 2450);

	// BRING CONE DOWN ON CONE
	// once the lift is at the top come down on the stack
	startTask(nb_lift_velocity);
	b_lift(-127);
	wait1Msec(500);
	waitUntil(lift.velocity > -150);
	b_lift(0);

	// disable vertibar PID to begin reset
	stopTask(nb_vbar_PID_task);

	// open claw
	b_cone_intake(70);
	waitUntil(SensorValue[ClawPot] < 1470);
	b_cone_intake(0);

	// go for second cone
	bl_drive(120, 1000, 127);
	autostack_state.maxHeight = 1570; // works 1/13
	autostack_state.vbarHeight = 2840;
	startTask(fieldReset);
	b_cone_intake(70);
	waitUntil(SensorValue[ClawPot] < 860);
	b_cone_intake(0);
	waitUntil(!autostack_state.stacked);
	b_cone_intake(-127);
	wait1Msec(250);
	startTask(autostackUp);

	// drive back, rotate
	bl_drive(725, 3000, -127);
	bl_drive_rotate(450, 3000, -127 * direction);

	// align the robot with the 20pt zone using the stago
	b_drive(-70, -70);
	waitUntil(stagoAlign(LEFT));
	bl_drive_rotate(900, 5000, -127);
	stopTask(autonManager);
	b_cone_intake(127);
	wait1Msec(350);
	scoreOn20();
}
