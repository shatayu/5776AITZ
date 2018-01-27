void auton9(int direction) {
	b_cone_intake(-20);

	// drive up to mogo
	startTask(autonManager);
	wait1Msec(300);
	bl_drive(725, 3000, 127);
	wait1Msec(250);
	nb_mogo_intake(2450, 127, 3000);
	waitUntil(SensorValue[MogoPot] > 2450);

	// BRING CONE DOWN ON CONE
	// once the lift is at the top come down on the stack
	stopTask(nb_vbar_PID_task);
	nb_vbar_PID(2840, 127, 1000);
	startTask(nb_lift_velocity);
	b_lift(-127);
	wait1Msec(200);
	waitUntil(lift.velocity > -150);
	b_lift(0);

	// open claw
	nb_cone_intake(OPEN);

	// go for second cone
	bl_drive(145, 1000, 127);
	autostack_state.maxHeight = 1570; // works 1/13
	autostack_state.vbarHeight = 2840;

	abortAutostack();
	nb_vbar(550, 127, 5000);
	nb_lift(1330, 127, 5000);
	waitUntil(SensorValue[TopLiftPot] < 600);
	b_lift(-127);
	b_drive(-127, -127);
	wait1Msec(400);
	nb_cone_intake(CLOSED);
	startTask(autostackUp);

	// drive back, rotate
	bl_drive(595, 3000, -127);
	abortAutostack();
	nb_vbar_PID(2600, 127, 5000);
	bl_drive_rotate(1800, 3000, 127 * direction);
	nb_cone_intake(OPEN);

	nb_lift(1600, 127, 5000);
	wait1Msec(700);

	b_mogo_intake(127);
	wait1Msec(1000);
	b_mogo_intake(0);

	b_drive(-127, -127);
	wait1Msec(700);
	b_drive(0);
}