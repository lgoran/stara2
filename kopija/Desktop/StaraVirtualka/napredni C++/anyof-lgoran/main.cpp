#include "par_any_of.h"
#include <vector>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "clock.h"
#include <stdexcept>


int main(){
    // Ovdje u tri primjera treba pokazati korektnost paralelnog algoritma usporedbom
    // sa std::any_of() algoritmom.  U trećem primjeru demonstrirati 
    // propagiranje izuzetka.
    for(int n=10;n<1000000000;n*=10)
    {
        std::vector<int> vec(n);
        vec.push_back(1);
        Clock t;

        t.start();
        if(std::any_of(vec.begin(), vec.end(), [](int i){ return i % 2 == 1; }))
        {
            std::cout << "Ima\n";
        }
        auto time = t.stop(Clock::microsec);
        std::cout << "N = " << n << ", serial time = " << std::setprecision(10) << ", time = " << time << " us" << std::endl;
        
        t.start();
        if(parany_of(vec.begin(), vec.end(), [](int i){ return i % 2 == 0; }))
        {
            std::cout << "Ima\n";
        }
        time = t.stop(Clock::microsec);
        std::cout << "N = " << n << ", parallel time = " << std::setprecision(10) << ", time = " << time << " us" << std::endl;
        std::cout << "---------------------------------------\n";
    }

    for(int n=10;n<1000000000;n*=10)
    {
        std::vector<int> vec(n);
        vec[(int)n/2]=10;
        Clock t;

        t.start();
        if(std::any_of(vec.begin(), vec.end(), [](int i){ return i > 5; }))
        {
            std::cout << "Da\n";
        }
        auto time = t.stop(Clock::microsec);
        std::cout << "N = " << n << ", serial time = " << std::setprecision(10) << ", time = " << time << " us" << std::endl;
        
        t.start();
        if(parany_of(vec.begin(), vec.end(), [](int i){ return i > 5; }))
        {
            std::cout << "Da\n";
        }
        time = t.stop(Clock::microsec);
        std::cout << "N = " << n << ", parallel time = " << std::setprecision(10) << ", time = " << time << " us" << std::endl;
        std::cout << "---------------------------------------\n";
    }
    
    //primjer 3
    std::vector<int> vec(1000000);
    vec.push_back(1);
    vec.push_back(2);
    try{
        std::cout << std::any_of(vec.begin(), vec.end(), [](int i){ if(i==2) throw std::runtime_error("greska"); return i == 5; }) << std::endl;
    }
    catch(const std::exception& e){
        std::cout << "Exception from the thread: " << e.what() << '\n';
    }

    try{
        std::cout << parany_of(vec.begin(), vec.end(), [](int i){ if(i==2) throw std::runtime_error("greska"); return i == 5; }) << std::endl;
    }
    catch(const std::exception& e){
        std::cout << "Exception from the thread: " << e.what() << '\n';
    }
    return 0;
}