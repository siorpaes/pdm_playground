/** \file txt2bin.c
 * \author david.siorpaes@gmail.com
 *
 * Converts 1-bit PDM ASCII audio data to 8 bit binary.
 * Input data can be easily created using Saleae logic analyzer
 * Usage:
 *
 * pdm2pcm8bit < pdm.txt > pdm.dat
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	int val;
	uint8_t val8;
 	int ret, bitn, dataWritten;

	ret = 1;
	bitn = 0;

	while(ret == 1){
		val8 = 0;
		for(bitn=0; bitn<8; bitn++){
			ret = fscanf(stdin, "%i", &val);

			/* OpenPDM format: MSB is oldest PDM bit */
			val8 |= (val << (7-bitn));
		}

		dataWritten = write(1, &val8, 1);
		if(dataWritten != 1){
			printf("Error writing to standard output\n");
			exit(-1);
		}
	}
   
	return 0;
}
