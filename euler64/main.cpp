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

	Fraction getNextFraction()
	{
		Fraction next;
		if( sr.getn() != 0) {
			int nearby;
			for(int i=1;; i++) { if (pow(i, 2) <= sr.getn() && pow(i+1, 2) >= sr.getn()) { nearby = i; break; } }
			n = nearby;

			cout << "nearby=" << nearby<< endl;

			int diff = sr.getn() - pow(nearby, 2);
			SquareRoot nextNsr(sr.getn());

			next.set( NULL, 0, NULL, diff, nextNsr, nearby);
		} else if( dsr.getn() != 0) {
			// TODO	
			int nextDn = (dsr.getn() - pow( dn, 2))/(nn);
			cout << "nextDn=" << nextDn << endl;

			int nearby;
			for(int i=1;; i++) { if (pow(i, 2) <= dsr.getn() && pow(i+1, 2) >= dsr.getn()) { nearby = i; break; } }
			n = nearby;
			
			int nextNn = nn;
			while( nextNn <= 0) {
				n++;
				nextNn -= nextDn;
			}
			next.set( NULL, 0, nsr, nextDn, NULL, nextNn);
		}
			else if( dn != 0) {
			n = 1;
			next.set( NULL, 0, nsr, (dn-nn)*(-1), NULL, dn);
		} else {
			cout << "TODO" << endl;
		}
		return next;
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

	cout << "<newf0>" << endl;
	Fraction newf0 = f.getNextFraction();
	newf0.print(); cout << endl; 
	cout << "prev n=" << f.getn() << endl;

	Fraction newf1 = newf0.getNextFraction();
	cout << "<newf1>" << endl;
	newf1.print(); cout << endl;
	cout << "prev newf0=" << newf0.getn() << endl;
	
	Fraction newf2 = newf1.getNextFraction();
	cout << "<newf2>" << endl;
	newf2.print(); cout << endl;
	cout << "prev newf1=" << newf1.getn() << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
