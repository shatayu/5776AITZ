task liftManagement() {
	b_lift(127);
	nb_vbar(2550, 127, 5000);
	waitUntil(SensorValue[MainLiftPot] > 1800);
	b_lift(-50);
	wait1Msec(50);
	b_lift(0);
	waitUntil(SensorValue[TopLiftPot] > 2550);
	b_vbar(20);
}

void scoreOn20() {
	// raise lift and drive into the 20pt pole
	startTask(liftManagement);
	wait1Msec(400);

	bl_drive(300, 2500, 127);
	b_drive(127, 127);
	wait1Msec(1000);
	b_mogo_intake(127);
	wait1Msec(1000);

	// drive backwards, then lift up to escape
	b_drive(-127, -127);
	wait1Msec(250);
	b_mogo_intake(-127);
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
}
