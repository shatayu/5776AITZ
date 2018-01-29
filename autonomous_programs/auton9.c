void auton9(int direction) {
	mogoAndCones();
	// drive back, rotate
	bl_drive(645, 3000, -127);
	abortAutostack();
	nb_vbar(2550, 127, 5000);
	bl_drive_rotate(1800, 3000, 127 * direction);
	b_vbar(20);
	nb_cone_intake(OPEN);

	nb_lift(1800, 127, 5000);
	wait1Msec(700);

	b_mogo_intake(127);
	wait1Msec(1000);
	b_mogo_intake(0);

	b_drive(-127, -127);
	wait1Msec(700);
	b_drive(0);
}
