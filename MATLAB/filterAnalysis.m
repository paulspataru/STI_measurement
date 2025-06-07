%% octave filter analysis
close all;
clc;
clear;

Fs = 48000;
F_left = [62.5 125 250 500 1000 2000 4000];
F_right = [250 500 1000 2000 4000 8000 16000];

for k = 1:length(F_right)

    % filter IR:
    d = designfilt("bandpassiir",FilterOrder=20, PassbandFrequency1=F_left(k),PassbandFrequency2=F_right(k), ...
        PassbandRipple=0.1,SampleRate=Fs);

    filterAnalyzer(d);
    k
    d.Numerator
    d.Denominator

end

%% half octave filter analysis
close all;
clc;
clear;

Fs = 48000;
F_left = [105.112 210.224 420.448 840.896 1681.973 3363.586 6727.171];
F_right = [148.651 297.302 594.604 1189.207 2378.414 4756.828 9523.657];

for k = 1:length(F_right)

    % filter IR:
    d = designfilt("bandpassiir",FilterOrder=20, PassbandFrequency1=F_left(k),PassbandFrequency2=F_right(k), ...
        PassbandRipple=0.1,SampleRate=Fs);

    filterAnalyzer(d);
    k
    d.Numerator
    d.Denominator

end