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
//BigInt lcm( BigInt x, BigInt y) { return x*y; }
BigInt lcm( BigInt x, BigInt y)
{
	cout << "lcm" << endl;	
	BigInt s, b; // smaller, bigger;
	if( x < y) { s = x; b = y; } else { s = y; b = x; }
	if( (b % s).toint() == 0){ cout << "lcm return(1)" << endl; return b; }

	BigInt l;
	for(int i=1;; i++)
	{
		BigInt bi = BigInt(i);
		l = s * bi;
		if( (l % b).toint() == 0) { break; }
		else { 
		}
	}
	cout << "lcm return(2)" << endl;
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

Fraction getNextFraction( Fraction& before)
{
	BigInt two = BigInt(2);
	BigInt one = BigInt(1);
	Fraction start; start.setFraction( one, one);
	Fraction inverse = start + before;
//	cout << "inverse ="; inverse.print(); cout << endl;

	BigInt d = BigInt( inverse.get_numerator());
	BigInt n = BigInt( inverse.get_denominator());
	Fraction next; next.setFraction( n, d); 
	return next;
}

int main(int argc, char** argv)
{
	clock_t begin = clock();
	
	/* starting code */
/*	
	BigInt one = BigInt(1);
	BigInt o = BigInt(12);
	BigInt t = BigInt(5);

	Fraction n1; n1.setFraction( t, o);
	Fraction n2; n2.setFraction( one, one);

	Fraction n3 = n1 + n2;
	n3.print(); 
	cout << endl;
	*/

	int count = 0;
	BigInt o = BigInt(1);
	BigInt t = BigInt(2);
	Fraction next; next.setFraction(o,t);
	for(int i=1; i<=1000; i++)
	{
		cout << "at=" << i << " "; 
		Fraction one; one.setFraction( o, o);

		Fraction got = next + one;
		BigInt d = got.get_denominator(); BigInt n = got.get_numerator();
		if( n.getDigitsLen() > d.getDigitsLen()) { count++; }
		got.print(); cout << endl;
		
		next = getNextFraction(got);
	}
	cout << "count=" << count << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
