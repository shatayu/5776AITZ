void auton9(int direction) {
// drive up to mogo
	startTask(autonManager);
	bl_drive(1310, 3000, 127);
	stopTask(autonManager)
	// intake mogo
	stopTask(nb_mogo_intake_task);
	//nb_mogo_intake(2700, 127, 3000);
	b_mogo_intake(-127);
	waitUntil(SensorValue[MogoPot] > 2600);
	b_mogo_intake(0);

	// BRING CONE DOWN ON CONE
	// once the lift is at the top come down on the stack
	stopTask(nb_vbar_PID_task);
	stopTask(nb_lift_PID_task);

	// bring lift down and outtake preload
	b_lift(-127);
	b_cone_intake(-127);
	wait1Msec(200);
	b_lift(0);

	// go for second cone
	abortAutostack();
	startTask(fieldReset);
	bl_drive(160, 1500, 127); // tune this distance
	waitUntil(autostack_state.stacked == false);
	autostack_state.maxHeight = 1800; // works 1/28
	// bring the lift down

	// bring rollers down
	abortAutostack();
	b_cone_intake(127);
	b_lift(-127);
	wait1Msec(600);
	// stack
	startTask(autostackUp);
	waitUntil(autostack_state.stacked);

	startTask(autonManager2);
	// drive back, rotate
	bl_drive(1400, 3000, -127); // tune this distance
	bl_drive_rotate(1800, 3000, -127 * direction);
	b_vbar(20);

	//mogo eject
	wait1Msec(100);
	b_mogo_intake(127); // tune?
	wait1Msec(800); // tune?
	bl_drive(500, 3000, -127);

	stopTask(autonManager);
}
