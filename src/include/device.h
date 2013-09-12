typedef struct {
	unsigned int type;
	unsigned int name;
	char number;
	char minornumber;
	unsigned int (*open), (*close), (*write),(*read);
} devstruct;

void init_devices(void);

typedef unsigned char   uint8;
typedef unsigned short  uint16;
typedef unsigned int    uint32;
typedef unsigned long   uint64;
typedef unsigned long   size_t;
typedef signed char             int8;
typedef signed short    int16;
typedef signed int              int32;
typedef signed long             int64;

