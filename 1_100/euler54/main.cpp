/*
	 Problem 54 - Poker hands
 */
#include <iostream>
#include <ctime>

#include <vector>
#include <fstream>
#include <algorithm>
#include <map>

using namespace std;

typedef enum
{
	HIGH_CARD,
	ONE_PAIR,
	TWO_PAIRS,
	THREE_OF_A_KIND,
	STRAIGHT,
	FLUSH,
	FULL_HOUSE,
	FOUR_OF_A_KIND,
	STRAIGHT_FLUSH,
	ROYAL_FLUSH,
} PokerHands;

typedef struct _Made
{
	int hands;
	int highest;
} Made;

class Card
{
	private:
	char suit; // spade, clover, diamond, heart 
	int rank; // 2, 3, ... King(13), Ace(14)
	
	public:
	Card( string str)
	{
		//str ex : "5H", "KD"
		suit = str[1];

		if( str[0] == 'A') {
			rank = 14;
		} else if( str[0] == 'K') {
			rank = 13;
		} else if( str[0] == 'Q') {
			rank = 12;
		} else if( str[0] == 'J') {
			rank = 11;
		} else if( str[0] == 'T') {
			rank = 10;
		} else {
			rank = str[0] - '0';
		}
	}

	char getSuit(){ return suit;}
	int getRank(){ return rank;}
};

bool ascendingSort( Card a, Card b){ return (a.getRank() < b.getRank()); }

class Deck 
{
	private:
		std::vector<Card> c;

		std::map<int,int> getCountMap()
		{
			std::map<int,int> cnt;
			std::map<int,int>::iterator it;
			for(int i=0; i<c.size(); i++)
			{
				int r = c[i].getRank();
				it = cnt.find( r);
				if( it != cnt.end()) {
					(it->second)++;
				} else {
					cnt.insert( std::map<int,int>::value_type( r, 1));
				}
			}
			return cnt;
		}

		Made isStraight()
		{
			Made m; m.hands = -1;
			if( c.size() < 5) return m; 
			bool is = true;
			int next = c[0].getRank();
			for(int i=0; i<c.size(); i++)
			{
				if( c[i].getRank() != next) {	
					if( c[0].getRank() == 2 && i == 4 && c[i].getRank() == 14) { // 2 3 4 5 A
						m.highest = 5;
						return m;
					}
					return m;
				}
				next++;
			}
			m.hands = STRAIGHT;
			m.highest = next;
			return m; 
		}

		Made isFlush()
		{
			Made m; m.hands = -1;
			int highest = c[0].getRank();
			char s = c[0].getSuit();
			for(int i=0; i<c.size(); i++){ 
				if (c[i].getSuit() != s) { return m; } 
				int r = c[i].getRank();
				if( r > highest) { highest = r;}
			}
			m.hands = FLUSH;
			m.highest = highest;
			return m; 
		}

		Made isFourOfAKind()
		{
			Made m; m.hands = -1;
			std::map<int,int> cnt = getCountMap();
			std::map<int,int>::iterator it;

			for( it=cnt.begin(); it != cnt.end(); it++)
			{
				if( it->second == 4) {
					m.hands = FOUR_OF_A_KIND;
					m.highest = it->first; 
					return m;
				}
			}
			return m;  // not made
		}

		Made isThreeOfAKind()
		{
			Made m; m.hands = -1;
			std::map<int,int> cnt = getCountMap();
			std::map<int,int>::iterator it;

			for( it=cnt.begin(); it != cnt.end(); it++)
			{
				if( it->second == 3) {
					m.hands = THREE_OF_A_KIND;
					m.highest = it->first;
					return m;
				}
			}
			return m;  // not made
		}
		
		Made isFullHouse()
		{
			Made m; m.hands = -1;
			std::map<int,int> cnt = getCountMap();
			std::map<int,int>::iterator it;
			
			bool triple = false;
			bool onePair = false;
			for( it=cnt.begin(); it != cnt.end(); it++)
			{
				if( it->second == 3) {
					triple = true;
					m.highest = it->first;
				} else if( it->second == 2){ 
					onePair = true;
				}
			}

			if ( triple && onePair) { m.hands = FULL_HOUSE;}
			return m;
		}
		
		Made isTwoPairs()
		{
			Made m; m.hands = -1;
			std::map<int,int> cnt = getCountMap();
			std::map<int,int>::iterator it;

			int h = 0;
			bool onePair_1 = false;
			bool onePair_2 = false;
			for( it = cnt.begin(); it != cnt.end(); it++)
			{
				if( it->second == 2) {
					if (h < it->first) { h = it->first; }
					onePair_1 == false ? onePair_1 = true : onePair_2 = true;
				}
			}

			if( onePair_1 && onePair_2) { 
				m.highest = h;
				m.hands = TWO_PAIRS; 
			}
			return m;
		}
		
		Made isOnePair()
		{
			Made m; m.hands = -1;
			std::map<int,int> cnt = getCountMap();
			std::map<int,int>::iterator it;
		
			for( it = cnt.begin(); it != cnt.end(); it++)
			{
				if( it->second == 2) {
					m.highest = it->first;
					m.hands = ONE_PAIR;
					break;
				}
			}
			return m;
		}

	public:
		Deck() {}
		
		void add( Card card) { c.push_back( card); }
		int nCards() { return c.size(); }
		void sort() { 
			std::sort( c.begin(), c.end(), ascendingSort); 
		}

		Made whatMade()
		{
			Made m;
			m.hands = -1;

			// Straight? 
			m = isStraight();
			if (m.hands == STRAIGHT) {
				Made msf = isFlush();
				if (msf.hands == FLUSH) {
					if (msf.highest == 14) {
						msf.hands = ROYAL_FLUSH;
					} else {
						msf.hands = STRAIGHT_FLUSH;
					}
					return msf;
				}

				// NOTE : Four of a Kind > Straight
				Made mf = isFourOfAKind();
				if (mf.hands == FOUR_OF_A_KIND) { return mf; }
				return m;
			}

			// Four of a Kind?
			m = isFourOfAKind();
			if( m.hands == FOUR_OF_A_KIND) {
				return m;
			}

			// Triple?
			m = isThreeOfAKind();
			if( m.hands == THREE_OF_A_KIND) {
				// Full House?
				Made mfh = isFullHouse();
				if( mfh.hands == FULL_HOUSE) {
					return mfh;
				}
				return m;
			}

			// Two Pair?
			m = isTwoPairs();
			if( m.hands == TWO_PAIRS) { return m; }

			m = isOnePair();
			if( m.hands == ONE_PAIR) { return m; }

			// Default 
			m.hands = HIGH_CARD;
			m.highest = c[4].getRank();
			return m;
		}

		bool isWin( Deck& rhs) 
		{
			sort();
			rhs.sort();

			Made mine = whatMade();
			Made yours = rhs.whatMade();

			if( mine.hands == yours.hands) {
				return ( mine.highest > yours.highest);
			}
			return ( mine.hands > yours.hands);
		}
};

int main(int argc, char** argv)
{
	clock_t begin = clock();
	/* starting code */ 

	string line;
	ifstream f("p054_poker.txt");
	
	string delim = " ";
	size_t lenDelim = delim.length();
	size_t pos = 0;

	int wincnt = 0;
	while( getline( f, line))
	{
		Deck p1;
		Deck p2;

		while(( pos = line.find( delim)) != std::string::npos) {
			string token = line.substr( 0, pos);
			
			Card c( token);
			(p1.nCards() < 5) ? p1.add(c) : p2.add(c);
			
			line.erase( 0, pos + lenDelim);
		}
		Card c( line); // 10th card
		p2.add( c);

		// Figure out made deck 
		if( p1.isWin( p2)) {
			wincnt++;
		}
	}
	f.close();
	cout << "p1 wins : " << wincnt << " times" << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
