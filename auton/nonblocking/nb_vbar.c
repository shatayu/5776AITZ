
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
	int error = vbar.target - SensorValue[TopLiftPot];
	int original_error = error;
	int timer = 0;

	while (sgn(error) == sgn(original_error) && timer < vbar.timeout) {
		error = vbar.target - SensorValue[TopLiftPot];
		b_vbar(vbar.power * sgn(error));
		timer += 20;
		wait1Msec(20);
	}

	b_vbar(-sgn(error) * BRAKE_POWER);
	wait1Msec(50);
	b_vbar(0);
}

bool already_init = false;
void init() {
	if(already_init) return;
	vbarPID.kp = 0.165;
	vbarPID.ki = 0.002;
	vbarPID.kd = 0.0006;
	vbarPID.totalCap = 127;
	vbarPID.integralCap = 40;
	already_init = true;
}

task nb_vbar_PID_task() {
	init();
	vbarPID.integral = 0;
	vbarPID.setPoint = vbar.target;

	const int stable_zone = 50;
	const int necessary_stable_epochs = 5;
	int consequtive_stable_epochs = 0;



	int timer = 0;
	while (timer < vbar.timeout) {
		int power = calc_PID(vbarPID, SensorValue[TopLiftPot]);
		int error = vbar.target - SensorValue[TopLiftPot];
		datalogDataGroupStart();
		datalogAddValue(1,power);
		datalogAddValue(2,error);
		datalogDataGroupEnd();
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
