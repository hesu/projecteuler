/*
 	Problem 31 - Coin sums 
*/

#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

class CoinSums
{
private :
	int _200;
	int _100;
	int _50;
	int _20;
	int _10;
	int _5;
	int _2;
	int _1;

public :
	CoinSums( int i200, int i100, int i50, int i20, int i10, int i5, int i2, int i1)
	{
		_200 = i200;
		_100 = i100;
		_50 = i50;
		_20 = i20;
		_10 = i10;
		_5 = i5;
		_2 = i2;
		_1 = i1;
	}

	std::vector<CoinSums> split()
	{
		std::vector<CoinSums> v;
		// 각 요소(200, 100, 50, 20, 10, 5, 2) 에 대해
		// 그 하위 요소로 쪼갤 수 있으면 쪼개서 리턴한다.
		if (_200 > 0){
			CoinSums c( _200-1, _100+2, _50, _20, _10, _5, _2, _1);
			v.push_back( c);
			CoinSums c2( _200-1, _100, _50+4, _20, _10, _5, _2, _1);
			v.push_back( c2);
			CoinSums c3( _200-1, _100, _50, _20+10, _10, _5, _2, _1);
			v.push_back( c3);
			CoinSums c4( _200-1, _100, _50, _20, _10+20, _5, _2, _1);
			v.push_back( c4);
			CoinSums c5( _200-1, _100, _50, _20, _10, _5+40, _2, _1);
			v.push_back( c5);
			CoinSums c6( _200-1, _100, _50, _20, _10, _5, _2+100, _1);
			v.push_back( c6);
			CoinSums c7( _200-1, _100, _50, _20, _10, _5, _2, _1+200);
			v.push_back( c6);
		}

		if (_100 > 0) {
			CoinSums c( _200, _100-1, _50+2, _20, _10, _5, _2, _1);
			v.push_back( c);
			CoinSums c2( _200, _100-1, _50, _20+5, _10, _5, _2, _1);
			v.push_back( c2);
			CoinSums c3( _200, _100-1, _50, _20, _10+10, _5, _2, _1);
			v.push_back( c3);
			CoinSums c4( _200, _100-1, _50, _20, _10, _5+20, _2, _1);
			v.push_back( c4);
			CoinSums c5( _200, _100-1, _50, _20, _10, _5, _2+50, _1);
			v.push_back( c5);
			CoinSums c6( _200, _100-1, _50, _20, _10, _5, _2, _1+100);
			v.push_back( c6);
		}
		
		if (_50 > 0) {
			CoinSums c( _200, _100, _50-1, _20+2, _10+1, _5, _2, _1);
			v.push_back( c);
			CoinSums c2( _200, _100, _50-1, _20, _10+5, _5, _2, _1);
			v.push_back( c2);
			CoinSums c3( _200, _100, _50-1, _20, _10, _5+10, _2, _1);
			v.push_back( c3);
			CoinSums c4( _200, _100, _50-1, _20, _10, _5, _2+25, _1);
			v.push_back( c4);
			CoinSums c5( _200, _100, _50-1, _20, _10, _5, _2, _1+50);
			v.push_back( c5);
		}
		
		if (_20 > 0) {
			CoinSums c( _200, _100, _50, _20-1, _10+2, _5, _2, _1);
			v.push_back( c);
			CoinSums c2( _200, _100, _50, _20-1, _10, _5+4, _2, _1);
			v.push_back( c2);
			CoinSums c3( _200, _100, _50, _20-1, _10, _5, _2+10, _1);
			v.push_back( c3);
			CoinSums c4( _200, _100, _50, _20-1, _10, _5, _2, _1+20);
			v.push_back( c4);
		}
		
		if (_10 > 0) {
			CoinSums c( _200, _100, _50, _20, _10-1, _5+2, _2, _1);
			v.push_back( c);
			CoinSums c2( _200, _100, _50, _20, _10-1, _5, _2+5, _1);
			v.push_back( c2);
			CoinSums c3( _200, _100, _50, _20, _10-1, _5, _2, _1+10);
			v.push_back( c3);
		}
		
		if (_5 > 0) {
			CoinSums c( _200, _100, _50, _20, _10, _5-1, _2+2, _1+1);
			v.push_back( c);
			CoinSums c2( _200, _100, _50, _20, _10, _5-1, _2, _1+5);
			v.push_back( c2);
		}
		
		if (_2 > 0) {
			CoinSums c( _200, _100, _50, _20, _10, _5, _2-1, _1+2);
			v.push_back( c);
		}

		return v;
	}
	
	void print()
	{
		cout << "200*" << _200 << " + " << "100*" << _100 << " + " << "50*" << _50 << " + " << "20*" << _20 << " + " << "10*" << _10 << " + " << "5*" << _5 << " + " << "2*" << _2 << " + " << "1*" << _1 << endl;
	}

	bool operator == ( CoinSums& rhs)
	{
		if((rhs._200 == _200) &&
		   (rhs._100 == _100) &&
		   (rhs._50 == _50) &&
		   (rhs._20 == _20) &&
		   (rhs._10 == _10) &&
		   (rhs._5 == _5) &&
		   (rhs._2 == _2) &&
		   (rhs._1 == _1)) {
			return true;
		}
		return false;
	}
};

int main(int argc, char** argv)
{
	clock_t begin = clock();

	/* starting code */
	std::vector<CoinSums> allcase;
	CoinSums big( 1, 0, 0, 0, 0, 0, 0, 0);
	allcase.push_back( big);

	bool keepgoing = true;
	int si=0; // search index
	while( keepgoing)
	{
		std::vector<CoinSums> push;
		for( int i=si; i<allcase.size(); i++)
		{
			std::vector<CoinSums> s = allcase[i].split();
			push.insert( push.end(), s.begin(), s.end());
		}
		si = allcase.size();
		std::unique(push.begin(), push.end());

		for(int j=0; j<push.size(); j++)
		{
			bool found = false;
			for(int i=0; i<allcase.size(); i++)
			{
				if (allcase[i] == push[j]) {
					found = true;
					break;
				}
			}
			if (found == false) {
				allcase.push_back( push[j]);
			}
		}

		std::unique(allcase.begin(), allcase.end());

		bool all_cannot_splitted = true;
		for( int i=0; i<push.size(); i++)
		{
			std::vector<CoinSums> t = push[i].split();
			if( t.size() != 0) { 
				all_cannot_splitted = false;
				break;
			}
		}
		if (all_cannot_splitted == true) {
			keepgoing = false;
		}
	}

	cout << "LAST : sizeof allcase=" << allcase.size() << endl;
	for(int i=0; i<allcase.size(); i++) { allcase[i].print();}
	/* end of code */
	
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}

