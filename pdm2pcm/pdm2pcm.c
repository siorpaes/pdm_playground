/** \file pdm2pcm.c
 * \author david.siorpaes@gmail.com
 *
 * Uses OpenPDM library to decode pdm data coming from standard input
 * and sends PCM data to standard output
 * Example usage:
 *
 * bzcat bellazio.txt.bz2 | ./txt2bin | ./pdm2pcm -f 1024000 -d128 | aplay -fS16_LE -c1 -r8000
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "OpenPDMFilter.h"

int main(int argc, char** argv)
{
	int opt, ret, dataCount;
	int finished = 0;
	unsigned int pdmSamplingF, decimationF, pcmSamplingF, pdmBufLen, pcmBufLen;
	uint8_t* pdmBuf;
	int16_t* pcmBuf;
	TPDMFilter_InitStruct filter;

	/* Get user options */
	pdmSamplingF = decimationF = 0;
	while((opt = getopt (argc, argv, "hf:d:")) != -1){
		switch(opt){
			case 'h':
				printf("%s -h(elp) -f <PDM sampling frequency> -d <decimation factor>\n", argv[0]);
				printf("Example usage: bzcat bellazio.txt.bz2 | ./txt2bin | ./pdm2pcm -f 1024000 -d128 | aplay -fS16_LE -c1 -r8000\n");
				exit(0);
				break;
				
			case 'f':
				pdmSamplingF = atoi(optarg);
				break;
				
			case 'd':
				decimationF = atoi(optarg);
				if(decimationF != 64 && decimationF != 128){
					fprintf(stderr, "Decimation factor must be 64 or 128\n");
					exit(-EINVAL);
				}
				break;

			case '?':
				if(optopt == 'f' || optopt == 'd'){
					fprintf(stderr, "Option %c requires argument\n", optopt);
					exit(-1);
				}
				break;
				
			default:
				break;
		}
	}

	if(decimationF == 0 || pdmSamplingF == 0){
		fprintf(stderr, "Must specify both PDM sampling frequency and decimation factor\n");
		exit(-EINVAL);
	}
	
	pcmSamplingF = pdmSamplingF/decimationF;

	/* Allocate buffers to contain 1ms worth of data */
	pdmBufLen = pdmSamplingF/1000;
	pcmBufLen = pdmBufLen/decimationF;
	pdmBuf = malloc(pdmBufLen/8);
	if(pdmBuf == NULL){
		fprintf(stderr, "Cannot allocate memory\n");
		exit(-ENOMEM);
	}

	pcmBuf = malloc(sizeof(int16_t)*pcmBufLen);
		if(pcmBuf == NULL){
		fprintf(stderr, "Cannot allocate memory\n");
		exit(-ENOMEM);
	}
	
	/* Initialize Open PDM library */
	filter.Fs = pcmSamplingF;
	filter.nSamples = pcmBufLen;
	filter.LP_HZ = pcmSamplingF/2;
	filter.HP_HZ = 10;
	filter.In_MicChannels = 1;
	filter.Out_MicChannels = 1;
	filter.Decimation = decimationF;
	Open_PDM_Filter_Init(&filter);

	while(finished == 0){
		/* Grab 1ms data from stdin */
		dataCount = 0;
		while((dataCount < pdmBufLen/8) && (finished == 0)){
			ret = read(STDIN_FILENO, pdmBuf + dataCount, pdmBufLen/8-dataCount);
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

		/* Decode PDM. Oldest PDM bit is MSB */
		Open_PDM_Filter_128(pdmBuf, pcmBuf, 1, &filter);

		/* Emit PCM decoded data to stdout */
		dataCount = 0;
		while(dataCount < sizeof(int16_t)*pcmBufLen){
			ret = write(STDOUT_FILENO, pcmBuf + dataCount, sizeof(int16_t)*pcmBufLen-dataCount);
			if(ret < 0){
				fprintf(stderr, "Error writing to STDOUT: %s\n", strerror(errno));
				exit(errno);
			}
		
			dataCount += ret;
		}
	}

	return 0;
}
