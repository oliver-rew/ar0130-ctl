#include <unistd.h>                       //Needed for I2C port
#include <stdint.h>
#include <fcntl.h>                        //Needed for I2C port
#include <sys/ioctl.h>                    //Needed for I2C port
#include <linux/i2c-dev.h>                //Needed for I2C port
#include <linux/i2c.h>                    //Needed for I2C port
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//I2C bus
char *filename = (char*)"/dev/i2c-2";
int file_i2c;

int i2cWrite(uint16_t reg, uint16_t val);
int i2cDump();