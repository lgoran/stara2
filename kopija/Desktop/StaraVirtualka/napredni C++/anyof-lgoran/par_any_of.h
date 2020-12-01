#pragma once
#include <thread>
#include <algorithm>
#include <numeric>
#include <vector>
#include <chrono>
#include <mutex>
#include <iomanip>
#include <future>
#include <stdexcept>

template<typename InputIt, typename UnaryPredicate, typename Promise, typename Future, typename AtomicBool, typename AtomicInt, typename Length>
void block_any_of(InputIt first, InputIt last, UnaryPredicate p, Promise &promise, Future &future, AtomicBool &found, AtomicInt &counter,  Length n) {

    for(auto temp = first; temp != last; ++temp) 
    {
         if (found.load()) return;
         try{
            if ( p(*temp) && future.valid()){
               found.store(true);
               promise.set_value(true);
               return;
            }
         }
         catch(...){
            try{
               if (future.valid()){
                  found.store(true);
                  promise.set_exception(std::current_exception());
                  return;
               }
            }
            catch(...){
               return;
            }
            }
         ++counter;
         if (counter.load() == n){
            promise.set_value(false);
            return;
         }
    }
}


template<typename InputIt, typename UnaryPredicate >
bool parany_of(InputIt first, InputIt last, UnaryPredicate p){

    auto length = std::distance(first, last);
    if(!length)
        return false;

    int phard = std::thread::hardware_concurrency();
    if(!phard)
        phard = 2;
    int n = 10;
    int pmax = (length > n) ? length/n : 1;
    int numberOfThreads = std::min(pmax, phard);

    std::vector<std::thread> threads(numberOfThreads);

    auto block_size = length/numberOfThreads;
    auto block_first = first;
    auto block_last = block_first;

    std::atomic<int> counter(0);
    std::atomic<bool> found (false);
    std::promise<bool> promise;
    auto future = promise.get_future();

    for(int i = 0; i < numberOfThreads - 1; i++){
         std::advance(block_last, block_size);
         threads[i] = std::thread(block_any_of<InputIt, UnaryPredicate, decltype(promise), decltype(future), decltype(found), decltype(counter), decltype(length) >,
                                          block_first, block_last, p, std::ref(promise), std::ref(future), std::ref(found), std::ref(counter), length) ;
         block_first = block_last;
    }
    threads[numberOfThreads - 1] = std::thread(block_any_of<InputIt, UnaryPredicate, decltype(promise), decltype(future), decltype(found), decltype(counter), decltype(length) >,
                                                block_first, last, p, std::ref(promise), std::ref(future), std::ref(found), std::ref(counter), length);

    for(int i = 0; i < numberOfThreads; i++)
        threads[i].join();

    try{
        auto x = future.get();
        return x;
    }
    catch(std::exception const & e){
        throw std::runtime_error(e.what());
    }
    catch(...){
        throw std::runtime_error("greska");
    }
}