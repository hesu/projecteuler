/*
 	Problem 43 - Sub-string divisibility 
*/
	
#include <iostream>
#include <ctime>
#include <algorithm>
#include <cmath>

using namespace std;

#define SIZE 10

unsigned int toDigit( unsigned int *p, unsigned int size)
{
	unsigned int d = 0;
	for(int i=0; i<size; i++)
	{
		d += p[i] * pow( 10, size-i-1);
	}
	return d;
}

unsigned int divider[8] = { 1,2,3,5,7,11,13,17};
bool isSubStringDivisible( unsigned int arr[])
{
	for(int i=1; i<8; i++)
	{
		unsigned int d = toDigit( &arr[i], 3);
		if( toDigit( &arr[i], 3)%divider[i] != 0) {
			return false;
		}
	}
	return true;
}

int main(int argc, char** argv)
{
	clock_t begin = clock();
	/* starting code */

	/* test
	unsigned int t[SIZE] = { 1,4,0,6,3,5,7,2,8,9};
	cout << "isSubStringDivisible 1406357289? = " << isSubStringDivisible( t) << endl;
	unsigned int t2[SIZE] = { 4,1,0,6,3,5,7,2,8,9 }; 
	cout<< "toDigit 4106357289 = " << toDigit( t2, SIZE) << endl;
	*/

	unsigned int nums[SIZE] = {0,};
	for(int i=0; i<SIZE; i++){
		nums[i] = i;
	}
	std::sort( nums, nums+SIZE);

	unsigned long int sum = 0;
	do {
		if( isSubStringDivisible( nums)) {
			sum += toDigit( nums, SIZE);
			cout << "num=" << toDigit( nums, SIZE) << endl;
		}
	} while( std::next_permutation( nums, nums+SIZE));
	cout << "sum= " << sum << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
