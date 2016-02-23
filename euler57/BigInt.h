#include <iostream>
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
		void copy( BigInt& n);
		void setdg( std::vector<int> _dg) { dg = _dg; }
		inline std::vector<int> getDigits() const { return dg; }
		int getDigitsLen() const { return dg.size(); }
		void print();
		BigInt operator * (BigInt &rhs);
		BigInt operator + (BigInt &rhs);
		BigInt& operator - (BigInt &rhs);
		BigInt& operator /( BigInt &rhs);
		
		BigInt& operator %( BigInt &rhs);
		bool operator <( BigInt const &rhs);
		bool operator <=( BigInt const &rhs);
		unsigned long long int toint();
};

