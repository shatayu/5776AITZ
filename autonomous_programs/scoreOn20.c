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

	bl_drive(300, 2500, 127);
	b_drive(127, 127);
	wait1Msec(800);
	b_mogo_intake(127);
	wait1Msec(800);

	// drive backwards, then lift up to escape
	wait1Msec(400); // needs tuning, check time

	stopTask(nb_vbar_PID_task);
	b_drive(-127, -127);
	wait1Msec(250);
	b_mogo_intake(-127);
	abortAutostack();
	writeDebugStreamLine("mogo deposited");
	wait1Msec(750);
	b_mogo_intake(0);
	b_drive(0, 0);

	// reset

	b_cone_intake(40);
	// bring the vertibar to an intermediary angle
	int resetVbarHeight = 830;
	int resetLiftHeight = 1500;
	nb_vbar(resetVbarHeight, 127, 125000);

	// reset lift all the way
	waitUntil(SensorValue[TopLiftPot] < resetVbarHeight + 200);

	// bring lift to reset height
	int height = 1320;

	//// brake lift
	nb_lift(height, 70, 7000);
	nb_cone_intake(OPEN);
	waitUntil(SensorValue[MainLiftPot] < height);
	autostack_state.stacked = false;

	// ensure autostack flag is not incorrect
	abortAutostack();
}
