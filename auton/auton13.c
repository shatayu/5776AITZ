void auton13(int direction){

	mogoAndCones28();
	startTask(autonManager2);

	// drive back to 5pt zone
	bl_drive(1580, 3000, -127); // tune this distance

	// rotate to deposit
	bl_drive_rotate(1800, 3000, -80 * direction);
	b_vbar(20);

	wait1Msec(100);
	b_mogo_intake(127); // tune?
	wait1Msec(800); // tune?
	bl_drive(500, 3000, -127);

	stopTask(autonManager2);
}
