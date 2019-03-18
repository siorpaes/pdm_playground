/** \file fx2grabber.c
 * \author david.siorpaes@gmail.com
 *
 * Reads 8-bit parallel data from Cypress FX2LP development board.
 * 
 * See Cypress application note AN58069
 * Usage:
 *
 * sudo ./fx2grabber | ../pdm2pcm/pdm2pcm | aplay -fS16_LE -c1 -r8000
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
unsigned char* outBufferPacked;

int packData(unsigned char* buffer, unsigned char* packedBuffer, int buflen)
{
	unsigned char val8;
	int i, bitn;

	/* Skip 8 bytes */
	for(i=0; i<buflen/8; i+=8){
		val8 = 0;
		for(bitn=0; bitn<8; bitn++){
			//val8 |= ((buffer[i*8 + 8*bitn] & 1 ) << (bitn));
			val8 |= ((buffer[i*8 + 8*bitn] & 1 ) << (7-bitn));
		}

		packedBuffer[i/8] = val8;
	}
	
	return 0;
}

/** Data Output thread
 */
void* dataOut(void* arg)
{
	int ret;
	int flags;
	unsigned int dataWritten;
	char del[3] = {'\b', ' ', '\b'};

	/* Set non-blocking IO */
	flags = fcntl(STDOUT_FILENO, F_GETFL);
	fcntl(STDOUT_FILENO, F_SETFL, flags | O_NONBLOCK);
	
	while(1){
		sem_wait(&semaphore);

		packData(outBuffer, outBufferPacked, BUFLEN);
		
		/* Dump buffer to STDOUT */
		dataWritten = 0;
		while(dataWritten < BUFLEN/64){
			ret = write(STDOUT_FILENO, outBufferPacked + dataWritten, BUFLEN/64-dataWritten);
			if(ret < 0){
				fprintf(stderr, "Error writing to STDOUT: %s\n", strerror(errno));
				exit(errno);
			}

			if(ret != BUFLEN/64)
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
	int i;
	int ret;
	int arg;

	char asterisk = '*';

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
			exit(-1);
		}

		usbTransfers[i].buf = buf;
	}
	
	outBuffer = malloc(BUFLEN);
	if(outBuffer == NULL){
		fprintf(stderr, "Can't allocate memory\n");
		exit(-1);
	}

	outBufferPacked = malloc(BUFLEN/8);
	if(outBufferPacked == NULL){
		fprintf(stderr, "Can't allocate memory\n");
		exit(-1);
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

