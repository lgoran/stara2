function [x0, n1]=aproksimacije(d, ro)
d=sort(d);
n=length(d);
d1=uniquetol(d);
n1=length(d1);

if ro>0
    for i=1:n1-1
        x0(i)=(d1(i)+d1(i+1))/2;
    end
    x0(n1)=d1(n1)+10;
else
    x0(1)=d1(1)-10;
    for i=2:n1
        x0(i)=(d1(i-1)+d1(i))/2;
    end
end



