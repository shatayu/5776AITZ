#define INTAKE 1
#define NEUTRAL 0
#define OUTTAKE -1

#define ON true
#define OFF false

void nb_cone_intake(int state);
void nb_mogo_intake(int target, int power, int timeout);

task nb_cone_intake_task();
task nb_mogo_intake_task();

settings cone_intake;
settings mogo_intake;
