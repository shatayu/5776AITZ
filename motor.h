void moveDrive (int left, int right) {
	motor[FRDrive] = right;
	motor[CRDrive] = right;
	motor[BRDrive] = right;

	motor[FLDrive] = left;
	motor[CLDrive] = left;
	motor[BLDrive] = left;
}

void moveLift (int power) {
	motor[LLift] = power;
	motor[RLift] = power;
}
