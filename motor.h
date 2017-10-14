void moveDrive(int left, int right) {
	motor[LDrive] = left;
	motor[RDrive] = right;
}

void moveMainLift(int power) {
	motor[LMainLift] = power;
	motor[RMainLift] = power;
}

void moveTopLift(int power) {
	motor[TopLift] = power;
}

void moveMogoIntake(int power) {
	motor[LMogoIntake] = power;
	motor[RMogoIntake] = power;
}

void moveConeIntake(int power) {
	motor[ConeIntake] = power;
}

void clawStall(bool on) {
	// if on then stall
	if (on) {
		moveConeIntake(30);
	} else {
		moveConeIntake(0);
	}
}
