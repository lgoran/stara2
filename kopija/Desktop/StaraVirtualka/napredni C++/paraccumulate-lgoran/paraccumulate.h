#pragma once
#include <thread>
#include <algorithm>
#include <numeric>
#include <vector>
#include <chrono>
#include <mutex>
#include "clock.h"
#include <iomanip>

template <typename T, typename Iterator>
void block_accumulate(Iterator first, Iterator last, T & result){
    T init = 0;
    result = std::accumulate(first, last, init);
}

// Pralalni accumulate algoritam
template <typename T, typename Iterator>
T parallel_accumulate(Iterator first, Iterator last, T init){
    auto length = std::distance(first, last);
    if(!length)
        return init; 

    int phard = std::thread::hardware_concurrency();
    if(!phard)
        phard = 2;  
    int n = 1000;  
    int pmax = (length > n) ? length/n : 1;  
    int p = std::min(pmax, phard);  

    std::vector<T> results(p); // mjesto za rezultat izračunavanja
    std::vector<std::thread> threads(p-1); // paralelne programske niti

    auto block_size = length/p;
    auto block_first = first;
    auto block_last = block_first;
    for(int i=0; i < p-1; ++i){
        std::advance(block_last, block_size);
        threads[i] = std::thread(block_accumulate<T,Iterator>,
                                 block_first, block_last, std::ref(results[i]));
        block_first = block_last;
    }
    // Ostatak sumiramo u glavnoj programskoj niti.
    results[p-1] = std::accumulate(block_first, last, T());  

    for(int i=0; i < p-1; ++i)
        threads[i].join();  
    // Kad sve dretve završe glavna će obaviti konačno sumiranje.
    return std::accumulate(results.begin(), results.end(), init); 
}

template <typename Iterator, class UnaryOperator>
void block_transform(Iterator first, Iterator last, Iterator outFirst, UnaryOperator unaryOperator){
    std::transform(first, last, outFirst, unaryOperator);
}

template <typename Iterator, class UnaryOperator>
void parallel_transform(Iterator first, Iterator last, Iterator outFirst, UnaryOperator unaryOperator){
    auto length = std::distance(first, last);
    if(!length)
        return; 

    int phard = std::thread::hardware_concurrency();
    if(!phard)
        phard = 2;  
    int n = 1000;  
    int pmax = (length > n) ? length/n : 1;
    int p = std::min(pmax, phard);

    std::vector<std::thread> threads(p-1); // paralelne programske niti

    auto block_size = length/p;
    auto block_first = first;
    auto block_last = block_first;
    for(int i=0; i < p-1; ++i){
        std::advance(block_last, block_size);
        threads[i] = std::thread(block_transform<Iterator,UnaryOperator>,
                                 block_first, block_last, block_first, unaryOperator);
        block_first = block_last;
    }
    // Ostatak sumiramo u glavnoj programskoj niti.
    std::transform(block_first, last, block_first, unaryOperator);  

    for(int i=0; i < p-1; ++i)
        threads[i].join();  
}