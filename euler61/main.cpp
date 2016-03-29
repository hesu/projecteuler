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

bool findCyclical( int number, int figurate, int cycle)
{
	char buf[8]= {0,};
	sprintf( buf, "%d", number);

	int newNumber;
	return false;
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
		cout << "triangle : " << it->first << endl;
	}

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
