# C++  STL 2

Vježbanje korištenja standardne biblioteke.    
Referenca: [en.cppreference.com/w/cpp](http://en.cppreference.com/w/cpp).
 
**Zadatak 1**. Treba napisati funkciju `readFile()` koja otvara tekstualnu datoteku
za čitanje i razbija tekst na riječi (vrši tokenizaciju). Sve riječi iz teksta se pamte 
u vektoru stringova na koji je funkcija dobila referencu.

Prilikom razbijanja teksta u riječi treba eliminirati sve bjeline 
(bjelina, '\t','\n','\v') tako da niti jedna riječ ne sadrži bjeline.

Nakon toga funkcija treba s početka i kraja svake riječi ukloniti interpunkcije,
navodnike  i zagrade (',','.',';',':',')','(', '"').

Funkcija readFile()` je time gotova i rezultat vraća kroz svoj drugi parametar.
 
*Uputa*. Za tokenizaciju koristiti funkciju `std::readline()`. Za ispitivanje 
bjelina koristiti funkciju `std::isspace` iz zaglavlja `<cctype>`.

**Zadatak 2**. Napisati klasu `X` čije je sučelje dano u src/zadatak.h datoteci.
Konstruktor uzima listu riječi, eliminira duplikate i za svaku riječ pamti 
broj suglasnika u njoj. U metodi `max_br_suglasnika()` vraća najveći broj 
suglasnika koji neka riječ u listi riječi sadrži. 

Metoda `print(out,k)` ispisuje  na izlazni stream `out` sve riječi s točno `k` suglasnika 
odvojene jednom bjelinom (bez prijelaza unovi red na kraju).
Riječi moraju biti ispisne *u leksikografskom poretku*.

*Uputa*. Koristiti `std::map` za sortiranje elemenata. Ispis na izlazni stream raditi 
kopiranjem (algoritmom). Ako je potrebno ispisati std::pair na stream-u ond aje najlakše
definirati operator ispisa u std imeniku. 
