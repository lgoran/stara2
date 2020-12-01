#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <utility>
#include "vect.h"
using namespace std;

int main()
{
    // Vaši testovi dolaze ovdje.
    Vect<int> vek;
/*    cout<<vek<<endl;
    vek.push_back(1);
    cout<<vek<<" "<<vek.mdata<<endl;
    auto *data=vek.mdata;
    vek.push_back(2);
    cout<<vek<<" "<<vek.mdata<<" "<<data<<endl;
    data=vek.mdata;
    vek.push_back(3);
    cout<<vek<<" "<<vek.mdata<<" "<<data<<endl;
    data=vek.mdata;
    vek.push_back(4);
    cout<<vek<<" "<<vek.mdata<<" "<<data<<endl;
    data=vek.mdata;
    vek.push_back(5);
    cout<<vek<<" "<<vek.mdata<<" "<<data<<endl;*/

/*    Vect<int> vec1(3,5);
    Vect<int> vec2(3,5);
    Vect<int> vec;
    cout<<vec1<<" "<<vec2<<" "<<vec<<endl;
    vec = vec1 + vec2;
    cout<<vec;
    //ASSERT_EQ(vec.size(), 3u);
    //for(size_t i=0; i < vec.size(); ++i)
    //    ASSERT_EQ(vec[i], 10);

    size_t n = 10;
    Vect<pair<int,char> > v1(n,make_pair(3,'a'));
    const Vect<pair<int,char> > v2(n,make_pair(4,'a'));
    //cout<<v1<<" "<<v2<<endl;
    cout<<v1[n-1].first<<" "<<v2[n-1].second<<endl;*/
    return 0;
}
