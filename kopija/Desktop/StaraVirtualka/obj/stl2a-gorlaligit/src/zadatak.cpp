#include "zadatak.h"
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include <map>
#include <utility>
#include <iterator>

using namespace std;
void readFile(std::string const & fileName, 
              std::vector<std::string> & words)
{
   // Ovdje dolazi vaš kod
    ifstream in(fileName);
    string rijec;
    char c;
    string interpukcija;
    interpukcija.push_back('.');
    interpukcija.push_back(',');
    interpukcija.push_back(':');
    interpukcija.push_back(';');
    interpukcija.push_back('(');
    interpukcija.push_back(')');
    interpukcija.push_back('"');
    bool flag=true;
    while(in.get(c))
    {
        if(isspace(c) && flag==true)
        {}
        else if(!isspace(c))
        {
            rijec.push_back(c);
            flag=false;
        }
        else if(isspace(c) && flag==false)
        {
            words.push_back(rijec);
            rijec.clear();
            flag=true;
        }
        
    }
    for(unsigned int i=0;i<words.size();i++)
    {
        string s=words[i];
        for(unsigned int j=0;j<interpukcija.size();j++)
        {
            if(s.front()==interpukcija[j])
            {
                s.erase(0,1);
            }
        }
        for(unsigned int j=0;j<interpukcija.size();j++)
        {
            if(s.back()==interpukcija[j])
            {
                s.pop_back();
            }
        }
        words[i]=s;
    }
    in.close();
   //throw std::runtime_error("Zadatak nije riješen.");
}

// konstruktor
X::X(std::vector<std::string> const & words){
   // Ovdje dolazi vaš kod
    int br=0;
   for(int i=0;i<words.size();i++)
   {
       for(int j=0;j<words[i].size();j++)
       {
           if(words[i][j]!='a'&&words[i][j]!='e'&&words[i][j]!='u'&&words[i][j]!='i'&&words[i][j]!='o'&&
           words[i][j]!='A'&&words[i][j]!='E'&&words[i][j]!='U'&&words[i][j]!='I'&&words[i][j]!='O')
           br++;
       }
    mapa.insert({words[i],br});
    br=0;
   }
   
   //throw std::runtime_error("Zadatak nije riješen.");
}


int X::max_br_suglasnika() const{
   // Ovdje dolazi vaš kod
   int max=0;
   int br=0;
   for(auto i=mapa.begin();i!=mapa.end();i++)
   {
       if(i->second > max)
       max=i->second;
   }
    return max;
   //throw std::runtime_error("Zadatak nije riješen.");
}


void X::print(std::ostream &out, int k) const{
   // Ovdje dolazi vaš kod
   vector<string> trazeni;
        for(auto it=mapa.begin();it!=mapa.end();it++)
    {
        if(it->second==k)
        {
            trazeni.push_back(it->first);
        }
    }
    copy(trazeni.begin(),trazeni.end(),ostream_iterator<const string>(out," "));
   //throw std::runtime_error("Zadatak nije riješen.");
}

