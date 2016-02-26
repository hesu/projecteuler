
#include "BigInt.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <string.h>

using namespace std;

void BigInt::copy( BigInt &n)
{
	std::vector<int> ndg = n.getDigits();
	for(int i=0; i<ndg.size(); i++)
	{
		dg.push_back( ndg[i]);
	}
}

void BigInt::print()
{
	for(int i=dg.size()-1; i>=0; i--) { cout << dg[i]; }
}

BigInt BigInt::operator * (BigInt &rhs)
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

BigInt BigInt::operator + (BigInt rhs)
{
	BigInt ret; 
	std::vector<int> retdg;

	int bigger;
	int rhslen = rhs.getDigitsLen();
	int len = getDigitsLen();
	rhslen > len ? bigger = rhslen : bigger = len;

	for(int i=0; i<bigger; i++)
	{
		retdg.push_back(0);
	}

	std::vector<int> rhsdg = rhs.getDigits();
	for(int i=0; i<bigger; i++)
	{
		if( rhslen > i) {
			retdg[i] += rhsdg[i];
		}

		if( len > i) {
			retdg[i] += dg[i];
		}
	}

	int carry = 0;
	for(int i=0; i<retdg.size(); i++)
	{
		retdg[i] += carry; carry = 0;
		if( retdg[i] >= 10) { 
			carry += retdg[i]/10; 
			retdg[i] -= 10;
		}
	}

	if (carry > 0) { retdg.push_back( carry); }

	for(int i= retdg.size()-1; i>=0; i--)
	{
		if( retdg[i] != 0) break;
		retdg.pop_back();
	}
	ret.setdg( retdg);
	cout << endl;
	return ret;
}

BigInt BigInt::operator - (BigInt &rhs)
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

	BigInt ret; ret.setdg( retdg);
	return ret;
}

BigInt BigInt::operator /( BigInt rhs)
{
	BigInt that; that.setdg( dg);
	int q = 0;
	BigInt zero = BigInt(0);

	while( zero + rhs <= that) {
		that = that - rhs;
		q++;
	}

	BigInt quo = BigInt( q);
	return quo;
}
		
BigInt BigInt::operator %( BigInt &rhs)
{
	BigInt that; that.setdg( dg);
	BigInt zero = BigInt(0);
	while( zero + rhs <= that) {
		that = that - rhs;
	}
	return that;
}

bool BigInt::operator <( BigInt const &rhs)
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

bool BigInt::operator <=( BigInt const &rhs)
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
	return true;
}

unsigned long long int BigInt::toint()
{
	int toi = 0;
	for(int i=0; i<dg.size(); i++) { toi += pow(10, i) * dg[i]; }
	return toi;
}

