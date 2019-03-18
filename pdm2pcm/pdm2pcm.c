/** \file pdm2pcm.c
 * Uses OpenPDM library to decode pdm data coming from standard input
 * and sends PCM data to standard output
 * Usage:
 * bzcat bellazio.txt.bz2 | ./txt2bin | ./pdm2pcm | aplay -fS16_LE -c1 -r8000
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "OpenPDMFilter.h"

/* Open PDM library settings */
#define GAIN           (1)

#if 0
#define PDM_SAMPLING_F (1000000)
#define DECIMATION_F   (100)
#endif

#define PDM_SAMPLING_F (1024000)
#define DECIMATION_F   (128)
#define PCM_SAMPLING_F (PDM_SAMPLING_F/DECIMATION_F)

/* Buffer lengths in _samples_ */
#define PDM_BUFLEN (PDM_SAMPLING_F/1000)
#define PCM_BUFLEN (PDM_BUFLEN/DECIMATION_F)

uint8_t pdmBuf[PDM_BUFLEN/8];
int16_t pcmBuf[PCM_BUFLEN];

int main(int argc, char** argv)
{
	int ret, dataCount;
	int finished = 0;
	TPDMFilter_InitStruct filter;
	
	/* Initialize Open PDM library */
	filter.Fs = PCM_SAMPLING_F;
	filter.LP_HZ = PCM_SAMPLING_F/2;
	filter.HP_HZ = 10;
	filter.In_MicChannels = 1;
	filter.Out_MicChannels = 1;
	filter.Decimation = DECIMATION_F;
	Open_PDM_Filter_Init(&filter);

	while(finished == 0){
		/* Grab 1ms data from stdin */
		dataCount = 0;
		while((dataCount < PDM_BUFLEN/8) && (finished == 0)){
			ret = read(STDIN_FILENO, pdmBuf + dataCount, PDM_BUFLEN/8-dataCount);
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

#if 0
		uint8_t in, out;
		int i, j;
		for(i=0; i<PDM_BUFLEN/8; i++){
			in = pdmBuf[i];
			out = 0;
			for(j=0; j<8; j++)
				out |= (in>>j & 1) << (7-j);
			pdmBuf[i] = out;
		}
#endif
	
		/* Decode PDM */
		Open_PDM_Filter_128(pdmBuf, pcmBuf, GAIN, &filter);

		/* Emit PCM decoded data to stdout */
		dataCount = 0;
		while(dataCount < 2*PCM_BUFLEN){
			ret = write(STDOUT_FILENO, pcmBuf + dataCount, 2*PCM_BUFLEN-dataCount);
			if(ret < 0){
				fprintf(stderr, "Error writing to STDOUT: %s\n", strerror(errno));
				exit(errno);
			}
		
			dataCount += ret;
		}
	}

	return 0;
}
