// helper task to manage lift/mogo intake
task forwardAutonHelper() {
	nb_lift_PID(400, 127, 5000);
	b_vbar(20);
	wait1Msec(300);
	// extend mogo
	b_mogo_intake(-127);
	wait1Msec(2000); // tune time
	b_mogo_intake(0);

	b_lift(0);
}

// comes down on cone
void getCone() {
	abortAutostack();
	b_cone_intake(127);
	b_lift(-127);
	b_vbar(-127);

	clearTimer(T1);
	waitUntil(sget_trigger() || time1[T1] > 600);
}

// gets mogo and preload + 1 field cones (24pt)
void mogoAndCones() {
// drive up to mogo
	//startTask(forwardAutonHelper);
	//b_cone_intake(20);
	//nb_lift_PID(600, 127, 5000);
	//b_vbar(20);
	//wait1Msec(300);
	//// extend mogo
	//b_mogo_intake(127);
	//wait1Msec(1000); // tune time
	//b_mogo_intake(0);

	//b_lift(0);

	//// proceed with auton
	//wait1Msec(700);
	//bl_drive(1250, 127, 3000);
	//stopTask(forwardAutonHelper);
	//// intake mogo
	//stopTask(nb_mogo_intake_task);

	//// withdraw mogo
	//b_mogo_intake(-127);
	//wait1Msec(2000); // tune time
	//b_mogo_intake(0);

	//// BRING CONE DOWN ON CONE
	//// once the lift is at the top come down on the stack
	//stopTask(nb_vbar_PID_task);
	//stopTask(nb_lift_PID_task);

	// bring lift down and outtake preload
	b_lift(-127);
	wait1Msec(200);
	b_cone_intake(-127);
	wait1Msec(200);
	b_lift(0);

	// go for second cone
	abortAutostack();
	startTask(field_reset);
	autostack_state.mogo_cones = 1;
	bl_drive(45, 127, 1500); // tune this distance
	waitUntil(autostack_state.stacked == 0);
	autostack_state.lift_height = 300; // works 1/28
	autostack_state.vbar_height = 3900;
	autostack_state.drop = 200;
	autostack_state.offset_up = 300;

	// bring lift and rollers down
	abortAutostack();
	//b_cone_intake(127);
	//b_lift(-127);
	//wait1Msec(600);
	getCone();
	// stack
	autostack(1, FIELD, false);
}

void mogoAndCones26() {
	mogoAndCones();
	waitUntil(autostack_state.stacked == 2);

	// cone #3
	startTask(field_reset);
	bl_drive(160, 127, 2100); // tune this distance
	waitUntil(autostack_state.stacked == 0);
	autostack_state.lift_height = 150 + 105; // works 1/28
	autostack_state.vbar_height = 3750;
	autostack_state.drop = 200;
	autostack_state.offset_up = 300;

	// bring rollers down
	abortAutostack();
	//b_cone_intake(127);
	//b_lift(-127);
	//wait1Msec(600);
	getCone();
	// stack
	startTask(field_up);
}

void mogoAndCones28() {
	mogoAndCones26();

	autostack_state.lift_height = 150 + 235; // works 1/28
	autostack_state.vbar_height = 3750;
	autostack_state.drop = 200;
	autostack_state.offset_up = 300;

	waitUntil(autostack_state.stacked == 2);
	startTask(field_reset);
	waitUntil(autostack_state.stacked == 0);
	b_cone_intake(127);
	bl_drive(160, 127, 2000);// fourth cone

	// intake cone
	abortAutostack();
	//b_cone_intake(127);
	//b_lift(-127);
	//wait1Msec(600);
	getCone();
	// stack
	startTask(field_up);
}
