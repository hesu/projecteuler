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

	void conversion()
	{
		if( sr.getn() != 0 ) {
			int nearby;
			for(int i=1;; i++)
			{
				if (pow(i, 2) > sr.getn() && pow(i+1, 2) < sr.getn()) {
					nearby = i;
					break;
				}
			}

		}
	}

	void print()
	{
		if( sr.getn() != 0) {  sr.print(); }
	}

};

int main(int argc, char** argv)
{
	clock_t begin = clock();
	
	/* starting code */
	SquareRoot s = SquareRoot( 23);
	Fraction f; f.set(s, 0, NULL, 0, NULL, 0);

	f.print();
	cout << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
