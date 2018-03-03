// helper task to manage lift/mogo intake
task autonManager() {
	nb_lift_PID(1800, 127, 5000);
	b_vbar(20);
	wait1Msec(300);
	nb_mogo_intake(800, 127, 3000);
	b_lift(0);
}

// gets mogo and preload + 1 field cones (24pt)
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
	wait1Msec(200);
	b_cone_intake(-127);
	wait1Msec(200);
	b_lift(0);

	// go for second cone
	abortAutostack();
	startTask(fieldReset);
	bl_drive(160, 1500, 127); // tune this distance
	waitUntil(autostack_state.stacked == false);
	autostack_state.maxHeight = 1750; // works 1/28

	// bring lift and rollers down
	abortAutostack();
	b_cone_intake(127);
	b_lift(-127);
	wait1Msec(600);
	// stack
	startTask(autostackUp);
}

void mogoAndCones26() {
	mogoAndCones();
	waitUntil(autostack_state.stacked);

	// cone #3
	startTask(fieldReset);
	bl_drive(160, 2100, 127); // tune this distance
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
	mogoAndCones26();
	autostack_state.maxHeight = 1790; // works 3/1
	waitUntil(autostack_state.stacked);
	startTask(fieldReset);
	waitUntil(autostack_state.stacked == false);
	b_cone_intake(127);
	bl_drive(160, 2000, 127);// fourth cone

	// intake cone
	abortAutostack();
	b_cone_intake(127);
	b_lift(-127);
	wait1Msec(600);
	// stack
	startTask(autostackUp);
}
