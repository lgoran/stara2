#include "zadatak.h"
#include <iostream>
#include <cassert>
#include <string>
#include <iterator>

#include <algorithm>
// Ubaciti potrebne include datoteke
void print_permutation(std::string str){
    std::sort(str.begin(),str.end());
    do
    {
        std::cout<<str<<"\n";
    }while(std::next_permutation(str.begin(),str.end()));
    
  //throw std::runtime_error("Zadatak nije riješen.");
}

// Ovdje dolazi vaš kod za Zadatak 1 i Zadatak 3.
void normalize_phone_number(std::vector<std::string> & vec_str){
    // VAŠ KOD DOLAZI OVDJE
  for(auto it=vec_str.begin();it!=vec_str.end();it++)
  {
    std::string str=*it;
    str.erase(std::remove_if(str.begin(),str.end(), ::isspace),str.end());
    if(str.front()=='0')
    {
      str.replace(0,1,"+385");
    }
    else if(str[0]=='3'&&str[1]=='8'&&str[2]=='5')
    {
      str.insert(0,"+");
    }
    else if(str[0]=='+'&&str[1]=='3'&&str[2]=='8'&&str[3]=='5')
    {
      
    }
    else if(str[0]=='1')
    {
      str.insert(0,"+3851");
    }
    else
    {
      str.insert(0,"+385");
    }
    *it=str;
  }
  
  
  //throw std::runtime_error("Zadatak nije riješen.");
}

