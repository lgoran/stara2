/* Kreirati paralelni min_element() algoritam koristeći programske niti. 
 * Vidi https://en.cppreference.com/w/cpp/algorithm/min_element
 */
#pragma once
#include <thread>
#include <algorithm>
#include <numeric>
#include <vector>
#include <chrono>
#include <mutex>
#include "clock.h"
#include <iomanip>

template<typename ForwardIt, typename Compare>
void block_min_element(ForwardIt first, ForwardIt last, Compare comp, ForwardIt &out)
{
    if (first == last)
    {
        out=first;
        return;
    }
 
    ForwardIt smallest = first;
    ++first;
    for (; first != last; ++first) {
        if (comp(*first, *smallest)) {
            smallest = first;
        }
    }
    out=smallest;
}
template<typename ForwardIt, typename Compare>
auto block_min_element2(ForwardIt first, ForwardIt last, Compare comp)
{
    if (first == last)
    {
        return *first;
    }
 
    ForwardIt smallest = first;
    ++first;
    for (; first != last; ++first) {
        if (comp(**first, **smallest)) {
            smallest = first;
        }
    }
    return *smallest;
}


template<typename ForwardIt, typename Compare>
ForwardIt par_min_element(ForwardIt first, ForwardIt last, Compare comp )
{
    auto length = std::distance(first, last);
    if(length<=1)
        return first; 

    int phard = std::thread::hardware_concurrency();
    if(!phard)
        phard = 2;  
    int n = 1000;  
    int pmax = (length > n) ? length/n : 1;  
    int p = std::min(pmax, phard);

    std::vector<ForwardIt> results(p);
    std::vector<std::thread> threads(p-1);

    auto block_size = length/p;
    auto block_first = first;
    auto block_last = block_first;
    for(int i=0; i < p-1; ++i){
        std::advance(block_last, block_size);
        threads[i] = std::thread(block_min_element<ForwardIt, Compare>,
                                 block_first, block_last, comp, std::ref(results[i]));
        block_first = block_last;
    }
    results[p-1] = std::min_element(block_first, last, comp);

    for(int i=0; i < p-1; ++i)
        threads[i].join();  
        
    return block_min_element2(results.begin(), results.end(), comp);
}
   

