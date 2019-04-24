#ifndef __LTC_1859_H_
#define __LTC_1859_H_

#include <sys_mcspi.h>

/* Define pin locations */
#define CS      7
#define _RD     1
#define _BUSY   0
#define CONVST  5

const uint8_t ADCch[] = {0, 4, 1, 5, 2, 6, 3, 7};

void LTC1859initialize(void);

uint16_t LTC1859singletransfer(uint8_t chan);

// void LTC1859multitransfer(uint8_t chan, uint8_t );

#endif
