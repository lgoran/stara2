#include <iostream>
#include <memory>
#include <algorithm>
#include <ostream>
#include <math.h>
#include "vect.h"

template <typename T>
std::allocator<T> Vect<T>::alloc;
template <typename T>
T Vect<T>::operator[](Index i) const { return mdata[i]; }
template <typename T>
T& Vect<T>::operator[](Index i) { return mdata[i]; }
template <typename T>
Vect<T>::Vect(size_t n, T v)
{  
    if(n==0)
        mdata=mfirst_free=mend=nullptr;
    else{
        mdata=alloc.allocate(n);
        for(size_t br=0;br<n;++br)
        {        
            alloc.construct(mdata+br,v);
        }
        mend=mfirst_free=mdata+n; 
    }   
}
template <typename T>
Vect<T>::Vect(const Vect& vek)
{
    mdata=alloc.allocate(vek.capacity());
    for(size_t i=0;i<vek.size();++i)
    {
        *(mdata+i)=vek[i];
    }
    mfirst_free=mdata+vek.size();
    mend=mdata+vek.capacity();
}
template <typename T>
Vect<T>& Vect<T>::operator=(const Vect& vek)
{
    if(mdata!=vek.mdata)
    {
        this->free();
        mdata=alloc.allocate(vek.capacity());
        for(size_t i=0;i<vek.size();++i)
        {
            *(mdata+i)=vek[i];
        }
        mfirst_free=mdata+vek.size();
        mend=mdata+vek.capacity();
    }
    return *this;
}
template <typename T>
Vect<T>::Vect(Vect && vek) noexcept: mdata(vek.mdata) , mfirst_free(vek.mfirst_free) ,mend(vek.mend)
{
    vek.mdata=vek.mfirst_free=vek.mend=nullptr;
}
template <typename T>
Vect<T>& Vect<T>::operator=(Vect && v) noexcept
{
    if(this != &v)
    {
        this->free();
        mdata=v.mdata;
        mfirst_free=v.mfirst_free;
        mend=v.mend;
        v.mdata=v.mfirst_free=v.mend=nullptr;
    }
    return *this;
}
template <typename T>
Vect<T>::~Vect()
{  
    this->free();
    mfirst_free=mend=mdata=nullptr;
}
template <typename T>
void Vect<T> :: push_back(T elem)
{
    if(mfirst_free!=mend)
    {
        mdata[this->size()]=elem;
        ++mfirst_free;
    }
    else
    {
        this->reallocate();
        mdata[this->size()]=elem;
        ++mfirst_free;
    }
}
template <typename T>
size_t Vect<T>::size() const
{
    size_t br=0;
    if(mdata==mfirst_free)
        return 0;
    for(;mdata+br!=mfirst_free;++br)
    {}
    return br;
}
template <typename T>
size_t Vect<T>::capacity() const
{
    size_t br=0;
    if(mdata==mend)
        return 0;
    for(;mdata+br!=mend;++br)
    {}
    return br;
}
template <typename T>
Vect<T>& Vect<T>::operator+=(const Vect& vek)
{
    for(size_t i=0;i<this->size();++i)
    {
        mdata[i]+=vek[i];
    }
    return *this;
}
template <typename T>
Vect<T>& Vect<T>::operator-=(const Vect& vek)
{
        for(size_t i=0;i<this->size();++i)
    {
        mdata[i]-=vek[i];
    }
    return *this;
}
template <typename T>
Vect<T>& Vect<T>::operator*=(const Vect& vek)
{
        for(size_t i=0;i<this->size();++i)
    {
        mdata[i]*=vek[i];
    }
    return *this;
}
template <typename T>
Vect<T> operator+(const Vect<T> & vek1,const Vect<T> & vek2)
{
    Vect<T> vek(vek1.size());
    for(size_t i=0;i<vek.size();i++)
    {
        vek[i]=vek1[i]+vek2[i]; 
    }    
    std::cout<<vek<<std::endl;
    return vek;
}
template <typename T>
Vect<T> operator-(const Vect<T> & vek1,const Vect<T> & vek2)
{
    Vect<T> vek(vek1.size()>=vek2.size() ? vek1.size():vek2.size());
    for(size_t i=0;i<vek.size();i++)
        vek[i]=vek1[i]-vek2[i];
    return vek;
}
template <typename T>
std::ostream & operator<<(std::ostream & out,const Vect<T> & vek){
    out << "[";
    if(vek.size()!=0)
    {
        for(size_t i=0;i<vek.size()-1;++i)
            out<<vek[i]<<",";
        out<<vek[vek.size()-1];
    }
    out<<"]";
    return out;
}
template <typename T>
void Vect<T> :: free()
{
    size_t velicina=this->size();
    for(size_t i=0;i<velicina;++i)
    {
        alloc.destroy(mdata+i);
    }
    alloc.deallocate(mdata,this->capacity());
    mend=mfirst_free=mdata=nullptr;
}
template <typename T>
void Vect<T> :: reallocate()
{
    if(mdata==mend)
    {
        mdata=alloc.allocate(1);
        mfirst_free=mdata;      
        mend=mdata+1;
    }
    else {
        size_t velicina=this->size();
        Vect<T> v(velicina);
        for(size_t i=0;i<velicina;++i)
            v[i]=mdata[i];
        auto *data=mdata;
        this->free();       
        do{
            mdata=alloc.allocate(velicina*2);
        }while(mdata==data);
        for(size_t i=0;i<velicina;++i)
            *(mdata+i)=v[i];
        mfirst_free=mdata+velicina;
        mend=mdata+velicina*2;
        v.free();
    }
}
template <typename T>
double Vect<T>::two_norm() const
{
    double suma=0;
    for(size_t i=0;i<this->size();++i)
    {
        suma+=mdata[i]*mdata[i];
    }
    return sqrt(suma);
}