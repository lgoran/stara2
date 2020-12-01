function [x, Qs, ind, br]=izbaci_iste(d, u, ro, n)
[d,perm]=sort(d);
u=u(perm);
ind=zeros(n,1);
x=zeros(n,1);
br=0;
Qs=zeros(n);
for i=1:n-1
    if u(i)==0
        ind(i)=1; br=br+1;
        x(i)=d(i);
        Qs(:,i)=zeros(n,1); Qs(perm(i),i)=1;
    else
        if d(i)==d(i+1)
            ind(i)=1; br=br+1;
            x(i)=d(i);
            Qs(:,i)=zeros(n,1); Qs(perm(i),i)=u(i+1); Qs(perm(i+1),i)=-u(i);
        end
    end
end
