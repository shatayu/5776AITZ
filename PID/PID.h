typedef struct {
	int setPoint;

	float kp;
	float ki;
	float kd;

	int bias;

	int powerMax;
	int powerMin;

	float integral;

	int integralMin;
	int integralMax;

	int lastError;
	int lastPoint;
	long lastTime;
} PID;

int calc_PID(PID pid, int currentPoint);
