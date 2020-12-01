%wilkinson test
n=21; br=11;
W=zeros(n);

for i=1:br
   W(i,i)=br-i;
end
for i=br+1:n
   W(i,i)=i-br;
end
d=1e-4;

T=zeros(10*n);
Delta=d*ones(n);

for i=0:9
    T(i*n+1:(i+1)*n, i*n+1:(i+1)*n)=W;
end

for i=0:8
    T(i*n+1:(i+1)*n, i*n+1+n:(i+1)*n + n )=Delta;
end

for i=0:8
    T(i*n+1+n:(i+1)*n+n, i*n+1:(i+1)*n)=Delta;
end

n=210;
m=105;

%1. racunanje rastava T=diag(T1,T2)+bm*v*v'
ro=T(m, m+1); %ro=b_m
T1=zeros(m); T2=zeros(n-m); %da rijesimo problem dimenzije u sljedecim iteracijama
T1=T(1:m, 1:m); %T1 je gornji lijevi blok
T1(m,m)=T1(m,m)-ro; %oduzimamo ro=b_m na zadnjem dijagonalnom elementu u T1
T2=T(m+1:n, m+1:n); %T2 je donji desni blok
T2(1,1)=T2(1,1)-ro; %oduzimamo ro=b_m na prvom dijagonalnom elementu u T2

T=hess(T);
Q1=zeros(m);
S1=zeros(m);
Q2=zeros(n-m);  %da rijesimo problem dimenzije u sljedecim iteracijama
S2=zeros(n-m);
[Q1,S1]=eig(T1);
[Q2,S2]=eig(T2);

D=zeros(n); u=zeros(n,1);
D(1:m,1:m)=S1; %gornji lijevi blok matrice D je S1
D(m+1:n,m+1:n)=S2; %donji desni blok matrice D je S2
%u je vektor izracunat pomocu v = posljednji stupac od Q1' i prvi stupac od Q2'
u(1:m)=Q1(m,1:m); %posljednji stupac od Q1' je posljednji redak od Q1
u(m+1:n)=Q2(1,1:n-m); %prvi stupac od Q2' je prvi redak od Q2
d=diag(D); %d je vektor dijagonalnih elemenata od D