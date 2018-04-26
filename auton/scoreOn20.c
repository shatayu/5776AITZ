void scoreOn20() {
	stopTask(subsystemControl);
	// drive up and deposit mobile goal
	nb_lift_PID(700, 127, 125000);
	nb_vbar(3600, 127, 5000);
	waitUntil(sget_lift(SENSOR) > 400);


	b_drive(127, 127); // tune?
	wait1Msec(1800);

	//// test
	//bl_drive(400, 127, 2000);


	b_mogo_intake(127); // tune?
	wait1Msec(1100); // tune?

	// drive backwards, then lift up to escape
	b_drive(-127, -127); // tune?
	wait1Msec(250); // tune?
	b_mogo_intake(-127); // tune

	// mogo withdrawn, drive stopped

	// test
	wait1Msec(750);
	//wait1Msec(250);


	b_drive(0, 0);
	stopTask(autostack_control);
	b_cone_intake(0);
	// raise lift and drive into the 20pt pole
	//nb_vbar(resetVbarHeight,
	b_cone_intake(0);
	// bring the vertibar to an intermediary angle
	int resetVbarHeight = 1550;

	// ensure autostack flag i 127, 125000);
	nb_lift_PID(900, 127, 125000);
	waitUntil(sget_lift(SENSOR) > 700);
	waitUntil(sget_vbar(SENSOR) > 2700);
	b_vbar(20);

	b_mogo_intake(0);
	b_drive(0, 0);

	// resets not incorrect
	autostack_state.stacked = false;
}
