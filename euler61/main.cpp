/*
 	Problem 61 - Cyclical figurate numbers
*/
	
#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <cmath>

//#include <string.h>
//#include <algorithm>
using namespace std;

int MAX = 100000;

std::map<string,std::vector<int>> triangle;
void getTriangle( int min, int max)
{
	for(int i=1; i<MAX; i++)
	{
		int t = i*(i+1)/2;
		string key = to_string(t).substr( 0, 2);
		
		if( t < min) continue; if( t > max) { break;}
		
		map<string,vector<int>>::iterator it = triangle.find( key);
		if( it != triangle.end()) {
			it->second.push_back( t);
		} else {
			// new insert
			std::vector<int> v;
			v.push_back(t);
			triangle.emplace( key, v);
		}

	}
}

std::map<string,std::vector<int>> square;
void getSquare( int min, int max)
{
	for(int i=1; i<MAX; i++)
	{
		int s = i*i;
		string key = to_string(s).substr( 0, 2);
		
		if( s < min) continue; if( s > max) { break;}

		map<string,vector<int>>::iterator it = square.find( key);
		if( it != square.end()) {
			it->second.push_back( s);
		} else {
			// new insert
			std::vector<int> v;
			v.push_back(s);
			square.emplace( key, v);
		}
	}
}

std::map<string,std::vector<int>> pentagonal;
void getPentagonal( int min, int max)
{
	for(int i=1; i<MAX; i++)
	{
		int p = i*(3*i-1)/2;
		string key = to_string(p).substr( 0, 2);
		
		if( p < min) continue; if( p > max) { break;}
		
		map<string,vector<int>>::iterator it = pentagonal.find( key);
		if( it != pentagonal.end()) {
			it->second.push_back( p);
		} else {
			// new insert
			std::vector<int> v;
			v.push_back(p);
			pentagonal.emplace( key, v);
		}

		if( p > max) { break;}
	}
}

std::map<string,std::vector<int>> hexagonal;
void getHexagonal( int min, int max)
{
	for(int i=1; i<MAX; i++)
	{
		int h = i*(2*h-1);
		string key = to_string(h).substr( 0, 2);
		
		if( h < min) continue; if( h > max) { break;}

		map<string,vector<int>>::iterator it = hexagonal.find( key);
		if( it != hexagonal.end()) {
			it->second.push_back( h);
		} else {
			// new insert
			std::vector<int> v;
			v.push_back(h);
			hexagonal.emplace( key, v);
		}

		if( h > max) { break;}
	}
}

std::map<string,std::vector<int>> heptagonal;
void getHeptagonal( int min, int max)
{
	for(int i=1; i<MAX; i++)
	{
		int h = i*(5*i-3)/2;
		string key = to_string(h).substr( 0, 2);
		
		if( h < min) continue; if( h > max) { break;}

		map<string,vector<int>>::iterator it = heptagonal.find( key);
		if( it != heptagonal.end()) {
			it->second.push_back( h);
		} else {
			// new insert
			std::vector<int> v;
			v.push_back(h);
			heptagonal.emplace( key, v);
		}

		if( h > max) { break;}
	}
}

std::map<string,std::vector<int>> octagonal;
void getOctagonal( int min, int max)
{
	for(int i=1; i<MAX; i++)
	{
		int o = i*(3*i-2);
		string key = to_string(o).substr( 0, 2);
		
		if( o < min) continue; if( o > max) { break;}
		
		map<string,vector<int>>::iterator it = octagonal.find( key);
		if( it != octagonal.end()) {
			it->second.push_back( o);
		} else {
			// new insert
			std::vector<int> v;
			v.push_back(o);
			octagonal.emplace( key, v);
		}

		if( o > max) { break;}
	}
}

// call ex ) findCyclical( TriangleN(0), now, sum, [ 4,5,6,7,8]);

bool findCyclical( int begin, int now, int sum, std::vector<int> todo)
{
	if( todo.size() <= 0) { 
		// end of recursion
		return true;
	}
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


	for( auto it = triangle.begin(); it != triangle.end(); it++)
	{
//		cout << "triangle key=" << it->first << " size=" << it->second.size() << endl;
		for( int i = 0; i< it->second.size(); i++)
		{
//			cout << "\t" << it->second[i];
			// TODO call findCycle code
		}
		cout << endl;
	}
	
	cout << "triangle=" << triangle.size() << " square=" << square.size() << " pentagonal=" << pentagonal.size() << " hexagonal=" << hexagonal.size() << " heptagonal=" << heptagonal.size() << " octagonal=" << octagonal.size() << endl;

	/* end of code */
	clock_t end = clock();
	cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << endl;
	return 0;
}
