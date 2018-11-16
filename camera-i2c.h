//I2C bus

/*
char *filename = (char *)"/dev/i2c-2";
int file_i2c;
*/

int i2cWrite(uint16_t reg, uint16_t val);
int i2cDump();
uint16_t i2cRead(uint16_t reg);


