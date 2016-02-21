/*
 	Problem 57 - Square root convergents 
*/
	
#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <string.h>

using namespace std;

#define BIGINTMAX 100
class BigInt
{
	private:
		std::vector<int> dg; // digit
	public:
		BigInt() {}
		BigInt( int n) 
		{
			char buf[BIGINTMAX] = {0,};
			sprintf( buf, "%d", n);
			int len = strlen( buf);
			for(int i=len-1; i>=0; i--)
			{
				dg.push_back( buf[i]-'0');
			}
		}
		
		void setBigInt( BigInt& n) 
		{
			std::vector<int> ndg = n.getDigits();
			for(int i=0; i<ndg.size(); i++)
			{
				dg.push_back( ndg[i]);
			}
		}
		
		std::vector<int> getDigits() { return dg; }
		int getDigitsLen() { return dg.size(); }

		void print()
		{
			for(int i=dg.size()-1; i>=0; i--) { cout << dg[i]; }
			cout << endl;
		}

		void multiply(int m)
		{
			for(int i=0; i<dg.size(); i++) { dg[i] *= m; }

			int nextCarry = 0;
			for(int i=0; i<dg.size(); i++)
			{
				dg[i] += nextCarry;
				nextCarry = 0;
				while( dg[i] >= 10) {
					dg[i] -= 10;
					nextCarry++;
				}
			}

			while( nextCarry > 0) {
				if( nextCarry > 10) {
					dg.push_back( nextCarry%10);
					nextCarry /=10;	
				} else {
					dg.push_back( nextCarry);
					nextCarry = 0;
				}
			}
		}

		BigInt operator + (BigInt &rhs) // TODO
		{
			BigInt ret = BigInt(0);
			std::vector<int> retdg = ret.getDigits();

			int rhslen = rhs.getDigitsLen();
			std::vector<int> rhsdg = rhs.getDigits();
			
			int len = getDigitsLen();
			for(int i=0; i<len; i++) {
				if( rhslen-1 >= i) { retdg[i] += dg[i] + rhsdg[i]; }
			}

			if( rhslen > len) {
				for(int i=len; i<rhslen; i++) { retdg.push_back( rhsdg[ i]); }
			}
		
			int carry = 0;
			for(int i=0; i<getDigitsLen(); i++)
			{
				retdg[i] += carry; carry = 0;
				if( retdg[i] >= 10) { carry += retdg[i]/10; }
				retdg[i] = retdg[i]%10;
			}

			if (carry > 0) { retdg.push_back( carry); }
			return ret;
		}

		unsigned long long int operator /( BigInt &rhs)
		{
			return (this->toint() / rhs.toint());
		}

		unsigned long long int toint()
		{
			int toi = 0;
			for(int i=0; i<dg.size(); i++) { toi += pow(10, i) * dg[i]; }
			return toi;
		}
};

int lcm( int x, int y)
{
	int s, b; // smaller, bigger;
	
	if( x>y) { s = y; b = x; } else { s = x; b = y;}
	if( b%s == 0) { return b;}

	int lcm;
	for(int i=1;; i++)
	{
		lcm = s*i;
		if( lcm % b ==0) { break; }
	}
	return lcm;
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
			numerator.setBigInt( n);
			denominator.setBigInt( d);
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
	Fraction next = Fraction( inverse.get_denominator(), inverse.get_numerator());
	return next;
}

int main(int argc, char** argv)
{
	clock_t begin = clock();
	
	/* starting code */
	/*
	Fraction n = Fraction(1,2); n.print(); cout << endl; 
	Fraction gn = getNextFraction( n); gn.print(); cout << endl;
	Fraction ggn = getNextFraction( gn); ggn.print(); cout << endl; 
	
	int count = 0;
	Fraction next = Fraction(1,2);
	for(int i=1; i<=1000; i++)
	{
		cout << "at=" << i << " "; 
		Fraction got = Fraction(1,1) + next;
		BigInt d = got.get_denominator();
		BigInt n = got.get_numerator();
		got.print(); cout << endl;
		if( n.getDigitsLen() > d.getDigitsLen()) { count++; }
		next = getNextFraction(next);
	}
	return count;
	*/

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
