#pragma once
#include <random>

// Klasa koja predstavlja generator slučajnih brojeva tipa int uniformno distribuiranih 
// u zadanom rasponu.  Sučelje klase je dano ovdje:
class RandomInt{
  public:
     RandomInt(int a, int b);
     RandomInt(RandomInt const & rhs);
     RandomInt & operator=(RandomInt const & rhs) = delete;
     int operator()();
  private:
     int a,b;
     std::uniform_int_distribution<int> uniform_dist;
     std::default_random_engine e;
};

RandomInt::RandomInt(int aa, int bb): a(aa),b(bb), uniform_dist(aa,bb), e(std::random_device()())
{
  
}
RandomInt::RandomInt(RandomInt const & rhs): a(rhs.a),b(rhs.b), uniform_dist(rhs.a,rhs.b), e(std::random_device()())
{

}
int RandomInt::operator()()
{
    return uniform_dist(e);
}

/*  
- a, b su granice distribuiranih int-ova;
- konstruktor kopije (i konstruktor) mora postaviti novi _seed_ kako kopija ne bi 
  generirala isti niz kao i original;
- operator() generira novu pseudoslučajnu vrijednost.
*/


