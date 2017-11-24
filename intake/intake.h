bool OPEN = true;
bool CLOSED = false;

typedef struct {
	int power;
	bool state;
	int timeout;
} Intake;

void moveConeIntake(int power);
task autonConeIntake();
void moveMogoIntake(int power);
task autonMogoIntake();

Intake coneIntake;
Intake mogoIntake;
