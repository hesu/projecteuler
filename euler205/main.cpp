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
    int getc() { return c;}
    int gete() { return e;}
    void setc( int _c) { c = _c; }
    string getString()
    {
      stringstream ss;
      ss << c;
      ss << "X^";
      ss << e;
      return ss.str();
    }
  private:
    int c; // coefficient(계수)
    int e; // exponent(지수)
};

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

    polynomials pow( int n)
    {
      polynomials powed;

      polynomials mul = polynomials(p);
      for(int i=0; i<n; i++)
      {
        powed = powed * mul;
      }
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

vector<Fraction> me_win_probability( polynomials dice_me, polynomials dice_you)
{
  // win probability for my dice.
  // return (whole_prob, me_win_prob)

  std::vector<Fraction> fv;

  int myall = dice_me.coefficientsum();
  int youall = dice_you.coefficientsum();
  int all = myall * youall;

  std::vector<poly> myv = dice_me.get();
  std::vector<poly> youv = dice_you.get();
  
  for(int i=0; i<myv.size(); i++)
  {
    for(int j=0; j<youv.size(); j++)
    {
      int myc = myv[i].getc();
      int youc = youv[j].getc();

      if( myv[i].gete() > youv[j].gete()) {
//        Fraction f = Fraction(myc, myall) * Fraction( youc, youall);

////////////////////////
//      식이 이게 아닌가..
//      맞는다고 생각했는데 계속 오답이 나옴.
//      나중에 다시 고민해 보자.
        Fraction f = Fraction( myc * youc , all);
////////////////////////

        fv.push_back( f);
      }
    }
  }

  int intsum = 0;
  cout << "get sum.." << endl;
  Fraction sum = Fraction(0,1);
  for(int i=0; i<fv.size(); i++)
  {
    intsum += fv[i].n;
//    sum += fv[i];
  }

  cout << "sum : ( " << sum.n << "," << sum.d << ")" << endl;
  cout << "intsum : " << intsum << endl;
  cout << "all=" << all << " myall=" << myall << " youall = " << youall << endl;
  cout << "my.size=" << myv.size() << " you.size=" << youv.size() << " f.size()=" << fv.size() << endl;
  //Fraction sumf( sum, all);
  //return sumf;
  return fv;
}

int main(int argc, char** argv)
{
  clock_t begin = clock();

  // 주사위 여러개 = (x + x^2 + .. x^n, n=주사위 제일 큰눈) 인 다항식을 주사위 개수만큼 곱한후,
  // 계수를 구하면 될듯.
  // 따라서 다항식 코드를 구현해야함.
  std::vector<poly> v;
  for(int i=1; i<=4; i++) v.push_back( poly(1, i));
  polynomials pdice( v);
  polynomials pdice_rolled = pdice.pow(9);
  cout << pdice_rolled.getString() << endl;

  cout << endl;
  std::vector<poly> v2;
  for(int i=1; i<=6; i++) v2.push_back( poly(1, i));
  polynomials cdice( v);
  polynomials cdice_rolled = pdice.pow(6);
  cout << cdice_rolled.getString() << endl;

  vector<Fraction> winprob = me_win_probability( pdice_rolled, cdice_rolled);
//  cout << " winprob n=" << winprob.n << " d=" << winprob.d << endl;

  int intsum = 0;
  for(int i=0; i<winprob.size(); i++)
  {
    intsum += winprob[i].n;
//    cout << "(" << winprob[i].n << "/" << winprob[i].d << ")" << endl;
  }

//  cout << setprecision(7) << (float)winprob.n/(float)winprob.d << endl;

  cout << setprecision(7) << (float)intsum/(float)winprob[0].d << endl;

  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
