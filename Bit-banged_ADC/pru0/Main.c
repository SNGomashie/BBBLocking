//  Attempt to read the
//  SPI ADC read program in C.
//
//	Pin configuration:
//  nRD (  Read Input ) :						P9.25 pr1_pru0_pru_r30_7
//  CS	( chip select ):  					P9.27 pr1_pru0_pru_r30_5
//  SDO ( Serial Data Out (MISO)):  P9.28 pr1_pru0_pru_r31_3
//  SDI ( Serial Data In (MOSI)):   P9.29 pr1_pru0_pru_r30_1
//  SCK ( Serial clock ) :      		P9.30 pr1_pru0_pru_r30_2
//  Convst (  Start conversion ) : 	P9.31 pr1_pru0_pru_r30_0

//Define pin locations
#define NRD 7
#define CS 5
#define MISO 3
#define MOSI 1
#define CLK 2
#define CONVST 0

#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table.h"

volatile register uint32_t __R30;
volatile register uint32_t __R31;

uint16_t spiCommand = 0x00000000;
uint16_t spiReceive = 0x00000000;

uint8_t i;


void main(void)
{


	/* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

	spiCommand = ( 0 << 4 ) | 0b10000000;

	__R30 = 0x00000000;         //  Clear the output pin.
	__R31 = 0x00000000;		  //  Clear the input pin.
	__R30 |= (0 << CS);  // Initialize chip select LOW.
	__R30 |= (0 << NRD); // Initialize Read input LOW.
	__R30 |= (1 << CONVST); //Initialize conversion start HIGH.

	while(1){
		__R30 |= (1 << CS); //Set CS high
		__R30 |= (0 << NRD); //Set nRD low
		__R30 |= (0 << CONVST); //Set ConvST low

		__R30 |= (0 << CLK);

		for (i = 0; i < 16; i++){
			spiReceive = spiReceive << 1; //shift

			if(spiCommand & (1 << i)) //write the command
				__R30 = ( 1 << MOSI );
			else
				__R30 = ( 0 << MOSI );

			__R30 = ( 1 << CLK ); //Rising edge Γ

			if (__R31 & ( 1 << MISO )) { //Save MISO
				spiReceive = 0x01;
			} else {
				spiReceive = 0x00;
			}
			__R30 = ( 0 << CLK ); //Falling edge Լ
		}
		__R30 |= ( 1 << NRD );
		__R30 |= ( 1 << CONVST );
		__R30 |= ( 0 << CS );
	}
__delay_cycles(200000000);

}
