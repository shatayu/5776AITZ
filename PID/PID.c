int dt;
int calc_PID(PID pid, int currentPoint) {
	dt = nSysTime - pid.lastTime;


	int error = pid.setPoint - currentPoint;

	float proportion = error * pid.kp;


	pid.integral += error * pid.ki;
	if(pid.integral > pid.integralMax) pid.integral = pid.integralMax;
	if(pid.integral < pid.integralMin) pid.integral = pid.integralMin;

	//if(sgn(pid.lastError) != sgn (error)) pid.integral = (pid.integral*2)/3;
	if(sgn(error) != sgn (pid.integral) && abs(error) >=1 ) pid.integral = (pid.integral*2)/3;
	if(proportion < pid.powerMin || proportion > pid.powerMax) pid.integral = 0;

	float derivative = (error - pid.lastError)*pid.kd;

	int power = proportion + pid.integral + derivative + pid.bias;
	if(power > pid.powerMax) power = pid.powerMax;
	if(power < pid.powerMin) power = pid.powerMin;

	pid.lastError = error;
	pid.lastTime = nSysTime;

	//datalogDataGroupStart();
	//	datalogAddValue(0,power);
	//	datalogAddValue(1,error);

	//	datalogAddValue(3,proportion);
	//	datalogAddValue(4,pid.integral);
	//	datalogAddValue(5,derivative);
	//datalogDataGroupEnd();

	return power;
}
