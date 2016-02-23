/*
 	Problem 57 - Square root convergents 
*/
	
#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <string.h>

#include "BigInt.h"

using namespace std;

BigInt lcm( BigInt x, BigInt y)
{
	BigInt s, b; // smaller, bigger;
	if( x < y) { s = x; b = y; } else { s = y; b = x; }
	if( (b % s).toint() == 0){ return b; }

	BigInt l;
	for(int i=1;; i++)
	{
		BigInt bi = BigInt(i);
		l = s * bi;
		if( (l % b).toint() == 0) { break; }
		else { 
//			(l % b).print();
//			cout << "try l=" << l.toint() << " b=" << b.toint() << " l % b=" << (l%b).toint() << endl;
		}
	}
	return l;
}

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
			BigInt commonD = BigInt( lcm( denominator.toint(), rhs.get_denominator().toint()));
			unsigned long long int myN = numerator.toint() * ( commonD.toint() / denominator.toint());
			unsigned long long int rhsN = rhs.get_numerator().toint() * ( commonD.toint() / rhs.get_denominator().toint());
			BigInt lastN = BigInt( myN + rhsN);
			Fraction r;
			r.setFraction( lastN, commonD); //r.reduce();
			return r;
		}

		BigInt get_denominator() { return denominator; }
		BigInt get_numerator() { return numerator; }
};

Fraction getNextFraction( Fraction& before)
{
	BigInt two = BigInt(2);
	BigInt one = BigInt(1);
	Fraction start; start.setFraction( two, one);
	Fraction inverse = start + before;

	BigInt d = BigInt( inverse.get_denominator());
	BigInt n = BigInt( inverse.get_numerator());
	Fraction next; next.setFraction( d, n); 
	return next;
}

int main(int argc, char** argv)
{
	clock_t begin = clock();
	
	/* starting code */
	int count = 0;
	BigInt o = BigInt(1);
	BigInt t = BigInt(2);
	Fraction next; next.setFraction(o,t);
	for(int i=1; i<=1000; i++)
	{
		cout << "at=" << i << " "; 
		Fraction one; one.setFraction( o, o);
		Fraction got = one + next;
		BigInt d = got.get_denominator(); BigInt n = got.get_numerator();
		got.print(); cout << endl;
		if( n.getDigitsLen() > d.getDigitsLen()) { count++; }
		next = getNextFraction(next);
	}
	return count;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
