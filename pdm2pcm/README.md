# PDM decoding on PC

Using logic analyzer to grab PDM data

- Acquire PDM data using Logic Analyzer and dump the contents in ASCII format. End result is a text file containing single rows of zeroes and ones
- Convert PDM data in the format suitable for openpdm library, i.e.: packed PDM bits, using 'txt2bin.c' program: `bzcat bellazio.txt.bz2 | ./txt2bin > bellazio.dat`
- Listen to decoded audio passing PDM sampling frequency (-f option) and decimation factor (-d option) : `pdm2pcm -f1024000 -d128 < ./bellazio.dat | aplay -fS16_LE -c1 -r8000`
- In one single line: `bzcat bellazio.txt.bz2 | ./txt2bin | ./pdm2pcm -f1024000 -d128 | aplay -fS16_LE -c1 -r8000`

Using Cypress FX2LP setup

- Grab all microphones with fx2grabber utility in pdmgrabber folder as follows: `fx2grabber -d4 pdm.dump`
- Use packdata utility to extract single microphone acquisitions: `packdata.exe 0 < pdm.dump | pdm2pcm -f 2048000 -d128 | aplay -fS16_LE -c1 -r16000` where '0' is the index of the microphone to extract.


