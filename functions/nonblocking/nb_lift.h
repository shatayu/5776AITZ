settings lift;
PID liftPID;

void nb_lift(int target, int power, int timeout);
void nb_lift_PID(int target, int power, int timeout);

task nb_lift_task();
task nb_lift_PID_task();
