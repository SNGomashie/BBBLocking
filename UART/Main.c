// Access the CYCLE and STALL registers
// devmem2 0x4A32200C - PRU0 CTRl register 0x4A322000 - offset cycle register 0x000C
#include <stdint.h>
#include <pru_cfg.h>
#include <pru_ctrl.h>
#include <pru_uart.h>
#include "resource_table.h"

#define out 1       // Bit number to output on

volatile register unsigned int __R30;
volatile register unsigned int __R31;

void main(void) {
}
