task liftManagement() {
	nb_lift(1800, 127, 5000);
	nb_vbar_PID(2400, 127, 5000);
	waitUntil(SensorValue[MainLiftPot] > 1800);
	b_lift(20);
}

void scoreOn20() {
	// raise lift and drive into the 20pt pole
	startTask(liftManagement);
	wait1Msec(400);

	bl_drive(300, 2500, 127);
	b_drive(30, 30);

	// pull mogo out (nonblocking function made blocking)
	b_mogo_intake(70);
	wait1Msec(500);
	b_mogo_intake(0);

	// drive backwards, then lift up to escape
	b_drive(-30, -30);
	wait1Msec(100);
	b_mogo_intake(-127);
	wait1Msec(700);
	b_mogo_intake(0);

	startTask(fieldReset);
	b_drive(-127, -127);
	wait1Msec(500);
	b_drive(50, 50);
	wait1Msec(30);
	b_drive(0, 0);

	// ensure autostack flag is not incorrect
}