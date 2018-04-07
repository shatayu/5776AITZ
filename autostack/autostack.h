typedef struct {
	int mogo_cones;
	int stago_cones;
	int lift_height;
	int vbar_height;
	int drop;
	bool stacked;
	int type;
} Autostack;

#define NONE 0
#define FIELD 1
#define MATCH 2
#define STAGO 3

Autostack autostack_state;
