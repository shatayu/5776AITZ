
//cones on stago starts at the hieght of the same value as  6 cones on mogo autostack(6) hieght
//cones on stogo max is 5 cones so autostack(11)
task stago_up() {
	autostack_state.stacked = 1;
	// stago is ~6 cones tall
	autostack_state.lift_height = heights[autostack_state.stago_cones + 6];

	// stall torque to hold cone
	b_cone_intake(30);

	// lift to correct heights
	nb_lift_PID(autostack_state.lift_height, 127, 5000);
	waitUntil(autostack_state.lift_height - 100 < sget_lift(SENSOR));

	// bring vbar to correct heights
	autostack_state.vbar_height = 2000; // vbar angle to land on stago - needs tuning
	nb_vbar_PID(autostack_state.vbar_height, 127, 5000);
	waitUntil(autostack_state.vbar_height + 50 > sget_vbar(SENSOR));

	b_lift(-127);
	autostack_state.drop = 400; // tune this
	wait1Msec(autostack_state.drop);
	b_lift(0);
	b_cone_intake(-127);
	autostack_state.stacked = 2;
}

task stago_reset() {
	stopTask(nb_lift_PID_task);
	// start outtaking
	b_cone_intake(-127);

	// get lift up
	if (autostack_state.mogo_cones > 11) {
		autostack_state.mogo_cones = 11;
	}
	nb_lift_PID(heights[autostack_state.mogo_cones + 1], 127, 10000);
	waitUntil(sget_lift(SENSOR) > heights[autostack_state.mogo_cones] - 50);

	// bring vbar to appropriate height
	stopTask(nb_vbar_PID_task);
	nb_vbar_PID(vbarHeights[autostack_state.mogo_cones], 127, 10000);
	waitUntil(sget_vbar(SENSOR) > vbarHeights[autostack_state.mogo_cones] - 50);
	autostack_state.stacked = 0;

	// start intaking again
	b_cone_intake(127);
}
