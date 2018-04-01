void auton9(int direction) {
	mogoAndCones();

	startTask(autonManager2);
	// drive back, rotate
	bl_drive(1250, 3000, -127); // tune this distance
	bl_drive_rotate(1800, 3000, -127 * direction);
	b_vbar(20);

	//mogo eject
	wait1Msec(100);
	b_mogo_intake(127); // tune?
	wait1Msec(800); // tune?
	bl_drive(500, 3000, -127);

	stopTask(autonManager2);
}
