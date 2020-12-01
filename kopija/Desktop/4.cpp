#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <deque>
#include <algorithm>
#include <iterator>
#include <string>
#include <fstream>//file stream
#include <sstream>//string stream
#include <stdexcept>//izuzetci


#include <set>//sortirani jedinstveno mulitset i multimap mogu imat vise istih
#include <map>
#include <unordered_set>//hashirane tablice-brze
#include <unordered_map>


namespace std{       //dodajemo u std stagod zelimo npr ispis para
    template <typename T,typename U>
    ostream & operator<<(ostream & out, pair<T,U> const & p)
    {
        out<<p.first<<" : "<<p.second;
        return out;
    }
}
using namespace std;
int main(){
/*int main(int argc, char *argv[])
{
    string ime_datoteke("unknown.txt");
    if(argc > 1)                       //nulti argument komandne linije je ime programa
        ime_datoteke=argv[1];          //prvi ce biti ime datoteke
    ifstream in(ime_datoteke);          //konstruktor je odma otvara//input file stream//ako zelimo pisati u file sa ofstream ga otvorimo pa slicno sve ide
    if(in)
        cout<<"otvoren file"<<endl;
    else
        throw runtime_error("Ne mogu otvoriti file "+ime_datoteke+" za čitanje");       //izbacivanje izuzetka(greske) i trazi se catch koji trazi izuzetak//nije greska programa
    
//    string word;
//    while(in>>word)//dok je u regularnom stanju ide while inace neide(kraj datoteke ili greska u citanju)
//    {
//        cout<< word<<endl;
//    }
    string line;
    while(getline(in, line, ';'))// procita liniju i stavi je u string line//sve dok ima linija za citanje// zadnji znak je ono sta cita za novi red,defaultno je \n
    {                            //get umisto getline dohvaca znak po znak
        cout<<line<<endl;
    }
    
    in.close();
*/
  
    set<int> s1{1,8,5,6,7,6};
    copy(s1.begin(),s1.end(),ostream_iterator<int>(cout," ")); //ispisivanje kopije fancy
    cout<<endl;
    auto rez =s1.insert(9);   //vraca par//drugi element true ako je ubacen ako nije false//
    if(rez.second)
        cout<<"element je ubacen"<<endl;
    else cout<<"nije ubacen"<<endl;
    cout<<*rez.first<<endl; // dereferencirano se vraca 9
    cout<<s1.erase(5)<<endl;//izbrise sve petice//vraca broj izbrisanih elemenata
    auto it=s1.erase(s1.begin());//vraca iterator na sljedeci element//brise prvi
    cout<<*it<<endl;
    
    
    map<string,int> mapa{{"abc",3},{"Qwert",5},{"yxc",12}};
    copy(mapa.begin(),mapa.end(),ostream_iterator<pair<const string,int>>(cout," ")); //nekad bez const izbaci gresku
    cout<<endl;
    return 0;
}


