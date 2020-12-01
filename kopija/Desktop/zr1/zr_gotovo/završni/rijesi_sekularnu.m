function [x]=rijesi_sekularnu(d, u, ro, max_iter)
n=length(d);
[x0, n1]=aproksimacije(d, ro);
for i=1:n1
    for j=1:max_iter
        x(i)=x0(i)-Fn(x0(i), ro, u, d, n)/dFn(x0(i), ro, u, d, n);
        %if i==1, display(dFn(x0(i), ro, u, d, n)); end
        if abs(x(i)-x0(i))<eps, break, end
        x0(i)=x(i);
    end
end