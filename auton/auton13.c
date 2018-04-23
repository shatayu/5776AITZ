void auton13(int direction){
	mogoAndCones28(true);
	stopTask(forwardAutonHelper);
	stopTask(subsystemControl);
	stopTask(autostack_control);

	//// drive back to 5pt zone
	bl_drive(1250, -127, 3000); // tune this distance

	//// rotate to deposit
	abortAutostack();
	bl_drive_rotate(1800, -127 * direction, 4000);
	b_lift(127);
	wait1Msec(500);
	b_lift(0);
	nb_vbar(3850, 127, 5000);

	// extend mogo
	b_mogo_intake(127);
	wait1Msec(1300); // tune time
	b_mogo_intake(0);

	bl_drive(500, -127, 2000);
}
