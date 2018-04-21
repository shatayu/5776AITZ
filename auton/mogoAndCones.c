// helper task to manage lift/mogo intake
task forwardAutonHelper() {
	b_cone_intake(20);
	nb_lift_PID(600, 127, 5000);
	b_vbar(20);
	wait1Msec(300);
	// extend mogo
	b_mogo_intake(127);
	wait1Msec(1000); // tune time
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
	startTask(forwardAutonHelper);
	wait1Msec(700);
	// proceed with auton
	bl_drive(1185, 127, 3000);
	stopTask(forwardAutonHelper);
	// intake mogo
	stopTask(nb_mogo_intake_task);

	// withdraw mogo
	b_mogo_intake(-127);
	wait1Msec(1300); // tune time
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
	startTask(field_reset);
	autostack_state.mogo_cones = 1;
	bl_drive(50, 127, 1500); // tune this distance
	waitUntil(autostack_state.stacked == 0);

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
	bl_drive(120, 127, 2100); // tune this distance
	waitUntil(autostack_state.stacked == 0);

	// bring rollers down
	abortAutostack();
	//b_cone_intake(127);
	//b_lift(-127);
	//wait1Msec(600);
	getCone();
	// stack
	autostack(2, FIELD, false);
}

void mogoAndCones28() {
	zero_gyro();
	mogoAndCones26();

	waitUntil(autostack_state.stacked == 2);
	startTask(field_reset);
	waitUntil(autostack_state.stacked == 0);
	b_cone_intake(127);
	bl_drive(170, 127, 2000);// fourth cone

	// intake cone
	abortAutostack();
	//b_cone_intake(127);
	//b_lift(-127);
	//wait1Msec(600);
	getCone();
	// stack
	autostack(3, MATCH, false);
}
