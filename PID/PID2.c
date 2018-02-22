
int calc_PID(PID2 pid, int currentPoint) {


	int error = pid.setPoint - currentPoint;
	int neg_dPower = -(currentPoint-pid.lastPoint); //dE/dt = -dP/dt and doesn't jerk with changes in setPoint

	float proportion, derivative;

	if(error > 0) {
		proportion = error * pid.kp_p;
		pid.integral += error * pid.ki_p;
		derivative = neg_dPower*pid.kd_p;
	}

	if(error < 0) {
		proportion = error * pid.kp_n;
		pid.integral += error * pid.ki_n;
		derivative = neg_dPower*pid.kd_n;
	}


	if(pid.integral > pid.integralMax) pid.integral = pid.integralMax;
	if(pid.integral < pid.integralMin) pid.integral = pid.integralMin;


	//back calculate maximum/minimum integral value that causes power to change within bounds
	//int partialPower = proportion + derivative;
	//int remainingPower;
	//if(partialPower < pid.powerMin) partialPower = pid.powerMin;
	//if(partialPower > pid.powerMax) partialPower = pid.powerMax;

	//if(partialPower > 0) remainingPower = pid.powerMax - partialPower;
	//if(partialPower < 0) remainingPower = pid.powerMin - partialPower;

	//if(pid.integral < 0 && pid.integral < remainingPower) pid.integral = remainingPower;
	//if(pid.integral > 0 && pid.integral > remainingPower) pid.integral = remainingPower;
	//end back calc
	if(proportion < pid.powerMin || proportion > pid.powerMax) pid.integral = 0;


	int power = proportion + pid.integral + derivative;
	if(power > pid.powerMax) power = pid.powerMax;
	if(power < pid.powerMin) power = pid.powerMin;

	pid.lastPoint = currentPoint;
	return power;
}
