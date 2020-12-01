#include <iostream>
#include "../src/binHeap.h"
#include "gtest/gtest.h"
#include <ctime>
#include <random>

template <typename T>
class CheckedHeap : public MaxHeap<T>{
  using Base = MaxHeap<T>;
  public:
    CheckedHeap() : Base() {}

    template <typename RAIT>
    CheckedHeap(RAIT begin, RAIT end) : Base(begin, end) {}

    bool isHeap() const ;
};


template <typename T>
bool CheckedHeap<T>::isHeap() const {
  bool rez = true;
  auto n = this->mData.size();
  for(typename Base::size_type i=0; i < n; ++i){
     auto left = 2*i+1;
     if(left >= n) 
         break;
     if(this->mData[i] < this->mData[left]) 
       rez = false;
    
     auto right = 2*i+2;
     if(right >= n) 
         break;
     if(this->mData[i] < this->mData[right]) 
       rez = false;
  }
  return rez;
}

template <typename T>
bool isHeap(std::vector<T> const & vec) {
  bool rez = true;
  auto n = vec.size();
  for(std::size_t i=0; i < n; ++i){
     auto left = 2*i+1;
     if(left >= n) 
         break;
     if(vec[i] < vec[left]) 
       rez = false;
    
     auto right = 2*i+2;
     if(right >= n) 
         break;
     if(vec[i] < vec[right]) 
       rez = false;
  }
  return rez;
}









TEST(Heap, Basic) 
{
  CheckedHeap<int> h1;
  h1.push(2);
  ASSERT_EQ(h1.isHeap(), true);
  ASSERT_EQ(h1.size(), 1u);
  h1.push(7);
  ASSERT_EQ(h1.isHeap(), true);
  h1.push(4);
  ASSERT_EQ(h1.isHeap(), true);
  h1.push(9);
  ASSERT_EQ(h1.isHeap(), true);
//  h1.print(); std::cout << std::endl;
  ASSERT_EQ(h1.isHeap(), true);
  h1.pop();
  ASSERT_EQ(h1.isHeap(), true);
  h1.pop();
  ASSERT_EQ(h1.isHeap(), true);
  h1.push(3);
  ASSERT_EQ(h1.isHeap(), true);
  h1.pop();
  ASSERT_EQ(h1.isHeap(), true);
  h1.pop();
  ASSERT_EQ(h1.isHeap(), true);
//  h1.print(); std::cout << std::endl;
  h1.pop();
  ASSERT_EQ(h1.empty(), true);
  ASSERT_EQ(h1.isHeap(), true);


  std::vector<short> a{1,3,7,3,4,9,1};
  ASSERT_EQ(isHeap(a), false);

  CheckedHeap<long> h2(a.begin(), a.end());
//  h2.print();
  ASSERT_EQ(h2.isHeap(),true);
  h1.push(2);
  ASSERT_EQ(h1.isHeap(), true);
  h1.pop();
  ASSERT_EQ(h1.isHeap(), true);
  h1.push(7);
  ASSERT_EQ(h1.isHeap(), true);
  h1.push(4);
  ASSERT_EQ(h1.isHeap(), true);

}


TEST(Heap, Sort) 
{
 
  std::vector<double> a{1.0, 3.0, 3.1, 3.01, 4.0, 9.0, 1.0};
  ASSERT_EQ(isHeap(a), false);

  CheckedHeap<double> h2(a.begin(), a.end());
  ASSERT_EQ(h2.isHeap(),true);
//  h2.print(); std::cout << std::endl;
  h2.sort(a);
  ASSERT_EQ(h2.empty(), true);
//  for(auto x : a) std::cout << x << " ";
//  std::cout << std::endl;
  ASSERT_DOUBLE_EQ(a[0], 1.0);
  ASSERT_DOUBLE_EQ(a[1], 1.0);
  ASSERT_DOUBLE_EQ(a[2], 3.0);
  ASSERT_DOUBLE_EQ(a[3], 3.01);
  ASSERT_DOUBLE_EQ(a[4], 3.1);
  ASSERT_DOUBLE_EQ(a[5], 4.0);
  ASSERT_DOUBLE_EQ(a[6], 9.0);
}


TEST(Heap, SortRand) 
{
   std::default_random_engine r_engine; // Generator slučajnih brojeva
   r_engine.seed( std::time(nullptr) );
   std::normal_distribution<> nd(0.0, 2.0);
   std::vector<double> rand(200), mysort(200);
   for(auto & x : rand) x = nd(r_engine);

   CheckedHeap<double> h2(rand.begin(), rand.end());
   ASSERT_EQ(h2.isHeap(),true);
   h2.sort(mysort);
   ASSERT_EQ(h2.empty(), true);
   std::sort(rand.begin(), rand.end());
   ASSERT_DOUBLE_EQ(mysort[0], rand[0]);
   ASSERT_DOUBLE_EQ(mysort[99], rand[99]);
   ASSERT_DOUBLE_EQ(mysort[199], rand[199]);


   std::uniform_int_distribution<> ind(-10000, 10000);
   std::vector<int> irand(200), imysort(200);
   for(auto & x : irand) x = ind(r_engine);

   CheckedHeap<int> ih2(irand.begin(), irand.end());
   ASSERT_EQ(ih2.isHeap(),true);
   ih2.sort(imysort);
   ASSERT_EQ(ih2.empty(), true);
   std::sort(irand.begin(), irand.end());
   ASSERT_DOUBLE_EQ(imysort[1], irand[1]);
   ASSERT_DOUBLE_EQ(imysort[97], irand[97]);
   ASSERT_DOUBLE_EQ(imysort[196], irand[196]);



}




int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
