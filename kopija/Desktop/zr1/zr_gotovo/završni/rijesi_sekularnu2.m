function [x]=rijesi_sekularnu2(d, u, ro, max_iter)
n=length(d);
F=makeF(ro,d,u,n);

[x0, n1]=aproksimacije(d, ro);

for i=1:n1
    x(i)=fsolve(F,x0(i));
end
x=uniquetol(x);