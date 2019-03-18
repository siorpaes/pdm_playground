/** \file pdm2pdm8bit.c
 * Converts 1-bit PDM ASCII audio data to 8 bit binary
 * Usage: pdm2pcm8bit < pdm.txt > pdm.dat
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	int val;
	uint8_t val8;
 	int ret, bitn;

	ret = 1;
	bitn = 0;

	while(ret == 1){
		val8 = 0;
		for(bitn=0; bitn<8; bitn++){
			ret = fscanf(stdin, "%i", &val);
			val8 |= (val << (7-bitn));
		}

		write(1, &val8, 1);
	}
   
	return 0;
}
