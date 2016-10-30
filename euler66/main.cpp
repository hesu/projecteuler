/*
  Problem 66 - Diophantine equation
*/

#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>
#include <algorithm>

#include "BigInt.h"

using namespace std;

class SquareRoot
{
	private :
	int n;

	public :
	SquareRoot() {};
	SquareRoot( int _n) { n = _n; }
	int getn() { return n; }
	void print()
	{
		cout << "sq(" << n << ")";
	}
};

int getnearby( SquareRoot sr)
{
	int nearby;
	for(int i=1;; i++) { if (pow(i, 2) <= sr.getn() && pow(i+1, 2) >= sr.getn()) { nearby = i; break; } }
	return nearby;
}

class Fraction
{
	private :
	// denominator
	SquareRoot dsr; int dn; 
	// numerator
	SquareRoot nsr; int nn;
	// n
	int n; SquareRoot sr;

	public :
	Fraction() {}

	void set( SquareRoot _sr, int _n, SquareRoot _dsr, int _dn, SquareRoot _nsr, int _nn)
	{
		sr = _sr; n = _n; dsr = _dsr; dn =_dn; nsr = _nsr; nn = _nn;
	}

	Fraction getConversed()
	{
		Fraction f;
		f.set( NULL, 0, nsr, nn, dsr, dn);
		return f;
	}

	Fraction getRationalized()
	{
		Fraction f;
		// intermediate
		int f_dn = (dsr.getn() - ( dn * dn)) / nn;
		SquareRoot f_nsr( dsr.getn());
		int f_nn = (dn * -1);
		int nearby = getnearby( dsr);
	
		// set final
		int f_n = (int)((nearby + f_nn) / f_dn);
		f.set( NULL, f_n, NULL, f_dn, f_nsr, f_nn - (f_n * f_dn));
		return f;
	}

	Fraction copy()
	{
		Fraction f;
		f.set( sr, n, dsr, dn, nsr, nn);
		return f;
	}

	bool hasSameFractionWith( Fraction f)
	{
		return 
			((dsr.getn() == f.getdsr().getn()) && ( dn == f.getdn()) 
			&&
			(nsr.getn() == f.getnsr().getn()) && ( nn == f.getnn()));
	}

	int getn() { return n; }
	SquareRoot getdsr() { return dsr; }
	int getdn() { return dn; }
	SquareRoot getnsr() { return nsr; }
	int getnn() { return nn; }

	void print()
	{
		cout << "(";
		if( sr.getn() != 0) {  sr.print(); }
		if( n != 0) { cout << "+" << n; }
		cout << ") + (";

		if( nsr.getn() != 0) { nsr.print(); }
		if( nn != 0) { cout << "+" << nn; }
		cout << "/";
		
		if( dsr.getn() != 0) { dsr.print(); }

		if( dn != 0) {
			if( dn > 0 ) { cout << "+" << dn; }
			else { cout << dn; }
		}
		cout << ")";
	}

};

Fraction getFirstFraction( int n)
{
	SquareRoot s(n);
	int nearby = getnearby( s);
	Fraction f;
	f.set( NULL, nearby, s, (-1)*nearby, NULL, 1);
	return f;
}


BigInt convergent_until_equation_solved( int di)
{
  BigInt b;

  BigInt de; // bunmo
  BigInt nu; // bunja

  return b;
}

int main(int argc, char** argv)
{
  clock_t begin = clock();

  std::vector<int> dvec;
  for(int i=1; i<=1000; i++)
  {
    double sqrted = sqrt( i);
    if( sqrted != ceil(sqrted)) {
      dvec.push_back(i); 
    }
  }
  cout << "dvec.size()=" << dvec.size() << endl;

  BigInt maxX(0);
  int atD;

  //for(int i=0; i<dvec.size(); i++)
  for(int i=0; i<1; i++)
  {
//    int di = dvec[i];
    int di = 7;

    cout << "di=" << di << endl;
    int seq=0;
    Fraction first = getFirstFraction( di);
    first.print(); cout << endl;
    Fraction next = first.copy();
    while( true)
    {
      seq++;
      next = next.getRationalized();
      next = next.getConversed();
      next.print(); cout << endl;

      // 이렇게 다음 연분수를 구해나가긴 하지만, 
      // 여기서 내가 관심있는 것은.. 분자/분모 로 이뤄진, 유리 근사값임.
      // if approximate fraction 'denominator, numerator' meets equation
      // equation solved. break!

      if( seq > 1000) break;
    }

    // get Convergent SquareRoot(di) while convergent x,y meets x^2 - Dy^2 = 1
    //BigInt x = convergent_until_equation_solved( di ); 
  }

  cout << "maxX = " << maxX.toString() << " at d=" << atD << endl;

  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
