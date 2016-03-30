/*
 	Problem 61 - Cyclical figurate numbers
*/
	
#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <cmath>

#include <string.h>
#include <algorithm>
using namespace std;

std::map<int,int> triangle;
void getTriangle( int min, int max)
{
	for(int i=1; i<max; i++)
	{
		int t = i*(i+1)/2;
		if( t >= min && t <= max) { triangle.insert( std::map<int,int>::value_type(t,t)); }
		if( t > max) { break;}
	}
}

std::map<int,int> square;
void getSquare( int min, int max)
{
	for(int i=1; i<max; i++)
	{
		int s = i*i;
		if( s >= min && s <= max) { square.insert( std::map<int,int>::value_type(s,s)); }
		if( s > max) { break;}
	}
}

std::map<int,int> pentagonal;
void getPentagonal( int min, int max)
{
	for(int i=1; i<max; i++)
	{
		int p = i*(3*i-1)/2;
		if( p >= min && p <= max) { pentagonal.insert( std::map<int,int>::value_type(p,p)); }
		if( p > max) { break;}
	}
}

std::map<int,int> hexagonal;
void getHexagonal( int min, int max)
{
	for(int i=1; i<max; i++)
	{
		int h = i*(2*h-1);
		if( h >= min && h <= max) { hexagonal.insert( std::map<int,int>::value_type(h,h)); }
		if( h > max) { break;}
	}
}

std::map<int,int> heptagonal;
void getHeptagonal( int min, int max)
{
	for(int i=1; i<max; i++)
	{
		int h = i*(5*i-3)/2;
		if( h >= min && h <= max) { heptagonal.insert( std::map<int,int>::value_type(h,h)); }
		if( h > max) { break;}
	}
}

std::map<int,int> octagonal;
void getOctagonal( int min, int max)
{
	for(int i=1; i<max; i++)
	{
		int o = i*(3*i-2);
		if( o >= min && o <= max) { octagonal.insert( std::map<int,int>::value_type(o,o)); }
		if( o > max) { break;}
	}
}

bool findCyclical( int n, int figurate)
{
	cout << "f=" << figurate << endl;
	if (n < 1000) return false;
	std::map<int,int>::iterator it;
	if (figurate == 3) {
		it = triangle.find(n);
		if (it == triangle.end()) return false;
	} else if (figurate == 4) {
		it = square.find(n);
		if (it == square.end()) return false;
	} else if (figurate == 5) {
		it = pentagonal.find(n);
		if (it == pentagonal.end()) return false;
	} else if (figurate == 6) {
		it = hexagonal.find(n);
		if (it == hexagonal.end()) return false;
	} else if (figurate == 7) {
		it = heptagonal.find(n);
		if (it == heptagonal.end()) return false;
	} else if (figurate == 8) {
		it = octagonal.find(n);
		if (it == octagonal.end()) return false;
	} else {
		cout << "true! n=" << n << endl;
		return true;
	}

	char buf[8]= {0,};
	sprintf( buf, "%d", n);

	char b1[8] = {0,}; char b2[8] = {0,};
	strncpy( b1, buf, 2);
	strncpy( b2, buf+2, 2);
	sprintf( buf, "%d%d", atoi(b2), atoi(b1));
	int newn = atoi( buf);
	cout << "n=" << n <<  " figurate=" << figurate << " newn=" << newn << endl;
	return findCyclical( newn, figurate+1);
}

int main(int argc, char** argv)
{
	clock_t begin = clock();
	
	/* starting code */
	getTriangle( 1000, 9999);
	getSquare( 1000, 9999);
	getPentagonal( 1000, 9999);
	getHexagonal( 1000, 9999);
	getHeptagonal( 1000, 9999);
	getOctagonal( 1000, 9999);

	cout << "triangle=" << triangle.size() << " square=" << square.size() << " pentagonal=" << pentagonal.size() << " hexagonal=" << hexagonal.size() << " heptagonal=" << heptagonal.size() << " octagonal=" << octagonal.size() << endl;

	for(std::map<int,int>::iterator it = triangle.begin(); it != triangle.end(); it++)
	{
		//		cout << "triangle : " << it->first << endl;
		bool find = findCyclical( it->first, 3);
		if( find) {
			cout << "found triangle= " << it->first << endl;
			break;
		}
	}

	/* end of code */
	clock_t end = clock();
	cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << endl;
	return 0;
}
