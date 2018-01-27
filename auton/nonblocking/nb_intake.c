void nb_cone_intake(int state) {
	if (state == OPEN) {
		b_cone_intake(127);
		wait1Msec(150);
		b_cone_intake(10);
	} else {
		b_cone_intake(-127);
		wait1Msec(150);
		b_cone_intake(-20);
	}
}


task nb_cone_intake_task() {
	if (coneIntake.target == OPEN) {
		b_cone_intake(-coneIntake.power);
	} else {
		b_cone_intake(coneIntake.power);
	}
	wait1Msec(coneIntake.timeout);
	b_cone_intake(0);
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
