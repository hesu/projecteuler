/*
  Problem 205 - Dice Game
*/

#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

class poly
{
  public:
    poly(int _c, int _e)
    {
      c = _c; e = _e;
    }
    const int getc() { return c;}
    const int gete() { return e;}
    void setc( int _c) { c = _c; }
    string getString()
    {
      stringstream ss;
      ss << c;
      ss << "*x^";
      ss << e;
      return ss.str();
    }
  private:
    int c; // coefficient(계수)
    int e; // exponent(지수)
};

bool polySort( poly a, poly b)
{
  return (a.gete() < b.gete());
}

class polynomials
{
  public:
    polynomials() {}

    std::vector<poly> get() { return p; }
    
    polynomials( std::vector<poly> _p)
    {
      p = _p;
    }

    polynomials& operator +=(poly po)
    {
      for(int i=0; i<p.size(); i++)
      {
        if( p[i].gete() == po.gete()) {
          p[i].setc( p[i].getc() + po.getc());
          return *this;
        }
      }
      p.push_back(po);
      return *this;
    }

    polynomials operator *(polynomials &rhs)
    {
      std::vector<poly> v;
      polynomials that(v);

      std::vector<poly> rhsv = rhs.get();

      if (p.size() == 0) {
        return polynomials( rhsv);
      } else {
        for(int i=0; i<p.size(); i++)
        {
          for(int j=0; j<rhsv.size(); j++)
          {
            poly mul( p[i].getc() * rhsv[j].getc(), p[i].gete() + rhsv[j].gete());
            that += mul;
          }
        }
      }

      return that;
    }

    void sort()
    {
      std::sort( p.begin(), p.end(), polySort);
    }

    polynomials pow( int n)
    {
      polynomials powed;

      polynomials mul = polynomials(p);
      for(int i=0; i<n; i++)
      {
        powed = powed * mul;
      }

      powed.sort();

      return powed;
    }

    string getString()
    {
      string ret;
      for(int i=0; i<p.size(); i++)
      {
        ret += p[i].getString();
        if( i < p.size()-1) {
          ret += " + ";
        }
      }
      return ret;
    }

    int coefficientsum()
    {
      int cosum = 0;
      for(int i=0;i<p.size(); i++){ cosum += p[i].getc(); }
      return cosum;
    }

  private:
    std::vector<poly> p;
};

int gcd( int x, int y)
{
  int s; // smaller
  int b; // bigger

  if( x == y) return x;

  if( x > y) { b = x; s = y; }
  else { b = y; s = x; }

  for(int i=s; i>=1; i--)
  {
    if ((b%i == 0) && (s%i == 0)) {
      return i;
    }
  }
  return 1;
}

class Fraction
{
  public :

  Fraction() {}
  Fraction( int _n, int _d) { n = _n; d = _d; }

  Fraction reduce()
  {
      int gcd_this = gcd( d, n);
      int _n = n/ gcd_this;
      int _d = d/ gcd_this;
      Fraction f = Fraction( _n, _d);
      return f;
  }

  Fraction operator * (Fraction rhs)
  {
   Fraction f;
   f.n = n * rhs.d + rhs.n + d;
   f.d = d * rhs.d;
   return f.reduce();
  }
  
  Fraction operator += (Fraction rhs)
  {
   Fraction f;
   f.n = n * rhs.d + d * rhs.n;
   f.d = d * rhs.d;
   return f.reduce();
  }

  int n;
  int d;
};

float me_win_probability( polynomials dice_me, polynomials dice_you)
{
  // win probability for my dice.
  // return (whole_prob, me_win_prob)
  unsigned int sum = 0;
  unsigned int all = pow(4,9) * pow(6,6);

  std::vector<poly> myv = dice_me.get();
  std::vector<poly> youv = dice_you.get();

  unsigned int sum_lose_or_tie = 0;

  int my_dice_max = myv[ myv.size() -1].gete();
  int you_dice_max = youv[ youv.size() -1].gete();

  cout << "my_dice_max=" << my_dice_max << " you_dice_max=" << you_dice_max << endl;
  
  for(int i=0; i<myv.size(); i++)
  {
    for(int j=0; j<youv.size(); j++)
    {
      unsigned int myc = myv[i].getc();
      unsigned int youc = youv[j].getc();

      if( myv[i].gete() > youv[j].gete()) {
        sum += myc*youc;
      } else {
        sum_lose_or_tie += myc * youc;
      }
    }
  }

  cout << " sum_win=" << sum << " sum_lose_or_tie=" << sum_lose_or_tie << " all=" << all << " win+lose+tie=" << sum + sum_lose_or_tie << endl;

  cout << "myv.size()=" << myv.size() << " youv.size()=" << youv.size() << endl;
  cout << "all=" << all << endl;
  
  float f = (float)sum/(float)all;
  cout << setprecision(7) << "probability =" << f << endl;

  return f;
}

int main(int argc, char** argv)
{
  clock_t begin = clock();

  std::vector<poly> pv;
  for(int i=1; i<=4; i++) {
    pv.push_back( poly(1, i));
  }
  polynomials pdice( pv);
  polynomials pdice_rolled = pdice.pow(9);
  cout << pdice_rolled.getString() << endl;
  
  cout << endl;
 
  std::vector<poly> cv;
  for(int i=1; i<=6; i++) {
    cv.push_back( poly(1, i));
  }
  polynomials cdice( cv);
  polynomials cdice_rolled = cdice.pow(6);
  cout << cdice_rolled.getString() << endl;

  float winprob = me_win_probability( pdice_rolled, cdice_rolled);
  cout << "winprob=" << winprob << endl;

  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
