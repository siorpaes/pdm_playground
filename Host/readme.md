This directory contains one single period of reference 500Hz tones with different magnitudes. They are generated with Octave script pdmtonegenerator.m.

tone500Hz.h represents full scale tone in [-1, 1] range. This represents microphone's Acoustic Overload Point (AOP) which corresponds to 0 dBFS (full-scale dB).

Microphone's AOP level is usually set to something like 120/130 dBSPL (Sound Pressure Level) which is usually quite a high value (see microphone's datasheet for exact AOP values). For this reason, a digital gain is foreseeable in the decimation filter to amplify sounds which lay in lower end acoustic levels. A reasonable peak level is the standard 94dBSPL value which is used to define microphone's sensitivity.

Using such value as a the full-scale representation, we need to apply a gain of AOP-94dB, corresponding to a linear gain of:

G = 10^((AOP-94)/20)


If, for example, the microphone has AOP=120dBSPL, we need to apply a gain of 20.
The other tones 'tone500HzAxx.h' in this directory are attenuated versions of the original full-scale tone and can be used to tune the gain of the decimation filter on an attenuated input signal.


See Invensense AN-1112 for more details.






