close all;
clc,clear;

myDir_read = uigetdir; % folderul din care se citeste
myFiles = dir(fullfile(myDir_read,'*.wav')); % structura primeste toate fisierele .wav pt citit
%myDir_write = uigetdir; % folderul in care se scriu matricile T30
Fs = 48000;
tt = 0:1/Fs:24;

% 1 octave:
F_left = [62.5 125 250 500 1000 2000 4000];
F_right = [250 500 1000 2000 4000 8000 16000];

% vectori cu parametrii mediati:
T30 = zeros(length(F_right),length(myFiles));
T30_mean = zeros(length(F_right),1);
C_mean = zeros(length(F_right),1);
C = 0;

for j = 1:length(myFiles)

    baseFileName = myFiles(j).name;
    fullFileName = fullfile(myDir_read, baseFileName);
    irtot = audioread(fullFileName);

    irtot = irtot/max(irtot);
    figure();
    semilogy(tt,irtot(1:length(tt)));
    ir1 = irtot(10*Fs+1:12*Fs);      
    ir2 = irtot(22*Fs+1:24*Fs);

    % generare semnale filtrate pe o octava:
    for k=1:length(F_right)
        d = designfilt("bandpassiir",FilterOrder=20, PassbandFrequency1=F_left(k),PassbandFrequency2=F_right(k), ...
            PassbandRipple=0.1,SampleRate=Fs);

        ir1k = filter(d,ir1);
        ir2k = filter(d,ir2);

        ir1k = ir1k / max(ir1k);
        ir2k = ir2k / max(ir2k);

        index = 1;
        while 20*log10(abs(ir1k(index)))<-20
            index = index + 1;
        end
        ir_sel = ir1k(index:index+1.6*Fs);
        te = 0.05;
        I1 = sum(ir_sel(1:te*Fs).^2);
        I2 = sum(ir_sel(te*Fs+1:end).^2);
        C = 10*log10(I1/I2);
        
        t = 0:1/Fs:length(ir1k)/Fs-1/Fs;
        t=t';
        N = length(ir1k);

        % calcul T30 prin metoda Hirata:
        EHirk = zeros(N,1);
        for n = N-1:-1:1
            EHirk(n) = EHirk(n+1)+ir1k(n)*ir1k(n);
        end
        EHirk = 10*log10(abs(EHirk)/max(abs(EHirk)));
        T30Hir = parame_reverb(t,EHirk);

        T30(k,j) = T30(k,j) + T30Hir;
        T30_mean(k,1) = T30_mean(k,1) + T30Hir;
        C_mean(k,1) = C_mean(k,1) + C;
    end

    % writeBaseFileName = myFiles(j).name;
    % writeBaseFileName = join(['T30_', writeBaseFileName(1:end-4)]);
    % writeBaseFileName = join([writeBaseFileName,".txt"]);
    % writeFullPathName = fullfile(myDir_write, writeBaseFileName);
    % writematrix(T30(:,j),writeFullPathName);
end

% mediile parametrilor pe fiecare octava:
T30_mean(:,1) = T30_mean(:,1) / length(myFiles);
C_mean(:,1) = C_mean(:,1) / length(myFiles);

% writeBaseFileName = join(['T30',".txt"]);
% writeFullPathName = fullfile(myDir_write, writeBaseFileName);
% writematrix(T30,writeFullPathName);
