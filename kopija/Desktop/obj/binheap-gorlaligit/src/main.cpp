#include <iostream>
#include "binHeap.h"
#include <vector>

using namespace std;
template <typename T>
void ispis(vector<T> vec)
{
  for(size_t i=0;i<vec.size();i++)
    cout<<vec[i]<<" ";
  cout<<endl;
}
int main()
{
 // Vaši testovi dolaze ovdje
  vector<short> vek{1,3,7,3,4,9,1};
  MaxHeap<int> hrpa;
  hrpa.push(2);hrpa.print();
  hrpa.push(7);hrpa.print();
  hrpa.push(4);hrpa.print();
  hrpa.push(9);hrpa.print();
  hrpa.pop();hrpa.print();
  hrpa.pop();hrpa.print();
  hrpa.push(3);hrpa.print();
  hrpa.pop();hrpa.print();
  hrpa.pop();hrpa.print();
  hrpa.pop();hrpa.print();
  MaxHeap<int> hrpa2(vek.begin(),vek.end());
  hrpa2.print();
  hrpa2.push(2);hrpa2.print();
  hrpa2.pop();hrpa2.print();
  hrpa2.push(7);hrpa2.print();
  hrpa2.push(4);hrpa2.print();

  std::vector<double> a{1.0, 3.0, 3.1, 3.01, 4.0, 9.0, 1.0};
  MaxHeap<double> h2(a.begin(), a.end());
  h2.print();
  h2.sort(a);ispis(a);
  h2.print();

  return 0;
}
