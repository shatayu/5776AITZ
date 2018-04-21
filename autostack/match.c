task match_up() {
	stopTask(nb_lift_PID_task);

	//// debug code - leave this here
	//autostack_state.vbar_height = testLiftHeight; // debug code
	//autostack_state.vbar_height = testVbarHeight;
	//autostack_state.drop = testDropTime;

	autostack_state.stacked = 1;
	// stall torque to grip cone with
	b_cone_intake(30);
	// nb_vbar_PID(2000, 127, 15000);
	// waitUntil(sget_vbar(SENSOR) > 1650);

	// tell lift to go up until vbar can start rising with it, then have both go up
	if (autostack_state.mogo_cones != 5) {
		nb_lift_PID(autostack_state.lift_height, 127, 15000);
	}
	waitUntil(sget_lift(SENSOR) > autostack_state.lift_height - autostack_state.offset_up);
	writeDebugStreamLine("vbar moving back now");
	stopTask(nb_vbar_PID_task);

	if (autostack_state.mogo_cones < 11) {
		nb_vbar(autostack_state.vbar_height, 127, 15000);
	} else {
		nb_vbar_PID(autostack_state.vbar_height, 127, 15000);
	}

	// come down once the vbar's all the way back
	waitUntil(sget_vbar(SENSOR) > autostack_state.vbar_height);
	b_vbar(20);
	stopTask(nb_lift_task);
	stopTask(nb_lift_PID_task);
	b_cone_intake(-127);
	wait1Msec(autostack_state.drop);
	// flag stacked as true
	autostack_state.stacked = 2;
}

task match_reset() {
	// bring the vertibar down all the way
	int vbar_reset = 1550;
	int lift_reset = 2200 - 1400;

	if (autostack_state.mogo_cones < 5) {
		nb_lift_PID(lift_reset - 500, 127, 5000);
		waitUntil(sget_lift(SENSOR) > lift_reset - 500);
	} else {
		b_lift(127);
		wait1Msec(150);
		b_lift(20);
	}

	stopTask(nb_vbar_PID_task);

	nb_vbar(vbar_reset, 127, 125000);

	// reset lift all the way
	int offset = 1400;
	waitUntil(sget_vbar(SENSOR) < vbar_reset + offset);
	writeDebugStreamLine("now coming down");

	// bring lift to reset height
	nb_lift_PID(lift_reset - 50, 127, 125000);

	// finish up
	b_cone_intake(127);
	waitUntil(sget_lift(SENSOR) < lift_reset + 200 && sget_vbar(SENSOR) < vbar_reset + 600);
	b_lift(20);
	autostack_state.stacked = 0;
}