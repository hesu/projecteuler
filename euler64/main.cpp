/*
 	Problem 64 - Odd period square roots
*/
	
#include <iostream>
#include <ctime>
#include <cmath>

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
		// TODO
		return f;
	}

	int getn() { return n; }

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

int main(int argc, char** argv)
{
	clock_t begin = clock();
	
	/* starting code */
	SquareRoot s = SquareRoot( 23);
	Fraction f; f.set(s, 0, NULL, 0, NULL, 0);
	f.print(); cout << endl;

	// TODO

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
