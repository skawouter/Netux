typedef struct {
	unsigned int type;
	unsigned int name;
	char number;
	char minornumber;
	unsigned int open, close, write,read;
} thisdev;

void init_devices(void);
