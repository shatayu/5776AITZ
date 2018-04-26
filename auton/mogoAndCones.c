// helper task to manage lift/mogo intake
task forwardAutonHelper() {
	b_cone_intake(40);
	nb_lift_PID(400, 127, 5000);
	b_vbar(20);
	wait1Msec(300);
	// extend mogo
	b_mogo_intake(127);
	wait1Msec(1000); // tune time
	b_mogo_intake(20);

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

bool detectMogo() {
	int threshold = 6;
	return SensorValue[MogoDetector] > -1 && SensorValue[MogoDetector] < threshold;
}

// gets mogo and preload + 1 field cones (24pt)
void mogoAndCones(bool correct) {
// drive up to mogo
	startTask(forwardAutonHelper);
	wait1Msec(600);
	// proceed with auton
	//bl_drive(570, 127, 3000, false); // used to be 1185 127 3000

	// test drive distance
	//bl_drive(610, 80, 3000);
	//bl_drive(distance1, 80, 3000);
	int timer = 0;
	b_drive(127, 127);
	while (!detectMogo() && timer < 8000) {
		timer += 20;
		wait1Msec(20);
	}
	bl_drive(70, 127, 1000);

	stopTask(forwardAutonHelper);
	// intake mogo
	stopTask(nb_mogo_intake_task);
	b_cone_intake(20);
	// withdraw mogo
	//nb_vbar_PID(3500, 127, 125000);
	b_mogo_intake(-127);
	wait1Msec(1300); // tune time
	b_mogo_intake(0);

	// BRING CONE DOWN ON CONE
	// once the lift is at the top come down on the stack
	stopTask(nb_vbar_PID_task);
	stopTask(nb_lift_PID_task);

	// bring lift down and outtake preload
	b_lift(-127);
	wait1Msec(300);
	b_cone_intake(-127);
	b_lift(127);
	wait1Msec(100);


	// go for second cone
	abortAutostack();
	startTask(field_reset);
	autostack_state.mogo_cones = 1;
	if (correct) {
		//bl_drive_rotate(-sget_gyro()/2, 60, 1000);
	}

	// test distance
	//bl_drive(70, 127, 1500); // tune this distance
	bl_drive(distance2, 127, 1500);
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

void mogoAndCones26(bool correct) {
	mogoAndCones(true);
	waitUntil(autostack_state.stacked == 2);

	// cone #3
	startTask(field_reset);
	if (correct) {
		bl_drive_rotate(-sget_gyro(), 127, 1000);
	}

	// drive forward at partial power
	// test distance
	bl_drive(distance3, 127, 2100);
	//bl_drive(120, 127, 2100); // tune this distance

	// wait until lift is back down
	waitUntil(autostack_state.stacked == 0);

	// bring rollers down
	abortAutostack();
	getCone();
	// stack
	autostack(2, FIELD, false);
}

void mogoAndCones28(bool correct) {
	zero_gyro();
	mogoAndCones26(true);

	waitUntil(autostack_state.stacked == 2);
	startTask(field_reset);
	if (correct) {
		bl_drive_rotate(sget_gyro(), 80, 1000);
	}
	waitUntil(autostack_state.stacked == 0);
	b_cone_intake(127);

	// test distance
	bl_drive(distance4, 127, 2000);
	//bl_drive(170, 127, 2000);// fourth cone

	// intake cone
	abortAutostack();
	getCone();

	bl_drive(80, -127, 2000);
	// stack
	autostack(3, MATCH, false);
}
