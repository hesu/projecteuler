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
int main(int argc, char** argv)
{
	clock_t begin = clock();
	
	/* starting code */

	BigInt f(1393);
	BigInt s(985);
	s = f+s;
	cout << "expected=" << 1393+985 << endl;
	cout << "s="; s.print(); cout << endl;

cout << "START!";
	int count = 0;
	BigInt n = BigInt(3); // numerator 
	BigInt d = BigInt(2); // denominator
	
	for(int i=1; i<=10; i++)
	{
		n.print(); cout << "/"; d.print(); cout << endl;
		if( n.getDigitsLen() > d.getDigitsLen()) {
			count++;
		}

		BigInt swp; swp.copy(n);
//		cout << "n="; n.print(); cout << " d="; d.print(); cout << " swp="; swp.print(); cout << endl;
		n = n+d+d;
//		cout << "now get d.." << endl;
//		cout << "swp="; swp.print(); cout << endl;
//		cout << "d="; d.print(); cout << endl;
		d = swp + d; 
	}
	cout << "count=" << count << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
