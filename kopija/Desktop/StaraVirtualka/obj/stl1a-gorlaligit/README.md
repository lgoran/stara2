# C++  STL 1

Vježbanje korištenja standardne biblioteke.    
Referenca: [en.cppreference.com/w/cpp](http://en.cppreference.com/w/cpp).


**Zadatak 1**. Napišite funkciju koja printa sve permutacije stringa.
Prva permutacija mora biti sortirani string.


**Zadatak 2**. Treba napisati zip-algoritam koji uzima dva ulazna niza i vraća niz parova. 
Svaki par je složen od člana
prvog niza (`first`) i člana drugog niza (`second`). Algoritam iterira kroz ulazne nizove i 
u svakoj iteraciji formira jedan par. Ulazni nizovi ne moraju biti iste duljine. Algoritam staje
kada iscrpi jedan od dva ulazna niza, tako da izlazni niz ima duljinu
kraćeg niza.   Algoritam mora raditi sa svim sekvencijalnim spremnicima.

Napraviti preopterećenu verziju ovog algoritma koja uzima kao ulaz
`std::vector<T>` i `std::vector<S>`  i vraća
`std::vector<std::pair<T,S>>`. Verzija treba pozivati prethodni
algoritam.  

**Zadatak3**. Treba transformirati listu telefonskih brojeva u normaliziranu formu
kao u ovim slučajevima:

 0911234567 --> +385911234567

 011234567   --> +38511234567.

 021123456   --> +38521123456

 +385 1 1234567 --> +38511234567

 385 1 1234567 --> +38511234567

1234567 --> +38511234567


Broju se dodaje + i pozivni za Hrvatsku ako ga nema. Ako broj nema lokalni pozivni
broj pretpostavlja se 01.  


Ne zaboravite, nakon što ste klonirali repozitorij, napraviti
```
git submodule init
git submodule update 
```
kako bi se dovukao googletest. Bez njega nećete moći kompilirati kod. 

Molim da izvršni kod smjestite u direktorij *build* paralelan sa *src*. 
