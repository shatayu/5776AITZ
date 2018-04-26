settings vbar;
PID vbarPID;
int vbarPIDlastTime;

bool nb_vbar_running();

void nb_vbar(int target, int power, int timeout);
void nb_vbar_PID(int target, int power, int timeout);

task nb_vbar_task();
task nb_vbar_PID_task();
