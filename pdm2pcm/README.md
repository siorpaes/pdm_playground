# PDM decoding on PC

- Acquire PDM data using Logic Analyzer and dump the contents in ASCII format. End result is a text file containing single rows of zeroes and ones
- Convert PDM data in the format suitable for openpdm library, i.e.: packed PDM bits, using 'txt2bin.c' program: `bzcat bellazio.txt.bz2 | ./txt2bin > bellazio.dat`
- Listen to decoded audio passing PDM sampling frequency (-f option) and decimation factor (-d option) : `pdm2pcm -f1024000 -d128 < ./bellazio.dat | aplay -fS16_LE -c1 -r8000`
- In one single line: `bzcat bellazio.txt.bz2 | ./txt2bin | ./pdm2pcm -f1024000 -d128 | aplay -fS16_LE -c1 -r8000`
