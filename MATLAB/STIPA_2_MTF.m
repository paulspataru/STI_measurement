%% Extragere matrice MTF pe baza masuratorii STIPA:
close all;
clc,clear;

myDir_semnal_test = 'C:\Users\Paul\Desktop\Dizertatie\STI matlab\STIPA_semnal_de_test';
myDir_read_measurements = uigetdir; % folderul din care se citesc masuratorile STIPA
% myDir_read_noise = uigetdir; % folderul din care se citeste zg ambiental
myDir_write = uigetdir; % folderul in care se scriu matricile mtf

myFiles = dir(fullfile(myDir_read_measurements,'*.wav')); % structura primeste toate fisierele .wav pt citit

myFiles_semnal_test = dir(fullfile(myDir_semnal_test,'*.wav'));

Fs = 48000; % frecv de esantionare
%T = 18; % timp semnal = 18 dar vom folosi doar portiunea [0,17] s pentru procesare 
T = 10;
t = 0 : 1/Fs : T-1/Fs; % vector timp pentru calcule
t = t';

% frecvente pt bancul de filtre de 1 octava:
F_left = [105.112 210.224 420.448 840.896 1681.973 3363.586 6727.171];
F_right = [148.651 297.302 594.604 1189.207 2378.414 4756.828 9523.657];

% frecvente de modulatie conform metodei STIPA:
fm1 = [1.6 1 0.63 2 1.25 0.8 2.5];
fm2 = [8 5 3.15 10 6.25 4 12.5];

% vom folosi perioadele pentru a masura pe un numar intreg de perioade
Tm1 = 1./fm1;
Tm2 = 1./fm2;

% Nr de perioade in primele 17 sec de semnal:
Nm1 = floor (T ./ Tm1);
Nm2 = floor (T ./ Tm2);

% Nr de perioade skip = primele 10%
Nskipm1 = round (Nm1.*0.1);
Nskipm2 = round (Nm2.*0.1);

% Nr de perioade pe care facem masuratoarea
Nmeasm1 = Nm1 - 2 * Nskipm1;
Nmeasm2 = Nm2 - 2 * Nskipm2;

% Momentele de timp (in secunde) la care incepem / oprim integrarea
T1start = Tm1 .* Nskipm1;
T2start = Tm2 .* Nskipm2;
T1stop = Tm1 .* (Nskipm1 + Nmeasm1);
T2stop = Tm2 .* (Nskipm2 + Nmeasm2);

% Momentele de timp in esantioane
itstartm1 = zeros(length(T1start),1);
itstartm2 = zeros(length(T2start),1);
itstopm1 = zeros(length(T1stop),1);
itstopm2 = zeros(length(T2stop),1);
for k = 1:length(T1start)

    for it = 1:length(t)
        if t(it) > T1start(k)
            itstartm1(k) = it;
            break;
        end
    end

    for it = 1:length(t)
        if t(it) > T2start(k)
            itstartm2(k) = it;
            break;
        end
    end

    for it = 1:length(t)
        if t(it) > T1stop(k)
            itstopm1(k) = it;
            break;
        end
    end

    for it = 1:length(t)
        if t(it) > T2stop(k)
            itstopm2(k) = it;
            break;
        end
    end

end

% SNR (dB) - todo : get from measurment, for now its hard-coded:
qk = [20 30 40 40 40 50 50];

% initializare MTFin si MTFout
mi = zeros(length(F_right),2);
mo = zeros(length(F_right),2);
m = zeros(length(F_right),2);

Lvoce = [-2.5 0.5 0 -6 -12 -18 -24];

% nivel zgomot ambiental masurat cu sonometrul:
% A01:
Ink = [12.3 20.2 21.4 25 21 16.4 14.3];

% A05:
%Ink = [25.5 20 23 27 18 15 14.2];

% B219:
%Ink = [2.1 4 4.7 8 10.7 13.1 13.9];

L = Lvoce + 65; % 65 dB volum de referinta

% SNR (dB) :
qk = L - Ink;

wl = 500;

% 1) mi a semnalului transmis

for j = 1:length(myFiles_semnal_test)

    baseFileName = myFiles_semnal_test(j).name;
    fullFileName = fullfile(myDir_semnal_test, baseFileName);
    STIPA_meas = audioread(fullFileName);
    STIPA_meas = STIPA_meas(1:T*Fs);
    STIPA_meas = STIPA_meas/max(STIPA_meas);
    
    for k = 1:length(F_right)

        % filtrare pe octave:
        d = designfilt("bandpassiir",FilterOrder=20, PassbandFrequency1=F_left(k),PassbandFrequency2=F_right(k), ...
            PassbandRipple=0.1,SampleRate=Fs);        

        Ik = filter(d,STIPA_meas);

        % calcul anvelopa 
        Ik = Ik.^2;
        Ik = lowpass(Ik,100,Fs,ImpulseResponse="iir",Steepness=0.95);
        % [Ik,~] = envelope(Ik,wl,'rms');

        % insumarea trebuie realizata pe un numar intreg de perioade pentru
        % fiecare frecventa de modulatie :
        sin1 = sin(2*pi*fm1(k)*t(itstartm1(k):itstopm1(k)));
        sin2 = sin(2*pi*fm2(k)*t(itstartm2(k):itstopm2(k)));
        cos1 = cos(2*pi*fm1(k)*t(itstartm1(k):itstopm1(k)));
        cos2 = cos(2*pi*fm2(k)*t(itstartm2(k):itstopm2(k)));

        SumSinf1  = sum(Ik(itstartm1(k):itstopm1(k)).*sin1);
        SumCosf1 = sum(Ik(itstartm1(k):itstopm1(k)).*cos1);
        SumSinf2 = sum(Ik(itstartm2(k):itstopm2(k)).*sin2);
        SumCosf2 = sum(Ik(itstartm2(k):itstopm2(k)).*cos2);
        SumIk1 = sum(Ik(itstartm1(k):itstopm1(k)));
        SumIk2 = sum(Ik(itstartm2(k):itstopm2(k)));

        mi(k,1) = sqrt( SumSinf1^2 + SumCosf1^2 ) / SumIk1;
        mi(k,2) = sqrt( SumSinf2^2 + SumCosf2^2 ) / SumIk2;

    end

end

% 2) mo a semnalului receptionat:

for j = 1:length(myFiles)

    baseFileName = myFiles(j).name;
    fullFileName = fullfile(myDir_read_measurements, baseFileName);
    STIPA_meas = audioread(fullFileName);
    STIPA_meas = STIPA_meas(1:T*Fs);
    STIPA_meas = STIPA_meas/max(STIPA_meas);
    
    for k = 1:length(F_right)

        % filtrare pe octave:
        d = designfilt("bandpassiir",FilterOrder=20, PassbandFrequency1=F_left(k),PassbandFrequency2=F_right(k), ...
            PassbandRipple=0.1,SampleRate=Fs);        

        Ik = filter(d,STIPA_meas);

        % calcul anvelopa 
        
        Ik = Ik.^2;
        Ik = lowpass(Ik,100,Fs,ImpulseResponse="iir",Steepness=0.95);
        %[Ik,~] = envelope(Ik,wl,'rms');

        % insumarea trebuie realizata pe un numar intreg de perioade pentru
        % fiecare frecventa de modulatie :
        sin1 = sin(2*pi*fm1(k)*t(itstartm1(k):itstopm1(k)));
        sin2 = sin(2*pi*fm2(k)*t(itstartm2(k):itstopm2(k)));
        cos1 = cos(2*pi*fm1(k)*t(itstartm1(k):itstopm1(k)));
        cos2 = cos(2*pi*fm2(k)*t(itstartm2(k):itstopm2(k)));

        SumSinf1  = sum(Ik(itstartm1(k):itstopm1(k)).*sin1);
        SumCosf1 = sum(Ik(itstartm1(k):itstopm1(k)).*cos1);
        SumSinf2 = sum(Ik(itstartm2(k):itstopm2(k)).*sin2);
        SumCosf2 = sum(Ik(itstartm2(k):itstopm2(k)).*cos2);
        SumIk1 = sum(Ik(itstartm1(k):itstopm1(k)));
        SumIk2 = sum(Ik(itstartm2(k):itstopm2(k)));
       
        mo(k,1) = sqrt( SumSinf1^2 + SumCosf1^2 ) / SumIk1;
        mo(k,2) = sqrt( SumSinf2^2 + SumCosf2^2 ) / SumIk2;

        if j == 2
            mot = mo;
        end

    end
    
    m = mo./mi;

    % for k = 1:length(F_right)
    %     m = m/ (1+10.^(-qk(k)));
    % end
    
    writeBaseFileName = myFiles(j).name;
    writeBaseFileName = join(['MTF_', writeBaseFileName(1:end-4)]);
    writeBaseFileName = join([writeBaseFileName,".txt"]);
    writeFullPathName = fullfile(myDir_write, writeBaseFileName);
    writematrix(m,writeFullPathName);

end