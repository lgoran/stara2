function [ sdFn ] = dFn( x, ro, u, d, n )
%racuna vrijednost derivacije sekularne jednadžbe u x
sdFn=0;
for i=1:n
    df=(u(i)^2)/(d(i)-x)^(2);
    sdFn=sdFn+df;
end
    sdFn=ro*sdFn;
end

