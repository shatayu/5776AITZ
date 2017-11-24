typedef struct {
	int target;
	int power;
	int timeout;
} Lift;

void moveMainLift(int power);
task autonMainLift();
task mainLiftPI();

void moveTopLift(int power);
task autonTopLift();
task topLiftPI();

Lift mainLift;
Lift topLift;
