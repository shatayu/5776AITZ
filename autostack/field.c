task field_up() {
	stopTask(nb_lift_PID_task);
	//// debug code - leave this here
	//autostack_state.vbar_height = testLiftHeight; // debug code
	//autostack_state.vbar_height = testVbarHeight;
	//autostack_state.drop = testDropTime;

	stopTask(nb_lift_PID_task);
	autostack_state.stacked = false;

	// stall torque to grip cone with
	b_cone_intake(20);

	// tell lift to go up until vbar can start rising with it, then have both go up
	nb_lift(autostack_state.lift_height, 127, 15000);
	waitUntil(sget_lift(SENSOR) > autostack_state.lift_height);
	b_lift(127);
	nb_vbar(autostack_state.vbar_height, 127, 2000);

	// come down once the vbar's all the way back
	waitUntil(sget_vbar(SENSOR) > autostack_state.vbar_height);
	stopTask(nb_lift_task);
	b_lift(-127);
	wait1Msec(autostack_state.drop);
	b_cone_intake(-127);
	wait1Msec(100);

	// flag stacked as true
	autostack_state.stacked = true;
}

task field_reset() {
	b_lift(127);
	wait1Msec(100);
	b_lift(20);

	// bring the vertibar down all the way
	int vbar_reset = 1470;
	int lift_reset = 1570;
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
