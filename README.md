This project hosts a collection of tools for dealing with Pulse Density Modulation (PDM) signals.

- pdmgenerator: Firmware for STM32 devices generating PDM tones. Very useful for testing PDM signals acquisition and processing.
- pdm2pcm: POSIX application meant to decode PDM signals and generate PCM output that can be played in real time using Linux 'aplay' program.
- pdmgrabber: Application based on libusb for acquiring in real time up to eight PDM signals using a Cypress FX2LP board. Useful for real time signal processing with microphone arrays.
- clockgen: very simple clock generator for Xilinx Basys3 board. Generates 8192 kHz and 2048 kHz clocks for testing pdmgrabber.


For more details see relevant README file of each tool.
