typedef struct {
	int mogo_cones;
	int stago_cones;
	int lift_height;
	int vbar_height;
	int offset_up;
	int drop;
	int up;
	int stacked;
	int type;
} Autostack;

#define NONE 0
#define FIELD 1
#define MATCH 2
#define STAGO 3

Autostack autostack_state;

task autostack_control();
void autostack(int cone, int reset, bool blocking = true);
