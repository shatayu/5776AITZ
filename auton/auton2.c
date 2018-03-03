// grabs stago and mogo
void auton2(int direction) {
	// stago score
	//wait1Msec(2500); // T team delay
	//bl_drive(20, 3000, 127); // needs tuning
	//bl_drive_rotate(900, 3000, -80 * direction);
	b_cone_intake(30);
	nb_lift_PID(2600, 127, 15000);
	wait1Msec(500); // T team delay
	nb_vbar(900, 127, 5000);
	bl_drive(560, 3000, 127); // needs tuning
	stopTask(nb_lift_PID_task);
	wait1Msec(500);
	b_lift(-127);
	wait1Msec(500);
	b_lift(0);
	b_cone_intake(-127);
	b_lift(127);
	wait1Msec(200);
	b_lift(0);
	b_cone_intake(0);
	bl_drive(460, 3000, -127); // needs tuning

	bl_drive_rotate(900, 3000, 80 * direction);
	bl_drive(500, 3000, -127);
}
