n=6; ro=2;
d=zeros(n,1);
for i=1:n, d(i)=i; end, d(5)=8; d(3)=7; d(2)=3; d(4)=8; %d=1 3 7 8 8 6 --> 1 3 6 7 8 8
D=diag(d);
u=ones(n,1); u(2)=0; u(3)=0; %u= 1 0 0 1 1 1 --> 1 0 1 0 1 1
Dt=D+ro*u*u';
max_iter=100;
Qs=zeros(n);
x=zeros(n,1);

[x, Qs, ind, br]=izbaci_iste(d, u, ro, n); %sada su mi u x i Qs na i-toj poziciji
%i-ta svojstvena vrijednosti vektor dobiveni u sluèaju da je d(i)==d(i+1)
%ili u(i)==0; ind(i)=1 ako je na x(i) sv.vrijednost, 0 ako nije
%k=n-br; k je broj nultoèaka sekularne jednadžbe koje æemo dobiti, tj. broj 
%svojstvenih vrijednosti koje su ostale nepoznate
y=rijesi_sekularnu2(d, u, ro, max_iter); %za u(i)=0 imat æemo dvostruku nultoèku,
%moramo je zamijeniti sa d(i) na odgovarajuæoj poziciji

if br==0
    S=diag(y);
else
    y=uniquetol(y,1e-8);
    x(ind==0)=y;
    S=diag(x);
end

%naðimo nepoznate vektore (za sv.vrij iz y)
for i=1:n
    if ind(i)==0
        for j=1:n %u i-ti stupac spremam i-ti svojstveni vektor
            Qs(j,i)=u(j)/(d(j)-x(i)); %i-ti svojstveni vektor je: inv(D-x(i)*I)*u
        end  
    end
    Qs(:,i)=Qs(:,i)./norm(Qs(:,i),2); %normiranje (svih, i onih veæ izraèunatih)
end
