pdmgrabber is a libusb based application interfacing with FX2LP board that acquires PDM data and sends it to standard output.

PDM data can then be piped in pdm2pcm application and finally played back using aplay. FX2LP needs a clock of at least 5MHz. The final application setup looks something like this:

![Microphone Array Setup](/images/mic_array_setup.png)

With this setup you can dump to a file the raw data from the microphones as follows:

    fx2grabber -d4 > pdm.dump
    
The `-d4` option specifies to keep just one PDM sample out of four since microphones are clocked ad 2048 kHz and the FX2LP acquisition is done at 8192 kHz. Each byte in the output stream represents the eight input channels sampled at the rising edge of the FX2LP clock, bit by bit.

It is also possible to play in real time one of the PDM channels. To decode and listen the first microphone, for example, do like follows:

    fx2grabber -p -s -d4 -c0 | ../pdm2pcm/pdm2pcm -f2048000 -d128 | aplay -fS16_LE -c1 -r16000

The `-c` option specifies which PDM channel to acquire. The `-p` option specifies to pack PDM bits in bytes so they can be decoded by pdm2pcm application. By default the bits are packed with LSB as the oldest sample. If using the `-s` option MSB is the oldest sample instead.

