/** \file fx2grabber.c
 * \author david.siorpaes@gmail.com
 *
 * Reads 8-bit parallel data from Cypress FX2LP development board.
 * Dumps to standard output data grabbed by Fx2LP. A data decimation factor can be specified.
 * Optionally, it is possible to extract just one of the eight channels, pack it in 8 bits and emit it.
 *
 * See Cypress application note AN58069 for Fx2LP firmware
 * Usage:
 *
 * ./fx2grabber -d8 > data.dump
 * ./fx2grabber -p -s -d8 -c0 | ../pdm2pcm/pdm2pcm | aplay -fS16_LE -c1 -r7812
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <errno.h>
#include <libusb-1.0/libusb.h>
#include "fx2grabber.h"

#define BUFLEN (16*1024)

/* Max number of USB pending transfers */
#define N_TRANSFERS 12
struct usbTransfer usbTransfers[N_TRANSFERS];

sem_t semaphore;
unsigned char* outBuffer;
unsigned char* outBufferDec;

/* Application parameters */
int decimation, packed, channel, swapBits;


/**
 * \brief Transforms raw data acquired by FX2LP in data to be emitted according to user preferences
 * \param buffer Raw data from Fx2LP
 * \param decBuffer Data to be emitted
 * \param buflen Input buffer length
 */
int packData(unsigned char* buffer, unsigned char* decBuffer, int buflen)
{
	unsigned char val8;
	int i, bitn;

	/* Skip N bytes */
	for(i=0; i<buflen/decimation; i+=decimation){
		val8 = 0;
		for(bitn=0; bitn<8; bitn++){
			if(swapBits)
				val8 |= ((buffer[i*decimation + 8*bitn] >> channel & 1 ) << (7-bitn));
			else
				val8 |= ((buffer[i*decimation + 8*bitn] >> channel & 1 ) << (bitn));
		}

		decBuffer[i/decimation] = val8;
	}
	
	return 0;
}

/** Data Output thread
 */
void* dataOut(void* arg)
{
	int ret, flags, i, j, decbuflen;
	unsigned int dataWritten;
	char del[3] = {'\b', ' ', '\b'};

	/* Set non-blocking IO */
	flags = fcntl(STDOUT_FILENO, F_GETFL);
	fcntl(STDOUT_FILENO, F_SETFL, flags | O_NONBLOCK);

	decbuflen = BUFLEN/decimation;
	if(packed)
		decbuflen /= 8;

	while(1){
		sem_wait(&semaphore);

		if(packed){
			packData(outBuffer, outBufferDec, BUFLEN);
		}
		else{
			for(i=0, j=0; i<BUFLEN; i+=decimation)
				outBufferDec[j++] = outBuffer[i];
		}
		
		/* Dump buffer to STDOUT */
		dataWritten = 0;
		while(dataWritten < decbuflen){
			ret = write(STDOUT_FILENO, outBufferDec + dataWritten, decbuflen-dataWritten);
			if(ret < 0){
				fprintf(stderr, "Error writing to STDOUT: %s\n", strerror(errno));
				exit(errno);
			}

			if(ret != decbuflen)
				fprintf(stderr, "D");

			dataWritten += ret;
		}

		/* Done with buffer: delete marker */
		ret = write(STDERR_FILENO, &del, 3);
	}
}



void callbackUSBTransferComplete(struct libusb_transfer* xfr)
{
	char asterisk = '*';
	int ret;
	
	switch(xfr->status)
	{
		case LIBUSB_TRANSFER_COMPLETED:

			/* Hand over data to data-output thread */
			memcpy(outBuffer, xfr->buffer, xfr->actual_length);
			sem_post(&semaphore);

			/* Repost transfer */
			if(libusb_submit_transfer(xfr) < 0){
				libusb_free_transfer(xfr);
				fprintf(stderr, "Error in submitting USB transfer\n");
				exit(1);
			}
			
			ret = write(STDERR_FILENO, &asterisk, 1);
			if(ret != 1)
				fprintf(stderr, "Error in writing asterisk\n");

			break;
			
		case LIBUSB_TRANSFER_CANCELLED:
		case LIBUSB_TRANSFER_NO_DEVICE:
		case LIBUSB_TRANSFER_TIMED_OUT:
		case LIBUSB_TRANSFER_ERROR:
		case LIBUSB_TRANSFER_STALL:
		case LIBUSB_TRANSFER_OVERFLOW:
			break;
	}
}


int main(int argc, char** argv)
{
	libusb_context* ctx;
	libusb_device_handle* handle;
	struct libusb_transfer* xfr;
	unsigned char* buf;
	pthread_t dataOutThread;
	int i, ret, arg, opt;
	char asterisk = '*';

	/* Parse options */
	while((opt = getopt (argc, argv, "hpsd:c:")) != -1){
		switch(opt){
			case 'h':
				printf("%s -h(elp) -d <decimation> -p(acked) -c <channel> -s(wap bits)\n", argv[0]);
				exit(0);
				break;

			case 'd':
				decimation = atoi(optarg);
				break;

			case 'c':
				channel = atoi(optarg);
				break;

			case 's':
				swapBits = 1;
				break;

			case 'p':
				packed = 1;
				break;

			case '?':
				if(optopt == 'd' || optopt == 'c'){
					printf("Options -d and -c require an argument\n");
					exit(-1);
				}
				break;

			default:
				break;
		}
	}


	sem_init(&semaphore, 0, 0);
	
	if(pthread_create(&dataOutThread, NULL, dataOut, &arg)) {
		fprintf(stderr, "Error creating thread\n");
		exit(-1);
	}

	for(i=0; i<N_TRANSFERS; i++){
		xfr = libusb_alloc_transfer(0);
		if(xfr == NULL){
			fprintf(stderr, "Can't allocate libusb_transfer structure %i\n", i);
			exit(-1);
		}

		usbTransfers[i].xfr = xfr;

		buf = malloc(BUFLEN);
		if(buf == NULL){
			fprintf(stderr, "Can't allocate buffer for USB transfer %i\n", i);
			exit(-ENOMEM);
		}

		usbTransfers[i].buf = buf;
	}
	
	outBuffer = malloc(BUFLEN);
	if(outBuffer == NULL){
		fprintf(stderr, "Can't allocate memory\n");
		exit(-ENOMEM);
	}

	outBufferDec = malloc(BUFLEN/decimation);
	if(outBufferDec == NULL){
		fprintf(stderr, "Can't allocate memory\n");
		exit(-ENOMEM);
	}


	/* Initialize libusb */
	ret = libusb_init(&ctx);
	if(ret != 0){
		fprintf(stderr, "Error %i initializing libusb\n", ret);
		exit(-ret);
	}

	/* Open USB device */
	handle = libusb_open_device_with_vid_pid(ctx, 0x04b4, 0x1003);
	if(handle == NULL){
		fprintf(stderr, "Error opening device\n");
		exit(-1);
	}


	/* Claim interface */
	ret = libusb_claim_interface(handle, 0);
	if(ret != 0){
		fprintf(stderr, "Error %i claiming interface\n", ret);
		exit(-ret);		
	}
	
	
	/* Initiate USB transfers */
	for(i=0; i<N_TRANSFERS; i++){
		libusb_fill_bulk_transfer(usbTransfers[i].xfr, handle, 0x82, usbTransfers[i].buf, BUFLEN, callbackUSBTransferComplete, NULL, 5000);
		if(libusb_submit_transfer(usbTransfers[i].xfr) < 0){
			libusb_free_transfer(usbTransfers[i].xfr);
			fprintf(stderr, "Error in submitting USB transfer %i\n", i);
			exit(1);
		}
		
		ret = write(STDERR_FILENO, &asterisk, 1);
	}


	while(1){
		if(libusb_handle_events(NULL) != LIBUSB_SUCCESS)
			break;
	}

	libusb_release_interface(handle, 0);
	libusb_close(handle);
	libusb_exit(ctx);
	
	return 0;
}

