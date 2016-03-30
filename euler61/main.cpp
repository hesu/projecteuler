/*
 	Problem 61 - Cyclical figurate numbers
*/
	
#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <cmath>

//#include <string.h>
#include <algorithm>
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

bool findCyclical( int begin, int now, int sum, std::vector<int> todo)
{
	if( todo.size() <= 0) { 
		// end of recursion
		//cout << "done" << endl;
		string bFirst = to_string(begin).substr( 0, 2);
		string nLast = to_string(now).substr( 2, 2);
		if (bFirst.compare( nLast) == 0) {
			cout << "begin=" << begin << " now=" << now << " sum=" << sum << endl;
		} else {
			cout << "begin=" << begin << " now=" << now << endl;
		}
		return true;
	}

	string nextKey = to_string(now).substr( 2, 2);
//	cout << "todo.size=" << todo.size() << " nextKey=" << nextKey << endl;
	for(int i=0; i<todo.size(); i++)
	{
		map<string,vector<int>>* m = NULL;

		if( todo[i] == 4) m = &square;
		else if( todo[i] == 5) m = &pentagonal;
		else if( todo[i] == 6) m = &hexagonal;
		else if( todo[i] == 7) m = &heptagonal;
		else if( todo[i] == 8) m = &octagonal;

		map<string,vector<int>>::iterator it;
		if (m != NULL) {
			it = m->find( nextKey);

			
			if (it != m->end()) {
				// dbg
				for(int i=0; i<todo.size(); i++) { cout << " "; } cout << "key=" << nextKey << endl;

				// make todo vector for next recursive
				std::vector<int> v(todo);
				v.erase( std::find(v.begin(),v.end(), todo[i]));
				cout << "v.size()=" << v.size() << endl;
				for(int j=0; j<it->second.size(); j++)
				{
					findCyclical( begin, it->second[j], sum + it->second[j], v);
				}
			} else {
	//			cout << "todo[i]=" << todo[i] << " key=" << nextKey << endl;
			}
		}
	}
	return false;
	/*
	std::vector<int> v( todo);
	v.pop_back();
	findCyclical( begin, now, sum, v);
	*/
}

int main(int argc, char** argv)
{
	clock_t begin = clock();
	
	/* starting code */
	getTriangle( 1000, 9999);
	getSquare( 1000, 9999);
	getPentagonal( 1000, 9999);
	getHexagonal( 1000, 9999);
//	getHeptagonal( 1000, 9999);
	getOctagonal( 1000, 9999);

	for( auto it = triangle.begin(); it != triangle.end(); it++)
	{
		for( int i = 0; i< it->second.size(); i++)
		{
			std::vector<int> v;
			v.push_back( 4);
			v.push_back(5);
			v.push_back(6);
		//	v.push_back(7);
			v.push_back(8);
			findCyclical( it->second[i], it->second[i], it->second[i], v);
		}
	}
	
	cout << "triangle=" << triangle.size() << " square=" << square.size() << " pentagonal=" << pentagonal.size() << " hexagonal=" << hexagonal.size() << " heptagonal=" << heptagonal.size() << " octagonal=" << octagonal.size() << endl;

	/* end of code */
	clock_t end = clock();
	cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << endl;
	return 0;
}
