struct ata_dev{
	int iobus;
	int control;
	int slave;
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

