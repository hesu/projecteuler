#include <iostream>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <string.h>

using namespace std;

#define BIGINTMAX 10000
class BigInt
{
	private:
		std::vector<int> dg; // digit
	public:
		BigInt() {};
		BigInt( int n)
		{
			char buf[BIGINTMAX] = {0,};
			sprintf( buf, "%d", n);
			int len = strlen( buf);
			for(int i=len-1; i>=0; i--)
			{
				dg.push_back( buf[i]-'0');
			}
		};
		
    BigInt( std::vector<int> v)
		{
      dg = v;
		};
		void copy( BigInt& n);
		
    void setIdxVal( int idx, int val);
		int getIdxVal( int idx);

		void setdg( std::vector<int> _dg) { dg = _dg; }
		inline std::vector<int> getDigits() const { return dg; }
		int getDigitsLen() const { return dg.size(); }
		void print();
		BigInt operator * (BigInt &rhs);
		BigInt multiply (BigInt &rhs, int maxdigit);
		BigInt operator + (BigInt rhs);
		BigInt operator - (BigInt &rhs);
		BigInt operator /( BigInt rhs);
		BigInt operator %( BigInt &rhs);

		void shift(int n); 
		bool operator <( BigInt const &rhs);
		bool operator <=( BigInt const &rhs);
		unsigned long long int toint();

		string toString();
};

class Fraction
{
	private : 
		BigInt numerator;
		BigInt denominator;
	public :
		Fraction(){}

		void setFraction( BigInt& n, BigInt& d);
		void print();

		BigInt get_denominator() { return denominator; }
		BigInt get_numerator() { return numerator; }
};

