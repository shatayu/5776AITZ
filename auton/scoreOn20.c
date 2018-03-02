task liftManagement() {
	nb_lift_PID(2400, 127, 125000);
	nb_vbar(2550, 127, 5000);
	waitUntil(SensorValue[MainLiftPot] > 1800);
	waitUntil(SensorValue[TopLiftPot] > 2550);
	b_vbar(20);
}

void scoreOn20() {
	b_cone_intake(0);
	// raise lift and drive into the 20pt pole
	startTask(liftManagement);

	// drive up and deposit mobile goal
	bl_drive(300, 2500, 127, false);
	b_drive(127, 127); // tune?
	wait1Msec(900);
	b_mogo_intake(127); // tune?
	wait1Msec(800); // tune?

	// drive backwards, then lift up to escape
	stopTask(nb_vbar_PID_task);
	b_drive(-127, -127); // tune?
	wait1Msec(250); // tune?
	b_mogo_intake(-127); // tune

	// mogo withdrawn, drive stopped
	abortAutostack();
	wait1Msec(750);
	b_mogo_intake(0);
	b_drive(0, 0);

	// reset
	b_cone_intake(0);
	// bring the vertibar to an intermediary angle
	int resetVbarHeight = 830;
	nb_vbar(resetVbarHeight, 127, 125000);

	// ensure autostack flag is not incorrect
	autostack_state.stacked = false;
	abortAutostack();
}
