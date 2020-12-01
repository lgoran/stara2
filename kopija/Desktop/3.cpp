#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include<iterator>
#include <cassert>
using namespace std;
template <typename Cont>
void print(Cont const & c, char const * delim = "")
{
    for(auto const  & x : c)
        cout<<x<<delim;
    cout<<"\n";//efikasnije od endl
}
int main()
{
    vector<int> vec{9,3,6,1,9,5,6,3};
    list<double> lst(vec.size()); // svih 8 elem inicijalizirani na 0
    deque<int> deq;//ka vector koji moze rast i lijevo i desno
    assert(deq.size()==0); // zaustavlja program ako ne vridi uvjet unutra
    print(vec,",");
    sort(vec.begin(),vec.end(),[](int x, int y){return x>y;});// ovo iza je za silazno
    print(vec,",");
    copy(vec.begin(),vec.end(),lst.begin());//pretpostavlja da ima dovoljno mista
                                            //vec kopira u lst
    print(lst,",");
    copy(vec.begin(),vec.end(), front_inserter(deq)); //back front i obicni insert
    assert(deq.size() == vec.size());
    print(deq,"*");
    
    ostream_iterator<int> osi(cout," "); // nacin ispisivanja- korisno za fileove
    copy(vec.begin(),vec.end(), osi);
    cout<<endl;

    istream_iterator<int> isi(cin); // netriba nikakvo sranje posli,to samo kod outputa
    istream_iterator<int> end; // "end " iterator
    vector<int> vec1(isi,end); // inicijalizira vector sa ulazom za tipkovnice
                               // ctrl+D za zaustavit unos
    print(vec1, "-");

    copy(vec.rbegin(),vec.rend(),lst.begin()); // reverzni iterator-obrnuti ispis
    print(lst,"__");
    
    cout<<"----------------------------------"<<endl;
    list<int> lst1{1,2,3,4,5,6,7,8,9};
    auto it=next(lst1.begin() , 2); // pomakne iterator za 2 mista,prev za previous
    cout<<*it<<endl;
    list<int>::reverse_iterator rit(it); //okrene poluotvoreni interval,ispise broj ispred
                                         //iako pokazuje na isto misto 
    cout<<*rit<<endl;
    cout<<*rit.base()<<endl;// pretvorba reverznog u obicni sa base
    return 0;
}


