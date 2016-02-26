#include "BigInt.h"

using namespace std;
class Fraction
{
	private : 
		BigInt numerator;
		BigInt denominator;
	public :
		Fraction(){}

		void setFraction( BigInt& n, BigInt& d)
		{
			numerator.copy( n);
			denominator.copy( d);
		}

		void print() { cout << numerator.toint() << "/" << denominator.toint(); }

		Fraction operator + (Fraction& rhs){
			BigInt commonD = BigInt( lcm( denominator, rhs.get_denominator()));

			BigInt quo = commonD / denominator;
			BigInt myN = numerator * quo;

			BigInt quo2 = commonD / rhs.get_denominator();
			BigInt rhsN = rhs.get_numerator() * quo2; 
			BigInt lastN = BigInt( myN + rhsN);
			Fraction r;
			r.setFraction( lastN, commonD); //r.reduce();
			return r;
		}

		BigInt get_denominator() { return denominator; }
		BigInt get_numerator() { return numerator; }
};
