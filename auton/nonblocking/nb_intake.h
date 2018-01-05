int OPEN = 1;
int CLOSED = 0;

void nb_cone_intake(int state);
void nb_mogo_intake();

task nb_cone_intake_task();
task nb_mogo_intake_task();

settings coneIntake;
settings mogoIntake;
