#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
// Predložak klase koji implementira maximalnu hrpu. 
template <typename T>
class MaxHeap{
public:
    using size_type = typename std::vector<T>::size_type;
	// Konstruktor
    MaxHeap() = default;
    // Parametrizirani konstruktor koji preuzima elemente iz raspona [begin, end).
    template <typename RAIT>
    MaxHeap(RAIT begin, RAIT end);
	// Gurni novi element na hrpu.
    void push(T);
	// Ukloni vodeći (maksimalni) element sa hrpe.
    void pop();
	// Vrati vodeći element hrpe.
    T top() const;
    // Je li hrpa prazna?
    bool empty() const;
	// Broj elemenata u hrpi.
    size_type size() const;
    // Ispiši sortirane vijednosti u vektor vec. 
	// MaxHeap ostaje prazan nakon sortiranja.
    void sort(std::vector<T> & vec);
    void print();
protected:
  std::vector<T> mData;
  void correct_heap(size_t broj_cvora);
  // Eventualne dodatne metode stavljati u ovu sekciju.
  
};
template <typename T>
void MaxHeap<T>::print(){
    for(size_t i=0;i<mData.size();i++)
    std::cout<<mData[i]<<" ";
  std::cout<<std::endl;
}

template <typename T>
void MaxHeap<T>::correct_heap(size_t broj_cvora)
{
  auto misto=broj_cvora;
  if(mData.size()<=1) return;
  while(misto<=(mData.size()-1-1)/2)
  {
    if((misto*2+2 <= mData.size()-1))
    {
      if(mData[misto]<mData[misto*2+2] && mData[misto*2+1]<mData[misto*2+2])
      {
        std::swap(mData[misto],mData[misto*2+2]);
        misto=misto*2+2;
        
      }
      else if(mData[misto]<mData[misto*2+1] && mData[misto*2+1]>=mData[misto*2+2])
      {
        std::swap(mData[misto],mData[misto*2+1]);
        misto=misto*2+1;        
      }
      else return;
    }
    else
    {
      if(mData[misto]<mData[misto*2+1])
      {
        std::swap(mData[misto],mData[misto*2+1]);
        misto=misto*2+1;
      }
      else return;
    }
    
  }
}

template <typename T>
template <typename RAIT>
MaxHeap<T>::MaxHeap(RAIT begin, RAIT end){
   // Vaš kod 
   auto it=begin;
   while(it!=end){
    mData.push_back(*it);
    it++;
   }
   int l=(mData.size()-1-1)/2;
   while(l>=0)
   {
     correct_heap(l);
     l--;
   }
}

template <typename T>
void MaxHeap<T>::push(T elem){
  // Vaš kod    
  mData.push_back(elem);
  auto misto=mData.size()-1;
  while(misto>0 && mData[misto]>mData[(misto-1)/2])
  {
    std::swap(mData[misto],mData[(misto-1)/2]);
    misto=(misto-1)/2;
  }
}

template <typename T>
void MaxHeap<T>::pop(){
  // Vaš kod
  if(this->empty()) return;
  std::swap(mData[0],mData[mData.size()-1]);
  mData.pop_back();
  correct_heap(0);  
}

template <typename T>
T MaxHeap<T>::top() const{
  // Vaš kod
  return mData[0];
}

template <typename T>
bool MaxHeap<T>::empty() const {
  // Vaš kod
  if(mData.size()==0)
    return true;
  return false;
}

template <typename T>
typename MaxHeap<T>::size_type MaxHeap<T>::size() const {
  // Vaš kod
  return mData.size();
}

template <typename T>
void MaxHeap<T>::sort(std::vector<T> & vec){
  // Vaš kod
  vec.resize(mData.size());
  size_t br=vec.size()-1;
  while(this->size()>0){
    vec[br--]=this->top();
    this->pop();
  }
}


#endif