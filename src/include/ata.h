typedef struct {
	unsigned short int flags;
	unsigned short int unused1[9];
	char     serial[20];
	unsigned short int unused2[3];
	char     firmware[8];
	char     model[40];
	unsigned short int sectors_per_int;
	unsigned short int unused3;
	unsigned short int capabilities[2];
	unsigned short int unused4[2];
	unsigned short int valid_ext_data;
	unsigned short int unused5[5];
	unsigned short int size_of_rw_mult;
	unsigned long int sectors_28;
	unsigned short int unused6[38];
	unsigned long long int  sectors_48;
	unsigned short int unused7[152];
} __attribute__((packed)) ata_identify_t;

struct ata_dev{
	int iobus;
	int control;
	int slave;
	ata_identify_t identity;
};
static struct ata_dev primary_master = {.iobus = 0x1F0, .control = 0x3F6,
.slave=0};
static struct ata_dev primary_slave = {.iobus = 0x1F0, .control = 0x3F6,
.slave=1};
static struct ata_dev secondary_master = {.iobus = 0x170, .control =
0x3F6, .slave=0};
static struct ata_dev secondary_slave = {.iobus = 0x170, .control =
0x3F6, .slave=1};

void ata_soft_reset(struct ata_dev *dev);
void ata_init();

