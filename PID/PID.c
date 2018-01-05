
int calc_PID(PID pid, int currentPoint) {
	int error = pid.setPoint - currentPoint;

	float proportion = error * pid.kp;

	pid.integral += error * pid.ki;
	if(fabs(pid.integral) > pid.integralCap) pid.integral = sgn(pid.integral) * pid.integralCap;

	float derivative = (error - pid.lastError)*pid.kd;

	int power = proportion + pid.integral + derivative;
	if(fabs(power) > pid.totalCap) power = sgn(power) * pid.totalCap;

	return power;
}
