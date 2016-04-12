/*
 	Problem 64 - Odd period square roots
*/
	
#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>

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

int main(int argc, char** argv)
{
	clock_t begin = clock();
	
	/* starting code */
/*
	Fraction f0 = getFirstFraction(23);
	f0.print(); cout << endl;
	Fraction rf0 = f0.getRationalized();
	rf0.print(); cout << endl;

	Fraction f1; f1 = rf0.getConversed();
	f1.print(); cout << endl;
	Fraction rf1 = f1.getRationalized();
	rf1.print(); cout << endl;
	*/

	int oddcnt = 0;
	for(int i=1; i<=10000; i++)
	{
		if( sqrt(i) == floor( sqrt(i))) { continue; }
		
		Fraction first = getFirstFraction( i);
		int firstN = first.getn();

		int seq = 0;
		Fraction next = first.copy();
		while( true) {
			seq++;
			next = next.getRationalized();
			next = next.getConversed();
			if (next.hasSameFractionWith( first)) { break; }
		}
//		cout << "i=" << i << " seq=" << seq << endl;
		if( seq%2 == 1) { oddcnt++; }
	}

	cout << "oddcnt = " << oddcnt << endl;
	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
