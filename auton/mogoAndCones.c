// helper task to manage lift/mogo intake
task autonManager() {
	nb_lift_PID(1700, 127, 5000);
	b_vbar(20);
  wait1Msec(250);
	nb_mogo_intake(800, 127, 3000);
	b_lift(0);
}

// gets mogo and preload + 2 field cones (26pt)
void mogoAndCones() {
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
	bl_drive(130, 1500, 127); // tune this distance
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

	// cone #3
	startTask(fieldReset);
	bl_drive(130, 1500, 127); // tune this distance
	waitUntil(autostack_state.stacked == false);
	autostack_state.maxHeight = 1800; // works 1/28

	// bring rollers down
	abortAutostack();
	b_cone_intake(127);
	b_lift(-127);
	wait1Msec(600);
	// stack
	startTask(autostackUp);
}

void mogoAndCones28() {
	mogoAndCones();
	autostack_state.maxHeight = 1790; // works 3/1
	waitUntil(autostack_state.stacked);
	startTask(fieldReset);
	waitUntil(autostack_state.stacked == false);
	b_cone_intake(127);
	bl_drive(160, 2000, 127);

	// intake cone
	abortAutostack();
	b_cone_intake(127);
	b_lift(-127);
	wait1Msec(600);
	// stack
	startTask(autostackUp);
}
