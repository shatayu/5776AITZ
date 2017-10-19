// conesOnMogo = cones CURRENTLY ON MOGO BEFORE NEW ONE IS STACKED ON
void autoStack(int conesOnMogo) {
	if (conesOnMogo == 0) {
		clawStall(true);
		while (SensorValue[LiftPot] < 3300) {
			moveTopLift(127);
		}
		moveTopLift(0);
	}
}
