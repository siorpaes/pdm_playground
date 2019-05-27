/** @file bin2txt.c
 * Converts S16_LE input to text
 * Usage:
 * bin2txt < audio.bin > audio.txt
 */

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>


int main(int argc, char** argv)
{
	int ret;
	int16_t input;
   
	ret = 2;

	while(ret == 2){
		ret = read(0, &input, 2);
		printf("%i,\n", input);
	}
	
	return 0;
}


