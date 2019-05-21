/** \file packdata.c
 * Packs PDM data produced by fx2grabber
 * Usage:
 * ./packdata 0 < ~/InData_0_0.dat | ./pdm2pcm  -f 2048000 -d128 | aplay -fS16_LE -c1 -r 16000
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int channel;
int swapBits = 1;

#define BUFLEN (2048)
uint8_t inBuf[BUFLEN];
uint8_t outBuf[BUFLEN/8];

int packData(uint8_t* inBuffer, uint8_t* outBuffer, int buflen)
{
	uint8_t val8;
	int i, bitn;

	for(i=0; i<buflen/8; i++){
		val8 = 0;
		for(bitn=0; bitn<8; bitn++){
			if(swapBits)
				val8 |= ((inBuffer[8*i + bitn] >> channel & 1 ) << (7-bitn));
			else
				val8 |= ((outBuffer[8*i + bitn] >> channel & 1 ) << (bitn));
		}

		outBuffer[i] = val8;
	}

	return 0;
}


int main(int argc, char** argv)
{
	int ret, dataCount;
	int finished = 0;

	channel = atol(argv[1]);
	fprintf(stderr, "Converting channel %i\n", channel);
	
	while(finished == 0){
		/* Grab 1ms data from stdin */
		dataCount = 0;
		while((dataCount < BUFLEN) && (finished == 0)){
			ret = read(STDIN_FILENO, inBuf + dataCount, BUFLEN-dataCount);
			if(ret < 0){
				fprintf(stderr, "Error reading from STDIN: %s\n", strerror(errno));
				exit(errno);
			}

			if(ret == 0){
				fprintf(stderr, "Decoding complete!\n");
				finished = 1;
			}

			dataCount += ret;
		}

		/* Pack PDM */
		packData(inBuf, outBuf, BUFLEN);

		/* Emit packed data to stdout */
		dataCount = 0;
		while(finished == 0 && dataCount < BUFLEN/8){
			ret = write(STDOUT_FILENO, outBuf + dataCount, BUFLEN/8-dataCount);
			if(ret < 0){
				fprintf(stderr, "Error writing to STDOUT: %s\n", strerror(errno));
				exit(errno);
			}
		
			dataCount += ret;
		}
	}
}


