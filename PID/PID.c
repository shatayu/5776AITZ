int min(int a, int b) {
	if(a<b) return a;
	return b;
}

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

	//prevent excessively abrupt stops
	int velocity = 0;
	if(nSysTime!=pid.lastTime) velocity = (currentPoint - pid.lastPoint)*1000/(nSysTime-pid.lastTime);
	if(abs(velocity) > 300 && sgn(power) != sgn(velocity) ) {
		power = sgn(power) * min(abs(power),20);
	}


	pid.lastPoint = currentPoint;
	pid.lastError = error;
	pid.lastTime = nSysTime;

	//datalogDataGroupStart();
	//	datalogAddValue(0,power);
	//	datalogAddValue(1,error);
	//	datalogAddValue(2,currentPoint);
	//	datalogAddValue(3,proportion);
	//	datalogAddValue(4,pid.integral);
	//	datalogAddValue(5,derivative);
	//datalogDataGroupEnd();

	return power;
}
