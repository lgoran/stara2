function [Q, S] = divide_and_conquer(T)
n=max(size(T));
max_iter=100;

if n==1  %uvjet zaustavljanja
    Q=1;
    S=T;
    return;
end

m=ceil(n/2);
%1. racunanje rastava T=diag(T1,T2)+bm*v*v'
ro=T(m, m+1); %ro=b_m
T1=zeros(m); T2=zeros(n-m); %da rijesimo problem dimenzije u sljedecim iteracijama
T1=T(1:m, 1:m); %T1 je gornji lijevi blok
T1(m,m)=T1(m,m)-ro; %oduzimamo ro=b_m na zadnjem dijagonalnom elementu u T1
T2=T(m+1:n, m+1:n); %T2 je donji desni blok
T2(1,1)=T2(1,1)-ro; %oduzimamo ro=b_m na prvom dijagonalnom elementu u T2

%2.,3. rekurzivnim pozivom racunamo svojstvene rastave od T1 i T2
Q1=zeros(m); 
S1=zeros(m);
Q2=zeros(n-m);  %da rijesimo problem dimenzije u sljedecim iteracijama
S2=zeros(n-m);
[Q1,S1]=divide_and_conquer(T1);
[Q2,S2]=divide_and_conquer(T2);

%4. racunamo D^tilda = D + ro*u*u' iz Q1, S1, Q2, S2
D=zeros(n); u=zeros(n,1);
D(1:m,1:m)=S1; %gornji lijevi blok matrice D je S1
D(m+1:n,m+1:n)=S2; %donji desni blok matrice D je S2
%u je vektor izracunat pomocu v = posljednji stupac od Q1' i prvi stupac od Q2'
u(1:m)=Q1(m,1:m); %posljednji stupac od Q1' je posljednji redak od Q1
u(m+1:n)=Q2(1,1:n-m); %prvi stupac od Q2' je prvi redak od Q2
d=diag(D); %d je vektor dijagonalnih elemenata od D
x=zeros(n,1); Qs=zeros(n); ind=zeros(n,1); S=zeros(n);

[x, Qs, ind, br]=izbaci_iste(d, u, ro, n); %sada su mi u x i Qs na i-toj poziciji
%i-ta svojstvena vrijednosti vektor dobiveni u sluèaju da je d(i)==d(i+1)
%ili u(i)==0; ind(i)=1 ako je na x(i) sv.vrijednost, 0 ako nije
%k=n-br; k je broj nultoèaka sekularne jednadžbe koje æemo dobiti, tj. broj 
%svojstvenih vrijednosti koje su ostale nepoznate
y=rijesi_sekularnu2(d, u, ro, max_iter); %za u(i)=0 imat æemo dvostruku nultoèku,
%moramo je zamijeniti sa d(i) na odgovarajuæoj poziciji
y

y=uniquetol(y);
x(ind==0)=y;
S=diag(x);


%naðimo nepoznate vektore (za sv.vrij iz y)
for i=1:n
    if ind(i)==0
        for j=1:n %u i-ti stupac spremam i-ti svojstveni vektor
            Qs(j,i)=u(j)/(d(j)-x(i)); %i-ti svojstveni vektor je: inv(D-x(i)*I)*u
        end  
    end
    Qs(:,i)=Qs(:,i)./norm(Qs(:,i),2); %normiranje (svih, i onih veæ izraèunatih)
end

Q=zeros(n);
Q(1:m,1:m)=Q1;
Q(m+1:n,m+1:n)=Q2;
Q=Q*Qs;

