void nb_set_lift_settings(int target, int power, int timeout) {
	lift.target = target;
	lift.power = power;
	lift.timeout = timeout;
}

void nb_lift(int target, int power, int timeout) {
	nb_set_lift_settings(target, power, timeout);
	startTask(nb_lift_task);
}

void nb_lift_PID(int target, int power, int timeout) {
	nb_set_lift_settings(target, power, timeout);
	startTask(nb_lift_PID_task);
}

task nb_lift_task() {
	// config
	int power = abs(lift.power) * sgn(lift.target - sget_lift(SENSOR)); // corrects the sign
	clearTimer(T1);

	// powers the lift
	b_lift(power);

	// waits until either the target is reached or the timeout has been hit
	if (power > 0) {
		waitUntil(lift.target < sget_lift(SENSOR) || time1[T1] > lift.timeout);
	} else {
		waitUntil(lift.target > sget_lift(SENSOR) || time1[T1] > lift.timeout);
	}

	// stopping
	//b_lift(-sgn(power) * 30);
	//wait1Msec(50);
	b_lift(0);
}

void nb_lift_PID_init() {
	static bool already_init = false;
	liftPID.lastPoint = sget_lift(SENSOR);
	if(already_init) return;
	liftPID.kp = 0.27;
	liftPID.ki = 0.01;
	liftPID.kd = 2.3;
	liftPID.bias = 15;
	liftPID.powerMax = 127;
	liftPID.powerMin = -127;
	liftPID.integralMax = 25;
	liftPID.integralMin = -25;
	already_init = true;
}

task nb_lift_PID_task() {
	nb_lift_PID_init();

	liftPID.integral = 0;
	liftPID.setPoint = lift.target;

	const int stable_zone = 50;
	const int necessary_stable_epochs = 5;
	int consequtive_stable_epochs = 0;


	int timer = 0;
	while (timer < lift.timeout) {
		int power = calc_PID(liftPID, sget_lift(SENSOR));
		int error = lift.target - sget_lift(SENSOR);
		b_lift(power);

		/*
		disable epoch stability test for testing
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

	b_lift(0);
}
