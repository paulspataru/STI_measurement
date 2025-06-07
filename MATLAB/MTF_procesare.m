%% Procesare matrici si extragere STI
close all;
clc,clear;

Fs = 48000;
T=10;

% frecvente pt bancul de filtre de 1 octava:
F_left = [62.5 125 250 500 1000 2000 4000];
F_right = [250 500 1000 2000 4000 8000 16000];

% ponderi pentru octave
alfa = [0.085 0.127 0.23 0.233 0.309 0.224 0.173];
beta = [0.085 0.078 0.065 0.011 0.047 0.095 0];
Lvoce = [-2.5 0.5 0 -6 -12 -18 -24]; % db SPL, ponderi specifice vocii
Ak = [46 27 12 6.5 7.5 8 12]; % db SPL, ponderi pentru limita de receptie

% citire fisiere mtf
myDir_read = uigetdir;
myFiles = dir(fullfile(myDir_read,'*.txt'));
% vor fi foldere separate pentru fiecare camera se vor face citirile si scrierile pe rand pentru
% fiecare camera in parte

auditoryMaskingFlag = 1;

L = Lvoce + 65;

STI_dict = configureDictionary("string","double");
for j = 1:length(myFiles)

    baseFileName = myFiles(j).name;
    fullFileName = fullfile(myDir_read, baseFileName);
    MTFtable = readtable(fullFileName, 'Delimiter',',');
    MTF = table2array(MTFtable);

    % -----------------------compensare mascare--------------------------
    if auditoryMaskingFlag == 1


        I = 10.^(L./10);
        Iam = zeros(length(I),1);
        C2 = zeros(length(I),1);

        for k = 2:length(F_right)

            if L(k-1) < 63
                La = 0.5 * L(k-1) - 65;
            else
                if L(k-1) < 67
                    La = 1.8 * L(k-1) - 146.9;
                else
                    if L(k-1) < 100
                        La = 0.5 * L(k-1) - 59.8;
                    else
                        La = -10;
                    end
                end
            end

            a = 10^(La/10);

            Iam(k) = I(k-1) * a;

        end

        Irt = 10.^(Ak./10);

        for k = 1:length(F_right)
            for fm = 1:length(MTF(k,:))
                if MTF(k,1) >= 1
                    MTF(k,1) = 0.99;
                end
            end
            MTF(k,:) = MTF(k,:).* (I(k)/(I(k)+Iam(k)+Irt(k)));
        end


    end

    % SNR eff
    SNReff = 10*log(MTF./(1-MTF));
    % trunchiere la +/- SNR
    for k = 1:size(SNReff,1)
        for fm = 1:size(SNReff,2)
            if SNReff(k,fm) > 15
                SNReff(k,fm) = 15;
            end
            if SNReff(k,fm) < -15
                SNReff(k,fm) = -15;
            end
        end
    end

    % TI (transmission index)
    TI = (SNReff + 15)./30;

    % MTIk (modulation transfer index)
    MTI = zeros(length(F_left),1);
    for k = 1:size(TI,1)
        MTI(k) = sum(TI(k,:)) / size(TI,2);
    end

    % STI

    % alpha sum:
    Salpha = 0;
    for k = 1:size(TI,1)
        Salpha = Salpha + MTI(k)*alfa(k);
    end

    % beta sum:
    Sbeta = 0;
    for k = 1:(size(TI,1)-1)
        Sbeta = Sbeta + sqrt(abs(MTI(k)*MTI(k+1)))*beta(k);
    end

    STI = Salpha - Sbeta;
    STI_dict(baseFileName(5:end-4)) = STI;

end