void b_drive(int left, int right) {
	motor[LDrive] = left;
	motor[RDrive] = right;
}

//positive power -> cw
//negative power -> ccw
void b_drive(int power) {
	b_drive(power, -power);
}

//positive power -> forward
//negative power -> backward
void b_drive_rotate(int power) {
	b_drive(power, power);
}


void b_lift(int power) {
	motor[LMainLift] = power;
	motor[RMainLift] = power;
}

void b_vbar(int power) {
	motor[TopLift] = power;
}

void b_cone_intake(int power) {
	motor[ConeIntake] = power;
}

void b_mogo_intake(int power) {
	motor[LMogoIntake] = power;
	motor[RMogoIntake] = power;
}
