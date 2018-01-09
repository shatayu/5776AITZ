int dt;
int calc_PID(PID pid, int currentPoint) {
	dt = nSystime - pid.lastTime;


	int error = pid.setPoint - currentPoint;

	float proportion = error * pid.kp;


	pid.integral += error * pid.ki;
	if(fabs(pid.integral) > pid.integralCap) pid.integral = sgn(pid.integral) * pid.integralCap;

	float derivative = (error - pid.lastError)*pid.kd;

	int power = proportion + pid.integral + derivative;
	if(fabs(power) > pid.totalCap) power = sgn(power) * pid.totalCap;

	pid.lastError = error;
	pid.lastTime = nSysTime;
	return power;
}
