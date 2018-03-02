#define BRAKE_POWER 30
#define BRAKE_TIME 50

//power's sign determines direction
//target given in encoder ticks
void bl_drive(int target, int timeout, int power, bool brake = true);
//target given in tenths of a degree
void bl_drive_rotate(int target, int timeout, int power);

//direction given as the direction the robot was moving in. motors will move at -direction to brake
void bl_drive_brake(int direction);
void bl_drive_rotate_brake(int direction);
