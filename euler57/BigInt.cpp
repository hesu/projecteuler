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
		
		void copy( BigInt& n) 
		{
			std::vector<int> ndg = n.getDigits();
			for(int i=0; i<ndg.size(); i++)
			{
				dg.push_back( ndg[i]);
			}
		}

		void setdg( std::vector<int> _dg) { dg = _dg; }
		
		std::vector<int> getDigits() const { return dg; }
		int getDigitsLen() const { return dg.size(); }

		void print()
		{
			for(int i=dg.size()-1; i>=0; i--) { cout << dg[i]; }
			cout << endl;
		}

		BigInt operator * (BigInt &rhs)
		{
			BigInt r;
			std::vector<int> retdg;
			
			std::vector<int> rdg = rhs.getDigits();	
			for(int i=0; i<dg.size(); i++)
			{
				for(int j=0; j<rdg.size(); j++)
				{
					int val = dg[i] * rdg[j];
					while( retdg.size() <= i+j) {
						retdg.push_back(0);
					}
					retdg[i+j] += val;
				}
			}

			int nextCarry = 0;
			for(int i=0; i<retdg.size(); i++)
			{
				retdg[i] += nextCarry;
				nextCarry = 0;
				while( retdg[i] >= 10) {
					retdg[i] -= 10;
					nextCarry++;
				}
			}

			while( nextCarry > 0) {
				if( nextCarry > 10) {
					retdg.push_back( nextCarry%10);
					nextCarry /=10;	
				} else {
					retdg.push_back( nextCarry);
					nextCarry = 0;
				}
			}

			r.setdg( retdg);
			return r;
		}

		BigInt operator + (BigInt &rhs)
		{
			BigInt ret; 
			std::vector<int> retdg;
			for(int i=0; i<getDigitsLen(); i++)
			{
				retdg.push_back(0);
			}

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
			ret.setdg( retdg);
			
			return ret;
		}

		BigInt& operator - (BigInt &rhs)
		{
			std::vector<int> retdg; for(int i=0; i<dg.size(); i++) { retdg.push_back( dg[i]); }

			for(int i=rhs.getDigitsLen()-1; i>=0; i--)
			{
				int retval = dg[i] - rhs.getDigits()[i];
				int j = i;
				while( retval < 0) {
					retdg[j+1]--;
					retdg[j] += 10;
					retval = retdg[j+1];
					j++;
				}
				retdg[i] = retdg[i] - rhs.getDigits()[i];
			}

			for(int i= retdg.size()-1; i>=0; i--)
			{
				if( retdg[i] != 0) break;
				retdg.pop_back();
			}

			BigInt* ret = new BigInt(); ret->setdg( retdg);
			return *ret;
		}

		BigInt& operator /( BigInt &rhs)
		{
			BigInt that; that.setdg( dg);
			cout << "operator /. and first that=" << that.toint() << endl;
			int q = 0;
			BigInt zero = BigInt(0);

			while( zero < that - rhs) { 
				cout << "try to minus. now value=" << that.toint() << endl;
				that = that - rhs;
				q++;
			}
			cout << "return that." << endl;

			BigInt* quo = new BigInt( q);
			return *quo;
		}
		
		BigInt& operator %( BigInt &rhs)
		{
			cout << "%" << endl;
			BigInt* that = new BigInt(); that->setdg( dg);
				cout << "that=" << that->toint() << endl;
			BigInt zero = BigInt(0);
			while( zero < *that) {
				*that = *that - rhs;
			}
			return *that;
		}

		bool operator <( BigInt const &rhs)
		{
			const int llen = getDigitsLen();
			const int rlen = rhs.getDigitsLen();
			if( llen != rlen) { return (llen < rlen); }
			std::vector<int> rdg = rhs.getDigits();
			for(int i=rlen-1; i>=0; i--)
			{
				if( dg[i] == rdg[i]	) { continue; }
				return (dg[i] < rdg[i]);
			}
			return false;
		}

		unsigned long long int toint()
		{
			int toi = 0;
			for(int i=0; i<dg.size(); i++) { toi += pow(10, i) * dg[i]; }
			return toi;
		}
};

int main(int argc, char** argv)
{
	clock_t begin = clock();
	
	/* starting code */
	BigInt n1= BigInt(2);
	n1.print();

	BigInt n2 = BigInt(501);
	n2.print();

	cout << "get quota" << endl;
	BigInt quo = n2 / n1;
	quo.print();
/*
	BigInt remain = n2 % n1;
	remain.print();
	*/

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
