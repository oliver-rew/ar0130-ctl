#include "main.h"

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	printf("%x\n", regs[0].val);

	//i2cWrite(0x300a, 0xbabe);
	//i2cDump();
}

struct camReg {
	uint16_t reg;
	uint16_t val;
};

struct camReg regs[50] = {
{.reg = 0x1515 , .val = 0xffff}
}