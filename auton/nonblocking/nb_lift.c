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
	int error = lift.target - SensorValue[MainLiftPot];
	int original_error = error;
	int timer = 0;

	while (sgn(error) == sgn(original_error) && timer < lift.timeout) {
		error = lift.target - SensorValue[MainLiftPot];
		b_lift(lift.power * sgn(error));
		timer += 20;
		wait1Msec(20);
	}

	b_lift(-sgn(error) * BRAKE_POWER);
	wait1Msec(50);
	b_lift(0);
}

void nb_lift_PID_init() {
	static bool already_init = false;
	if(already_init) return;
	liftPID.kp = 0.25;
	liftPID.ki = 0.01;
	liftPID.kd = 0.4;
	liftPID.bias = 45;
	liftPID.powerMax = 127;
	liftPID.powerMin = -80;
	liftPID.integralMax = 25;
	liftPID.integralMin = -50;
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
		int power = calc_PID(liftPID, SensorValue[MainLiftPot]);
		int error = lift.target - SensorValue[MainLiftPot];

		b_lift(power);

		datalogDataGroupStart();
		datalogAddValue(1,power);
		datalogAddValue(2,error);
		datalogDataGroupEnd();
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
