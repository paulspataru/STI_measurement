%% Extragere matrice MTF pe baza IR:
close all;
clc,clear;

myDir_read = uigetdir; % folderul din care se citeste
myDir_write = uigetdir; % folderul in care se scriu matricile mtf
myFiles = dir(fullfile(myDir_read,'*.wav')); % structura primeste toate fisierele .wav pt citit

Fs = 48000;

MethodFlag = 1;
% 0 ----> Schroeder, use only first half
% 1 ----> Hirata, use both halves

% frecvente modulatie:
F_mod = [0.63 0.8 1 1.25 1.6 2 2.5 3.15 4 5 6.3 8 10 12.5 ];

% frecvente pt bancul de filtre de 1 octava:
F_left = [62.5 125 250 500 1000 2000 4000];
F_right = [250 500 1000 2000 4000 8000 16000];

% nivel zgomot ambiental masurat cu sonometrul:
% A01:
Ink = [12.3 20.2 21.4 25 21 16.4 14.3];

% A05:
%Ink = [25.5 20 23 27 18 15 14.2];

% B219:
%Ink = [2.1 4 4.7 8 10.7 13.1 13.9];


% nivel semnal de test
Isk = [99 96 93 90 87 84 81];

% SNR (dB) : 
qk = Isk - Ink;

% procesare MTF

% MTF matrix
Mk_fm = zeros(length(F_right),length(F_mod));

for j = 1:length(myFiles)

    baseFileName = myFiles(j).name;
    fullFileName = fullfile(myDir_read, baseFileName);
    irtot = audioread(fullFileName);

    irtot = irtot/max(irtot);
    index_max_1 = find(irtot(1:15*Fs) == max(irtot(1:15*Fs)));
    index_max_2 = find(irtot(1:23*Fs) == max(irtot(15*Fs:23*Fs)));


    ir1 = irtot(index_max_1 - 2400 :(index_max_1 + 2*Fs));
    % tt = 0:1/Fs:2;
    % figure()
    % semilogy(tt(1:length(ir1)),ir1)

    if MethodFlag == 1
        ir2 = irtot(index_max_2 - 2400 :(index_max_2 + 2*Fs));
    else
        ir2 = ir1;
    end

    for k = 1:length(F_right)

        % filter IR:
        d = designfilt("bandpassiir",FilterOrder=20, PassbandFrequency1=F_left(k),PassbandFrequency2=F_right(k), ...
            PassbandRipple=0.1,SampleRate=Fs);

        ir1k = filter(d,ir1);
        ir2k = filter(d,ir2);

        t = 0:1/Fs:length(ir1k)/Fs-1/Fs;
        t=t';
        N = length(ir1k);

        Ek = 0;
        Sk = 0;

        for fm = 1 : length(F_mod)

            for tau = N-1:-1:1
                Ek = Ek + ir1k(tau) * ir2k(tau) ; % conversia din analogic in digital e integrala -> suma
                Sk = Sk + ir1k(tau) * ir2k(tau) * exp(-2i*pi*F_mod(fm)*t(tau)) ;

            end

            %Mk_fm(k,fm) = abs(Sk)/Ek;
            % intensity ratio correction:
            Mk_fm(k,fm) = abs(Sk)/abs(Ek) / (1+10.^(-qk(k)));

        end


    end

    % for k = 1:length(F_right)
    %         for fm=1:length(F_mod)
    %             if Mk_fm(k,fm) >= 1 % measurment invalid because of errors, convert to 0.99
    %                 Mk_fm(k,fm) = 0.99;
    %             end
    %         end
    % end
    
    writeBaseFileName = myFiles(j).name;
    writeBaseFileName = join(['MTF_', writeBaseFileName(1:end-4)]);
    writeBaseFileName = join([writeBaseFileName,".txt"]);
    writeFullPathName = fullfile(myDir_write, writeBaseFileName);
    writematrix(Mk_fm,writeFullPathName);

end


