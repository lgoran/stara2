function [ sFn ] = Fn( x, ro, u, d, n)
%racuna vrijednost sekularne jednadžbe u x
sFn=0;
for i=1:n
    f=(u(i)^2)/(d(i)-x);
    sFn=sFn+f;
end
    sFn=sFn*ro+1;
end

