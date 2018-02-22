typedef struct {
	int setPoint;

	float kp_p;
	float ki_p;
	float kd_p;

	float kp_n;
	float ki_n;
	float kd_n;

	int powerMax;
	int powerMin;

	int integralStart;
	float integral;

	int integralMin;
	int integralMax;

	int lastPoint;
} PID2;

int calc_PID(PID2 pid, int currentPoint);
