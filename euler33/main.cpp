/*
 	Problem 33 - Digit cancelling Fractions 
*/
	
#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

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
		Fraction( int n, int d)
		{
			denominator = d;
			numerator = n;
		}

		void print()
		{
			cout << numerator << "/" << denominator;
		}

		Fraction reduce()
		{
			int gcd_this = gcd( denominator, numerator);
			int n = numerator / gcd_this;
			int d = denominator / gcd_this;
			Fraction f = Fraction( n, d);
			return f;
		}

		bool operator == ( Fraction& rhs)
		{
			Fraction lf = reduce();
			Fraction rf = rhs.reduce();

			if( (lf.get_denominator() == rf.get_denominator()) &&
				(lf.get_numerator() == rf.get_numerator())) {
				
				print();
				cout << " == ";
				rhs.print();
				cout << endl;

				return true;
			}
			return false;
		}

		int get_denominator() { return denominator; }
		int get_numerator() { return numerator; }

	private : 
		int denominator;
		int numerator;
};

int main(int argc, char** argv)
{
	clock_t begin = clock();
	
	/* starting code */
	std::vector<Fraction> l;

	// xa, ay
	for(int x=0; x <10; x++)
	{
		for(int y=0; y<10; y++)
		{
			for( int a=0; a<10; a++)
			{
				int xa = 10*x + a;
				int ay = 10*a + y;
				if( xa > 9 && ay > 9 && xa < 100 && ay < 100) {
					if( xa < ay && x < y) {
						Fraction o1 = Fraction( xa, ay);
						Fraction o2 = Fraction( x, y);
						if( o1 == o2) { 
							l.push_back(o1); 
						}
					}
				}
			}
		}
	}

	int d = 1;
	int n = 1; 
	for(int i=0; i<l.size(); i++)
	{
		l[i].print();
		cout << endl;
		n *= l[i].get_numerator();
		d *= l[i].get_denominator();
	}

	Fraction answer = Fraction( n, d).reduce();
	cout << "answer denominator = " << answer.get_denominator() << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
