void b_drive(int left, int right) {
	motor[LDrive] = left;
	if (left == 0 || abs(left) == 127) {
		motor[MLDrive] = left;
	}
	motor[RDrive] = right;
	if (right == 0 || abs(right) == 127) {
		motor[MRDrive] = right;
	}
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
	motor[MogoIntake] = power;
	//motor[RMogoIntake] = power;
}
