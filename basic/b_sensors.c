int sget_lift(int value) {
	// bounds of lift motion (based on actual pot)
	int min = 1800; // with mogo out
	int max = 4095;

	if (value == MIN) {
		return min;
	} else if (value == MAX) {
		return max;
	} else {
		// returns distance from minimum value - these stay constant even if the pot is remounted
		int raw = SensorValue[MainLiftPot];
		int adjusted = raw - min;
		return adjusted;
	}
}

int sget_vbar(int value) {
	// bounds of vbar motion (based on actual pot)
	int min = 0;
	int max = 4095;

	if (value == MIN) {
		return min;
	} else if (value == MAX) {
		return max;
	} else {
		// returns distance from minimum value - these stay constant even if the pot is remounted
		int raw = SensorValue[TopLiftPot];
		int adjusted = raw - min;
		return adjusted;
	}
}

int sget_mogo(int value) {
	// bounds of mogo motion (based on actual pot)
	int min = 0;
	int max = 4095;

	if (value == MIN) {
		return min;
	} else if (value == MAX) {
		return max;
	} else {
		// returns distance from minimum value - these stay constant even if the pot is remounted
		int raw = SensorValue[MogoPot];
		int adjusted = raw - min;
		return adjusted;
	}
}

int sget_trigger() {
	int raw = SensorValue[stackTrigger];
	return raw;
}

int sget_encoder() {
	int raw = SensorValue[LEncoder];
	return raw;
}
void zero_encoder() {
	SensorValue[LEncoder] = 0;
}

int sget_gyro() {
	int raw = SensorValue[Gyro];
	return raw;
}

void zero_gyro() {
	SensorValue[Gyro] = 0;
}

int sget_l_ultrasonic() {
	int raw = SensorValue[LUltrasonic];
	return raw;
}

int sget_r_ultrasonic() {
	int raw = SensorValue[RUltrasonic];
	return raw;
}
