typedef struct {
	unsigned int type;
	unsigned int name;
	char number;
	char minornumber;
	unsigned int (*open), (*close), (*write),(*read);
} devstruct;

void init_devices(void);
