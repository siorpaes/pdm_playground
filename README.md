This project is a PDM microphone simulator meant to be used as a hardware
reference data source for DSP algorithms development and testing.
The firmware runs on a 32 pin [Nucleo-L432KC](https://www.amazon.it/STM32-St-nucleo-Development-Board/dp/B077GFHLFS).
Any other Nucleo board can be easily adapted as only a SPI slave interface is
needed and STM32 Cube APIs are used.


Pinout

|Signal        | STM32 IO |  Nucleo connector |
|--------------|:--------:|:-----------------:| 
| PDM Clock    |   PA1    |      CN4-11 [A1]  | 
| PDM Data     |   PA6    |      CN4-7  [A5]  |
| 8MHz clkout  |   PA5    |      CN4-8  [A4]  |
| 2MHz clkout  |   PA9    |      CN3-1  [D9]  |
| 1MHz clkout  |   PA3    |      CN4-10 [A2]  |
| LED DMAdone  |   PB3    |      CN4-15 [D13] |



Apply PDM clock to PA1 and read resulting PDM data from PA6. A 1MHz clock is
available on PA3 for testing purposes.
The PDM data represents a 500Hz sinusoidal tone with a period of 2000 PDM
samples. Such parameters have been chosen in order to represent an audible
periodic PCM tone with the constraint for the PDM period to be a multiple of 8
which is the dimension of the minumum bit quantity that can be transferred via
SPI interface.

The tone has been generated with Octave using the script in the 'Host'
directory.

