#include "main.h"
#include "regs.h"
#include "camera-i2c.h"

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	for (int i = 0; i < 120; ++i)
	{
		printf("reg = 0x%04x, val = 0x%04x\n", regs[i].reg, regs[i].val);
		//i2cWrite(regs[i].reg, regs[i].val);
	}
	//printf("%x\n", regs[1].val);

	//i2cWrite(0x300a, 0xbabe);
	i2cDump();
}
