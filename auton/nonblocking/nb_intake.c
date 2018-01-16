void nb_cone_intake(int state) {
	coneIntake.target = state;
	coneIntake.power = 127;
	coneIntake.timeout = 250;

	startTask(nb_cone_intake_task);
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
	int timer = 0;

	if (mogoIntake.target > SensorValue[MogoPot]) {
		while (mogoIntake.target > SensorValue[MogoPot] && timer < mogoIntake.timeout) {
			b_mogo_intake(mogoIntake.power);
			wait1Msec(20);
			timer += 20;
		}
	} else {
		while (mogoIntake.target < SensorValue[MogoPot] && timer < mogoIntake.timeout) {
			b_mogo_intake(-mogoIntake.power);
			wait1Msec(20);
			timer += 20;
		}
	}
	b_mogo_intake(0);
}
