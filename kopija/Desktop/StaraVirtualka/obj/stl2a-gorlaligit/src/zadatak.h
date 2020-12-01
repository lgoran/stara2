#ifndef KLASA
#define KLASA

#include <string>
#include <vector>
#include <iostream>
#include <map>

/* Funkcija čita tekst iz datoteke fileName i vraća pročitani tekst
 * kao niz riječi u varijabli words. Potrebno je napraviti transformacije
 * naznačene u zadatku.
 */
void readFile(std::string const & fileName, 
              std::vector<std::string> & words);

// Klasa pamti niz riječi i nudi neke informacije o riječima.
struct X{
    // Konstruktor
    X(std::vector<std::string> const & words);
    // Funkcija vraća maksimalni broj suglasnika u riječi 
    //
    int max_br_suglasnika() const;
    // Printaj na izlazni stream out sve riječi s točno k suglasnika 
    // odvojene jednom bjelinom (bez prijelaza unovi red na kraju).
    // Riječi moraju biti ispisne u leksikografskom poretku.
    void print(std::ostream &out, int k) const;    
private:
    // Vi određujete privatni dio klase
    std::map<std::string,int> mapa;
};
#endif

