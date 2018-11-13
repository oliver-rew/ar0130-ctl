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

#include "camera-i2c.h"