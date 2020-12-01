#include "minelement.h"
#include "random_int.h"
#include "clock.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

bool compare(int a, int b)
{
  return (a<b) ? true:false;
}

int main(int argc, char * argv[])
{
  int N = 1000000;
  if(argc > 1)
      N = std::atoi(argv[1]);
  
  RandomInt ri(-5000000,5000000);
  std::vector<int> source(N);
  std::generate(std::begin(source), std::end(source), ri); 

  Clock t;
  std::cout<<std::endl<<*par_min_element(source.begin(), source.end(), compare)<<std::endl;
  auto time = t.stop(Clock::microsec);
  std::cout << "N = " << N << ", parallel min_elem" << std::setprecision(10) << ", time = " << time << " us" << std::endl;
  
  t.start();
  std::cout<<std::endl<<*std::min_element(source.begin(), source.end(), compare)<<std::endl;
  time = t.stop(Clock::microsec);
  std::cout << "N = " << N << ", serial min_elem" << std::setprecision(10) << ", time = " << time << " us" << std::endl;
 
  return 0;
}
