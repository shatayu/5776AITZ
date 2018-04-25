void nb_set_vbar_settings(int target, int power, int timeout) {
	vbar.target = target;
	vbar.power = power;
	vbar.timeout = timeout;
}

void nb_vbar(int target, int power, int timeout) {
	nb_set_vbar_settings(target, power, timeout);
	startTask(nb_vbar_task);
}

void nb_vbar_PID(int target, int power, int timeout) {
	nb_set_vbar_settings(target, power, timeout);
	startTask(nb_vbar_PID_task);
}

task nb_vbar_task() {
	// config
	int power = abs(vbar.power) * sgn(vbar.target - sget_vbar(SENSOR)); // corrects the sign
	clearTimer(T2);

	// powers the vertibar
	b_vbar(power);

	// waits until either the target is reached or the timeout has been hit
	if (power > 0) {
		waitUntil(vbar.target < sget_vbar(SENSOR) || time1[T2] > vbar.timeout);
	} else {
		waitUntil(vbar.target > sget_vbar(SENSOR) || time1[T2] > vbar.timeout);
	}

	// brake the vertibar
	b_vbar(-sgn(power) * BRAKE_POWER);
	wait1Msec(50);
	b_vbar(0);
}

void nb_vbar_PID_init() {
	static bool already_init = false;
	if(already_init) return;
	vbarPID.kp = 0.25; // used to be 0.18
	vbarPID.ki = 0.002;
	vbarPID.kd = 2;//old 1.5
	vbarPID.powerMax = 127;
	vbarPID.powerMin = -127;
	vbarPID.integralMax = 40;
	vbarPID.integralMin = -40;
	already_init = true;
}

task nb_vbar_PID_task() {
	nb_vbar_PID_init();
	vbarPID.integral = 0;
	vbarPID.setPoint = vbar.target;

	const int stable_zone = 50;
	const int necessary_stable_epochs = 5;
	int consequtive_stable_epochs = 0;



	int timer = 0;
	while (timer < vbar.timeout) {
		int power = calc_PID(vbarPID, sget_vbar(SENSOR));
		int error = vbar.target - sget_vbar(SENSOR);

		b_vbar(power);

		/*
		disable epoch stability test for testing
		int error = vbar.target - SensorValue[TopLiftPot];
		if(abs(error) <= stable_zone) {
			consequtive_stable_epochs++;
		} else {
			consequtive_stable_epochs = 0;
		}
		if(consequtive_stable_epochs >= necessary_stable_epochs) break;
		*/

		timer += 20;
		wait1Msec(20);
	}

	b_vbar(0);
}
