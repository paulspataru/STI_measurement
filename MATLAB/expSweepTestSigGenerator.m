%% Generare si salvare semnal de test
clear; close all; clc;
% f1 = frecventa de start
% f2 = frecventa de stop
% T = durata semnal
% Fs = frecventa de esantionare

f1 = 20; % 200 de Hz frecventa de start pentru ca boxa nu este capabila sa produca frecvente mai joase
f2 = 18100; % 18 kHz va fi frecventa de stop pentru ultimul filtru
Fs = 48000;
T=6;

w1=2*pi*f1;
w2=2*pi*f2;

L=T/log(w2/w1);
k=w1*L;
t = 0:1/Fs:T-1/Fs;
s = sin(k*(exp(t/L)-1));
s=s*10^(-3/20);
%s2 = [s,zeros(1,2*Fs),s]';
audiowrite('IR_expSweep/sTest_6s_Schroeder.wav',s,Fs,BitsPerSample=32);

% filtru de inversare pentru extragere raspuns la impuls:
% finv=s(end:-1:1).*exp(-t/L);
% audiowrite('filtru_inv_10s.wav',finv,Fs);

%% Afisare semnal test si filtru de inversare pe grafic:

figure(1);
plot(t,s);
xlabel('Timp[s]');ylabel('Amplitudine');title('Semnal de test si filtru in timp')
hold on;
plot(t,finv);
legend('semnal de test','filtru invers');
hold off;

Finv = fft(finv);
S=fft(s);
f=0:Fs/length(s):Fs/2-Fs/length(s);
figure(2);
semilogx(f,20*log10(abs(S(1:end/2))));
hold on;
semilogx(f,20*log10(abs(Finv(1:end/2))));
xlabel('Frecventa [Hz]');ylabel('Amplitudine[dB]');
title('Spectre semnal de test si filtru');
legend('semnal de test','filtru invers');

%% Procesare si salvare raspuns la impuls
close all;

myDir_read = uigetdir; % folderul din care se citeste
myDir_write = uigetdir; % folderul in care se scrie
% vor fi foldere separate pentru fiecare camera se vor face citirile si scrierile pe rand pentru
% fiecare camera in parte

myFiles_read = dir(fullfile(myDir_read,'*.wav')); % structura primeste toate fisierele .wav pt citit

for k = 1:length(myFiles_read)

    baseFileName = myFiles_read(k).name;
    fullFileName = fullfile(myDir_read, baseFileName);
    y = audioread(fullFileName);
    y = y(1:(2*T+2)*Fs);

    % t=0:1/Fs:length(y)/Fs-1/Fs;
    % plot(t,y);
    % xlabel('Timp[s]');ylabel('Amplitudine');title('semnal inregistrat');
    % Y = fft(y(1:Fs*T));
    % f=0:Fs/length(Y):Fs/2-Fs/length(Y);
    % figure();
    % semilogx(f,20*log10(abs(Y(1:end/2))));
    % xlabel('Frecventa[Hz]');ylabel('Amplitudine[dB]');title('spectrul semnalului inregistrat');

    finv2=[finv';zeros(length(y),1)];
    y2=[y;zeros(length(finv),1)];
    h=ifft(fft(finv2).*fft(y2));

    h = h/max(h); % normare raspuns la impuls
    h=h*10^(-3/20); % warning la audiowrite pentru ca intra in limitare la max
    figure();
    t=0:1/Fs:length(h)/Fs-1/Fs;
    plot(t,20*log10(abs(h)));
    xlabel('Timp[s]');ylabel('Amplitudine [dB]');title('Raspuns la impuls');

    %writeBaseFileName = join(['IR_', myFiles_read(k).name]);
    writeFullFileName = fullfile(myDir_write, myFiles_read(k).name);
    audiowrite(writeFullFileName,h,Fs,'BitsPerSample',24);
end