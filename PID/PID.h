typedef struct {
	int setPoint;

	float kp;
	float ki;
	float kd;

	int totalCap;

	float integral;
	int integralCap;

	int lastError;

	long lastTime;
} PID;

int calc_PID(PID pid, int currentPoint);
