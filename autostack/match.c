task match_up() {
	if (autostack_state.mogo_cones < 4) {
		// bring vertibar back
		b_vbar(127);
		waitUntil(sget_vbar(SENSOR) > sget_vbar(MAX) - 50);
		b_vbar(0);

		// drop the cone
		b_cone_intake(-127);
		wait1Msec(300); // tune drop time
	} else {
		startTask(field_up);
		waitUntil(autostack_state.stacked);
		b_lift(127);
		wait1Msec(100);
		b_lift(20);
	}
}

task match_reset() {
	// bring the vertibar down all the way
	int vbar_reset = 1470;
	int lift_reset = 1570; // needs tuning
	stopTask(nb_vbar_PID_task);

	nb_vbar(vbar_reset, 127, 125000);

	// reset lift all the way
	int offset = 1600;
	waitUntil(sget_vbar(SENSOR) < vbar_reset + offset);

	// bring lift to reset height
	nb_lift_PID(lift_reset, 127, 125000);

	// finish up
	b_cone_intake(127);
	waitUntil(sget_lift(SENSOR) < lift_reset);
	autostack_state.stacked = false;
}
