#ifndef ZADATAK_IS_INCLUDED             
#define ZADATAK_IS_INCLUDED             

#include <vector>
#include <string>
#include <stdexcept>
#include <utility>
// Zadatak 1
void print_permutation(std::string str);


// Zadatak 2
template <typename InputIt1, typename InputIt2, typename OutputIt>
void zip(InputIt1 beg1, InputIt1  end1, InputIt2 beg2, InputIt2 end2, OutputIt beg3)
{
  // VAŠ KOD DOLAZI OVDJE
  while(beg1!=end1&& beg2!=end2)
  {
    *beg3=std::make_pair(*beg1,*beg2);
    beg3++;
    beg1++;
    beg2++;
  }
  //throw std::runtime_error("Zadatak nije riješen.");
}

template <typename T, typename S>
std::vector<std::pair<T,S> > 
zip(std::vector<T> const & vec1, std::vector<S> const & vec2)
{
  std::vector<std::pair<T,S> > vektor(vec1.size() > vec2.size() ? vec2.size() : vec1.size() );
  zip(vec1.begin(),vec1.end(),vec2.begin(),vec2.end(),vektor.begin());
  return vektor;
  //throw std::runtime_error("Zadatak nije riješen.");
}


// Zadatak 3
void normalize_phone_number(std::vector<std::string> & vec_str);

#endif
