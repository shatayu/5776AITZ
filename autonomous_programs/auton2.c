void auton2(int direction) {
	b_cone_intake(-20);

	bl_drive(20, 3000, 127);
	bl_drive_rotate(900, 5000, 70 * direction);

	// raise lift up
	nb_lift(2100, 127, 5000);
	nb_vbar_PID(2400, 127, 125000);
	waitUntil(SensorValue[MainLiftPot] > 1800);
	b_lift(20);

	// go up to stago
	bl_drive(300, 5000, 127);
	stopTask(nb_vbar_PID_task);
	nb_vbar(550, 127, 5000);
	wait1Msec(500);

	// bring lift down
	nb_lift(1800, 127, 2000);
	wait1Msec(2000);
	nb_cone_intake(OPEN);

	// raise lift and dip out
	nb_lift(2100, 127, 5000);
	wait1Msec(500);
	b_drive(-127, -127);
	wait1Msec(500);
	b_drive(0);
}
