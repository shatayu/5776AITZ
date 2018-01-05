
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

task nb_lift_PID_task() {
	liftPID.kp = 0;
	liftPID.ki = 0.001;
	liftPID.kd = 0;

	liftPID.totalCap = 127;
	liftPID.integralCap = 30;

	liftPID.setPoint = lift.target;

	const int stable_zone = 50;
	const int necessary_stable_epochs = 5;
	int consequtive_stable_epochs = 0;


	int timer = 0;
	while (timer < lift.timeout) {
		b_lift(calc_PID(liftPID, SensorValue[MainLiftPot]));

		int error = lift.target - SensorValue[MainLiftPot];
		if(abs(error) <= stable_zone) {
			consequtive_stable_epochs++;
		} else {
			consequtive_stable_epochs = 0;
		}
		if(consequtive_stable_epochs >= necessary_stable_epochs) break;


		timer += 20;
		wait1Msec(20);
	}

	b_lift(0);
}
