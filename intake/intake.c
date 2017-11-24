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

task autonMogoIntake() {
	int OPEN_ANGLE = 1;
	int CLOSED_ANGLE = 2;

	int timer = 0;
	int target = (mogoIntake.state) ? OPEN_ANGLE : CLOSED_ANGLE;
	int error = target - SensorValue[MogoPot];

	while (abs(error) > 20 && timer < mogoIntake.timeout) {
		moveMogoIntake(-sgn(error) * mogoIntake.power);
		wait1Msec(20);
		timer += 20;
		error = target - SensorValue[MogoPot];
	}
	moveMogoIntake(0);
}
