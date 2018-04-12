task field_up() {
	stopTask(nb_lift_PID_task);

	//// debug code - leave this here
	//autostack_state.vbar_height = testLiftHeight; // debug code
	//autostack_state.vbar_height = testVbarHeight;
	//autostack_state.drop = testDropTime;

	autostack_state.stacked = 1;

	// stall torque to grip cone with
	b_cone_intake(20);

	// tell lift to go up until vbar can start rising with it, then have both go up
	nb_lift(autostack_state.lift_height, 127, 15000);
	waitUntil(sget_lift(SENSOR) > autostack_state.lift_height - autostack_state.offset_up);
	nb_vbar(autostack_state.vbar_height, 127, 2000);

	// come down once the vbar's all the way back
	waitUntil(sget_vbar(SENSOR) > autostack_state.vbar_height);
	stopTask(nb_lift_task);
	b_lift(-127);
	wait1Msec(autostack_state.drop);
	b_cone_intake(-127);
	wait1Msec(100);

	// flag stacked as true
	autostack_state.stacked = 2;
}

task field_reset() {
	b_lift(127);
	wait1Msec(150);
	b_lift(20);

	// bring the vertibar down all the way
	int vbar_reset = 1470;
	int lift_reset = 300;
	stopTask(nb_vbar_PID_task);

	nb_vbar(vbar_reset, 127, 125000);

	// reset lift all the way
	int offset = 1400;
	waitUntil(sget_vbar(SENSOR) < vbar_reset + offset);

	// bring lift to reset height
	nb_lift(lift_reset, 127, 125000);
	b_lift(20);

	// finish up
	b_cone_intake(127);
	waitUntil(sget_lift(SENSOR) < lift_reset + 200 && sget_vbar(SENSOR) < vbar_reset + 600);
	autostack_state.stacked = 0;
}
