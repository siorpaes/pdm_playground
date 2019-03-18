PDM decoding on PC

-Acquire PDM data using Logic Analyzer and dump the contents in ASCII format.
 End result is a text file containing single rows of zeroes and ones
-Convert PDM data in the format suitable for openpdm library, i.e.: packed
 PDM bits, using 'txt2bin.c' program:
 bzcat bellazio.txt.bz2 | ./txt2bin > bellazio.dat
-Edit pdm2pcm parameters according to the input PDM frequency and desired
 decimation factor. Note that openpdm library works on 1ms PDM data buffers.
-Listen to decoded audio with:
 ./pdm2pcm < ./bellazio.dat | aplay -fS16_LE -c1 -r10000
-In one single line:
 bzcat bellazio.txt.bz2 | ./txt2bin | ./pdm2pcm | aplay -fS16_LE -c1 -r10000
