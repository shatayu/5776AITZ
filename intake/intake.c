void moveConeIntake(int power) {
	motor[ConeIntake] = power;
}

task autonConeIntake() {
	coneIntake.timeout = 250;
	if (coneIntake.state) {
		moveConeIntake(-127);
	} else {
		moveConeIntake(127);
	}
	wait1Msec(coneIntake.timeout);
	moveConeIntake(0);
	stopTask(autonConeIntake);
}

void moveMogoIntake(int power) {
	motor[LMogoIntake] = power;
	motor[RMogoIntake] = power;
}

// 720 all the way out
// 2720 all the way in
// 1270 release mogo
task autonMogoIntake() {
	int timer = 0;
	int target = mogoIntake.state;

	if (mogoIntake.state > SensorValue[MogoPot]) {
		while (mogoIntake.state > SensorValue[MogoPot] && timer < mogoIntake.timeout) {
			moveMogoIntake(mogoIntake.power);
			wait1Msec(20);
			timer += 20;
		}
	} else {
		while (mogoIntake.state < SensorValue[MogoPot] && timer < mogoIntake.timeout) {
			moveMogoIntake(-mogoIntake.power);
			wait1Msec(20);
			timer += 20;
		}
	}
	moveMogoIntake(0);
	stopTask(autonMogoIntake);
}
