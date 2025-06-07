function [T30,T20,EDT] = parame_reverb(t,E)
% extragerea parametrilor energetici de reverberatie
% E trebuie sa fie normata si in dB
index0 = 1; % % index pentru nivelul de 0 dB
while(E(index0)>-0.1)
    index0 = index0+1;
end

index5 = 1;
while E(index5)>-5 
    index5 = index5+1;
end

index10 = 1;
while E(index10)>-10
    index10 = index10+1;
end

index25 = 1;
while E(index25)>-25
    index25 = index25+1;
end

index35 = 1;
while E(index35)>-35
    index35 = index35+1;
end

[a, b] = reglin( t(index5:index35), E(index5:index35));
T30 = -60/a;

[a, b] = reglin( t(index5:index25), E(index5:index25));
T20 = -60/a;

[a, b] = reglin( t(index0:index10), E(index0:index10));
EDT = -60/a;