function [a,b] = reglin(t,y)
% calculeaza ecuatia unei drepte pe baza regresiei liniare
a = (mean(t.*y)- mean(t)*mean(y)) /...
    (mean(t.^2)-mean(t)^2);
b = mean(y) - a*mean(t);