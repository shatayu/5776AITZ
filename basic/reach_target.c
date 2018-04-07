task nb_lift_task() {
	// config
	int power = abs(lift.power) * sgn(target - sget_lift(SENSOR)); // corrects the sign
	clearTimer(T1);

	// powers the lift
	b_lift(power);

	// waits until either the target is reached or the timeout has been hit
	if (power > 0) {
		waitUntil(lift.target < sget_lift(SENSOR) || time1[T1] > lift.timeout);
	} else {
		waitUntil(lift.target > sget_lift(SENSOR) || time1[T1] > lift.timeout);
	}

	// stopping
	b_lift(-sgn(power) * 30);
	wait1Msec(50);
	b_lift(0);
}

task nb_vbar_task() {
	// config
	int power = abs(vbar.power) * sgn(vbar.target - sget_vbar(SENSOR)); // corrects the sign
	clearTimer(T2);

	// powers the vertibar
	b_vbar(power);

	// waits until either the target is reached or the timeout has been hit
	if (power > 0) {
		waitUntil(vbar.target < sget_vbar(SENSOR) || time1[T2] > vbar.timeout);
	} else {
		waitUntil(vbar.target > sget_vbar(SENSOR) || time1[T2] > vbar.timeout);
	}

	// stop the vertibar
	b_vbar(0);
}

task nb_mogo_task() {
	// config
	int power = abs(mogo.power) * sgn(mogo.target - sget_mogo(SENSOR)); // corrects sign
	clearTimer(T3);

	// powers the mogo intake
	b_mogo(power);

	// waits until either the target is reached or the timeout has been hit
	if (power > 0) {
		waitUntil(mogo.target < sget_mogo(SENSOR) || time1[T3] > mogo.timeout);
	} else {
		waitUntil(mogo.target > sget_mogo(SENSOR) || time1[T3] > mogo.timeout);
	}

	// stop the mogo
	b_mogo(0);
}
