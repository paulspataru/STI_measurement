%% Generare si salvare semnal de test
clear; close all; clc;

Fs = 48000; % frecventa de esantionare
T = 18; % durata semnal de test
pi = 3.14159;
t = 0:1/Fs:T-1/Fs;

% generare noise:
x = lowpass(randn(1,T*Fs,"single"),16000,Fs); % eliminare componente peste 16 kHz
x = x / max(x) * 10^(-3/20); % normare


% f=0:Fs/length(x):Fs/2-Fs/length(x);
% X = fft(x);
% figure();
% semilogx(f,20*log10(abs(X(1:end/2))));

% frecvente pt bancul de filtre :
Fc = [125 250 500 1000 2000 4000 8000]; % frecvente centrale pentru filtre de 1/2 octava
Flo = [105.112 210.224 420.448 840.896 1681.973 3363.586 6727.171];
Fhi = [148.651 297.302 594.604 1189.207 2378.414 4756.828 9523.657];

% ponderi pentru modelare spectrala
L = [-2.5 0.5 0 -6 -12 -18 -24]; % in dB
G = 10.^(L/20);

% frecvente de modulatie conform metodei STIPA:
fm1 = [1.6 1 0.63 2 1.25 0.8 2.5];
fm2 = [8 5 3.15 10 6.25 4 12.5];

x_sum = zeros(size(x));
% vom folosi filtre Chebyshev de tip 1 ordinul 12
for k = 1:7

    d = designfilt("bandpassiir",FilterOrder=12, PassbandFrequency1=Flo(k),PassbandFrequency2=Fhi(k), ...
        PassbandRipple=0.3,SampleRate=Fs);

    y = filter(d,x);
    y = y / max(y) * 10^(-3/20);
    % f=0:Fs/length(y):Fs/2-Fs/length(y);
    % Y = fft(y);
    % figure();
    % semilogx(f,20*log10(abs(Y(1:end/2))));

    % aplicare pondere
    y = y*G(k);

    figure();
    plot(t,y); title ( "pre modulatie");

    % modulatie
    A = sqrt(0.5*(1+0.55*(sin(2*pi*fm1(k)*t)-sin(2*pi*fm2(k)*t))));
    y = y.*A;

    figure();
    plot(t,y); title ( "post modulatie");

    %
    x_sum = x_sum + y;

end

x_sum = x_sum / max(x_sum) * 10^(-3/20); % normare si reducere cu 3 dB

audiowrite("STIPA_semnal_de_test/STIPA_testSig_18s.wav",x_sum,Fs,'BitsPerSample',24);

figure();
subplot(2,1,1);
plot(t,x_sum);title("Semnalul de test STIPA");
xlabel(" Timp [s]"); ylabel("Amplitudine")

f=0:Fs/length(x_sum):Fs/2-Fs/length(x_sum);
Y = fft(x_sum);
%figure();
subplot(2,1,2);
semilogx(f,20*log10(abs(Y(1:end/2)))); title("Spectrul semnalului de test STIPA");
xlabel(" Frecventa [Hz]"); ylabel("Amplitudine [dB]")




