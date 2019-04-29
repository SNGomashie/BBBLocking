/* includes */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <pru_intc.h>
#include <pru_cfg.h>
#include "resource_table.h"

/* PRU definiton */
#define PRU0
#define DEBUG_PIN 3
/* Interrupt definitions */
#define INT_OFF 0x00000000
#define INT_ON 0xFFFFFFFF

/* GPIO registers */
volatile register unsigned int __R30;
volatile register unsigned int __R31;

/* Shared memory location & definiton*/
#define SHARE_MEM  0x00010000
volatile uint32_t *shared =  (unsigned int *) SHARE_MEM;


void main(void) {
	static unsigned int data = 0;
	data++;
	unsigned int* dataPtr = &data;

	shared[0] = INT_OFF;

/* Infinite loop */
	while(1) {
		data = 0xF0F00F0F;
		while(shared[0] == INT_OFF){
			__R30 ^= (1 << DEBUG_PIN);
			/* Send interrupt over shared memory */
			shared[0] = INT_ON;

			/* Send data object through the scratchpad */
			__xout(10, 0, 0, dataPtr);
			__R30 ^= (1 << DEBUG_PIN);

		}
	}
}
