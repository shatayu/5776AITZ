void nb_cone_intake(int state) {
	cone_intake.target = state;
	startTask(nb_cone_intake_task);
}

task nb_cone_intake_task() {
	if (cone_intake.target == INTAKE) { // sensor based intake
		b_cone_intake(127);
		waitUntil(sget_trigger());
		b_cone_intake(0);
	} else if (cone_intake.target == OUTTAKE) { // time based outtake
		int outtakeTime = 300;
		b_cone_intake(-127);
		wait1Msec(outtakeTime);
		b_cone_intake(0);
	} else { // neutral
		b_cone_intake(0);
	}
}

void nb_mogo_intake(int target, int power, int timeout) {
	mogo_intake.target = target;
	mogo_intake.power = power;
	mogo_intake.timeout = timeout;

	startTask(nb_mogo_intake_task);
}

task nb_mogo_intake_task() {
	// config
	int power = abs(mogo_intake.power) * sgn(mogo_intake.target - sget_mogo(SENSOR)); // corrects sign
	clearTimer(T3);

	// powers the mogo intake
	b_mogo_intake(power);

	// waits until either the target is reached or the timeout has been hit
	if (power > 0) {
		waitUntil(mogo_intake.target < sget_mogo(SENSOR) || time1[T3] > mogo_intake.timeout);
	} else {
		waitUntil(mogo_intake.target > sget_mogo(SENSOR) || time1[T3] > mogo_intake.timeout);
	}

	// stop the mogo
	b_mogo_intake(0);
}
