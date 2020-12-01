#include "clock.h"
#include "paraccumulate.h"
#include <iostream>

// Glavni program koji testira paralelnu verziju accumulate() algoritma.
// Potrebno je na par primjera usporediti serijsku i paralelnu verziju 
// algoritma i usporediti njihova vremena izvršavanja kao funkciju veličine
// spremnika na kojem rade, 

int main(){
    for(int n=10;n<1000000000;n*=10)
    {
        std::vector<int> niz(n,1);
        Clock t;

        t.start();
        double sum = std::accumulate(niz.begin(), niz.end(), 0.0);
        auto time = t.stop(Clock::microsec);
        std::cout << "N = " << n << ", serial sum = " << std::setprecision(10) << sum << ", time = " << time << " us" << std::endl;
        
        t.start();
        sum = parallel_accumulate(niz.begin(), niz.end(), 0.0);
        time = t.stop(Clock::microsec);
        std::cout << "N = " << n << ", parallel sum = " << std::setprecision(10) << sum << ", time = " << time << " us" << std::endl;
        std::cout << "---------------------------------------\n";
    }

    for(int n=10;n<1000000000;n*=10)
    {
        std::vector<int> niz(n,1);
        Clock t;
        double sum;

        t.start();
        std::transform(niz.begin(), niz.end(), niz.begin(), [](int broj) -> int{return ++broj;});
        auto time = t.stop(Clock::microsec);
        sum = parallel_accumulate(niz.begin(), niz.end(), 0.0);
        std::cout << "N = " << n << ", serial transform, current sum = " << std::setprecision(10) << sum << ", time = " << time << " us" << std::endl;
        
        t.start();
        parallel_transform(niz.begin(), niz.end(), niz.begin(), [](int broj) -> int{return ++broj;});
        time = t.stop(Clock::microsec);
        sum = parallel_accumulate(niz.begin(), niz.end(), 0.0);
        std::cout << "N = " << n << ", parallel transform, current sum = " << std::setprecision(10) << sum << ", time = " << time << " us" << std::endl;
        std::cout << "---------------------------------------\n";
    }
    return 0;
}
