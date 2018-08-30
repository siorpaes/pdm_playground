clear all;
Fs = 2048000;
Ts = 1/Fs;
Ftone = 512;

% Attenuation
% /20 attenuation corresponds to 120dB-94dB = 26dB
% 120dB is the Acoustic Overload Point of the microphone corresponding
% to a full scale [-1..1] range. See datasheet of your microphone.
% 94dB is the Sound Pressure Level used as sensitivity reference
Attenuation = 20;

% This must be integer!
Nperiod = Fs/Ftone;

%Generate tone
n=0:(Nperiod-1);
tone = sin(2*pi*Ftone*n*Ts);
tone = tone/Attenuation;
qe = 0;

%Generate PDM in [-1, 1]
for i=1:length(tone)
 if ( tone(i) > qe )
   pdm(i) = 1;
 else
   pdm(i) = -1;
 endif
 qe = pdm(i) - tone(i) + qe;
endfor

%Frame in [0, 1]
pdm = pdm + 1;
pdm = pdm / 2;

plot(n, pdm, n, tone);

%Write to file
pdmint = int32(pdm);
dlmwrite ("tonepdm.txt", pdmint, "delimiter", ",", "newline", "\n")
