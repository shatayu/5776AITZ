bool getStackTrigger() {
	int threshold = 2310; // tuned
	return SensorValue[ClawPot] > threshold && autoDetection; // false := don't stack, true := do stack
}

void detect(bool state) {
	autoDetection = state;
}

void nb_cone_intake(int state) {
	coneIntake.target = state;
	startTask(nb_cone_intake_task);
}

task nb_cone_intake_task() {
	if (coneIntake.target == INTAKE) { // sensor based intake
		b_cone_intake(127);
		waitUntil(getStackTrigger());
		b_cone_intake(0);
	} else if (coneIntake.target == OUTTAKE) { // time based outtake
		int outtakeTime = 300;
		b_cone_intake(-127);
		wait1Msec(outtakeTime);
		b_cone_intake(0);
	} else { // neutral
		b_cone_intake(0);
	}
}

void nb_mogo_intake(int target, int power, int timeout) {
	mogoIntake.target = target;
	mogoIntake.power = power;
	mogoIntake.timeout = timeout;

	startTask(nb_mogo_intake_task);
}

// 720 all the way out
// 2720 all the way in
// 1270 release mogo
task nb_mogo_intake_task() {
	clearTimer(T2);
	if (mogoIntake.target > SensorValue[MogoPot]) {
		b_mogo_intake(-abs(mogoIntake.power));
		waitUntil(mogoIntake.target < SensorValue[MogoPot]);
	} else {
		b_mogo_intake(abs(mogoIntake.power));
		waitUntil(mogoIntake.target > SensorValue[MogoPot]);
	}
	b_mogo_intake(0);
}
