# PDM decoding on PC

Using logic analyzer to grab PDM data

- Acquire PDM data using a Logic Analyzer and export the data in ASCII format. End result is a text file containing single rows of zeroes and ones. If using Salae logic analyzer, for example, you can use the "Parallel Decoder". See `bellazio.txt.bz2` for a PDM dump file example.
- Convert PDM data in the format suitable for openpdm library, i.e.: packed PDM bits, using 'txt2bin.c' program: `bzcat bellazio.txt.bz2 | ./txt2bin > bellazio.dat`
- Listen to decoded audio passing PDM sampling frequency (-f option) and decimation factor (-d option) : `pdm2pcm -f1024000 -d128 < ./bellazio.dat | aplay -fS16_LE -c1 -r8000`
- All in a single line: `bzcat bellazio.txt.bz2 | ./txt2bin | ./pdm2pcm -f1024000 -d128 | aplay -fS16_LE -c1 -r8000`

Using Cypress FX2LP setup

- Follow instructions provided in the `pdmgrabber` folder for setting up the hardware.
- Grab up to eight microphones in parallel using fx2grabber utility as follows: `fx2grabber -d4 dump.pdm`
- Use `packdata` utility to extract microphone channels and decode them to PCM with:  `packdata.exe 0 < dump.pdm | pdm2pcm -f 2048000 -d128 | aplay -fS16_LE -c1 -r16000` where '0' is the index of the microphone to extract.
