#include "camera-i2c.h"

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	i2cWrite(0x300a, 0xbabe);
	i2cDump();
}

int i2cDump()
{

	if ((file_i2c = open(filename, O_RDWR)) < 0)
	{
		//ERROR HANDLING: you can check errno to see what went wrong
		printf("Failed to open the i2c bus");
		return 1;
	}

	//acquire i2c bus
	int addr = 0x10; //<<<<<The I2C address of the slave
	if (ioctl(file_i2c, I2C_SLAVE, addr) < 0)
	{
		printf("Failed to acquire bus access and/or talk to slave.\n");
		//ERROR HANDLING; you can check errno to see what went wrong
		return 1;
	}

	struct i2c_rdwr_ioctl_data msgset;
	struct i2c_msg iomsg[2];
	uint8_t buf[2];
	uint8_t reg[2];
	int rc;

	for (uint16_t i = 0x3000; i <= 0x31FC; i += 0x02)
	{
		//set address
		reg[0] = i >> 8;
		reg[1] = i & 0x00ff;

		//message that sends the register to read
		iomsg[0].addr = addr;
		iomsg[0].flags = 0; //no flags means write the contents of buf
		iomsg[0].buf = reg;
		iomsg[0].len = 2; //num bytes to write

		//message that reads back the data
		iomsg[1].addr = addr;
		iomsg[1].flags = I2C_M_RD; //read data
		iomsg[1].buf = buf;
		iomsg[1].len = 2;

		msgset.msgs = iomsg;
		msgset.nmsgs = 2;

		rc = ioctl(file_i2c, I2C_RDWR, &msgset);
		if (rc < 0)
			printf("ioctl error return code %d \n", rc);

		uint16_t val = (buf[0] << 8) | buf[1];

		printf("addr 0x%x : val = 0x%04x\n", i, val);
	}
}

int i2cWrite(uint16_t reg, uint16_t val)
{

	if ((file_i2c = open(filename, O_RDWR)) < 0)
	{
		//ERROR HANDLING: you can check errno to see what went wrong
		printf("Failed to open the i2c bus");
		return 1;
	}

	//acquire i2c bus
	int addr = 0x10; //<<<<<The I2C address of the slave
	if (ioctl(file_i2c, I2C_SLAVE, addr) < 0)
	{
		printf("Failed to acquire bus access and/or talk to slave.\n");
		//ERROR HANDLING; you can check errno to see what went wrong
		return 1;
	}

	struct i2c_rdwr_ioctl_data msgset;
	struct i2c_msg iomsg[2];
	uint8_t r[4];
	int rc;

	//set address(0,1) and data (2,3)
	r[0] = reg >> 8;
	r[1] = reg & 0x00ff;
	r[2] = val >> 8;
	r[3] = val & 0x00ff;

	//message that sends the register to read
	iomsg[0].addr = addr;
	iomsg[0].flags = 0; //no flags means write the contents of buf
	iomsg[0].buf = r;
	iomsg[0].len = 4; //num bytes to write

	msgset.msgs = iomsg;
	msgset.nmsgs = 1;

	rc = ioctl(file_i2c, I2C_RDWR, &msgset);
	if (rc < 0)
		printf("ioctl error return code %d \n", rc);

	printf("Finished Write\n");
}

uint16_t i2cRead(uint16_t reg)
{
	if ((file_i2c = open(filename, O_RDWR)) < 0)
	{
		//ERROR HANDLING: you can check errno to see what went wrong
		printf("Failed to open the i2c bus");
		return -1;
	}

	//acquire i2c bus
	int addr = 0x10; //<<<<<The I2C address of the slave
	if (ioctl(file_i2c, I2C_SLAVE, addr) < 0)
	{
		printf("Failed to acquire bus access and/or talk to slave.\n");
		//ERROR HANDLING; you can check errno to see what went wrong
		return -1;
	}

	struct i2c_rdwr_ioctl_data msgset;
	struct i2c_msg iomsg[2];
	uint8_t buf[2];
	uint8_t r[2];
	int rc;

	r[0] = reg >> 8;
	r[1] = reg & 0x00ff;

	//message that sends the register to read
	iomsg[0].addr = addr;
	iomsg[0].flags = 0; //no flags means write the contents of buf
	iomsg[0].buf = r;
	iomsg[0].len = 2; //num bytes to write

	//message that reads back the data
	iomsg[1].addr = addr;
	iomsg[1].flags = I2C_M_RD; //read data
	iomsg[1].buf = buf;
	iomsg[1].len = 2;

	//set the message
	msgset.msgs = iomsg;
	msgset.nmsgs = 2;

	rc = ioctl(file_i2c, I2C_RDWR, &msgset);
	if (rc < 0) 
	{
		printf("ioctl error return code %d \n", rc);
		return -1;
	}

	uint16_t val = (buf[0] << 8) | buf[1];

	return val;

}