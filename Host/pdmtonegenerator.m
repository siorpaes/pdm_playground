clear all;
Fs = 1000000;
Ts = 1/Fs;
Ftone = 500;

% This must be integer!
Nperiod = Fs/Ftone;

n=0:(Nperiod-1);
tone = sin(2*pi*Ftone*n*Ts)/2 + 0.5;
qe = 0;

for i=1:length(tone)
 if ( tone(i) > qe )
   pdm(i) = 1;
 else
   pdm(i) = 0;
 endif
 qe = pdm(i) - tone(i) + qe;
endfor

plot(n, pdm, n, tone);

pdmint = int32(pdm);
dlmwrite ("tonepdm.txt", pdmint, "delimiter", ",", "newline", "\n")
