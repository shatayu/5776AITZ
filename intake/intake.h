int OPEN = 1;
int CLOSED = 0;

typedef struct {
	int power;
	int state;
	int timeout;
} Intake;

void moveConeIntake(int power);
task autonConeIntake();
void moveMogoIntake(int power);
task autonMogoIntake();

Intake coneIntake;
Intake mogoIntake;
