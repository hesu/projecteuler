/*
 	Problem 89 - Roman numerals
*/

#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;

int roman( char a)
{
  if (a == 'I') return 1;
  else if (a == 'V') return 5;
  else if (a == 'X') return 10;
  else if (a == 'L') return 50;
  else if (a == 'C') return 100;
  else if (a == 'D') return 500;
  else if (a == 'M') return 1000;
  else return 0;
}

string minimalRomans( int n)
{
  string s;
  int m = n/1000;
  for(int i=0; i<m;i++) { s.append( "M"); }

  n %= 1000;
  if( n >= 900) { n-= 900; s.append( "CM"); }
  else if( n >= 800) { n-= 800; s.append( "DCCC"); }
  else if( n >= 700) { n-= 700; s.append( "DCC"); }
  else if( n >= 600) { n-= 600; s.append( "DC"); }
  else if( n >= 500) { n-= 500; s.append( "D"); }
  else if( n >= 400) { n-= 400; s.append( "CD"); }
  else if( n >= 300) { n-= 300; s.append( "CCC"); }
  else if( n >= 200) { n-= 200; s.append( "CC"); }
  else if( n >= 100) { n-= 100; s.append( "C"); }
  
  if( n >= 90) { n-= 90; s.append( "XC"); }
  else if( n >= 80) { n-= 80; s.append( "LXXX"); }
  else if( n >= 70) { n-= 70; s.append( "LXX"); }
  else if( n >= 60) { n-= 60; s.append( "LX"); }
  else if( n >= 50) { n-= 50; s.append( "L"); }
  else if( n >= 40) { n-= 40; s.append( "XL"); }
  else if( n >= 30) { n-= 30; s.append( "XXX"); }
  else if( n >= 20) { n-= 20; s.append( "XX"); }
  else if( n >= 10) { n-= 10; s.append( "X"); }
  
  if( n >= 9) { n-= 9; s.append( "IX"); }
  else if( n >= 8) { n-= 8; s.append( "VIII"); }
  else if( n >= 7) { n-= 7; s.append( "VII"); }
  else if( n >= 6) { n-= 6; s.append( "VI"); }
  else if( n >= 5) { n-= 5; s.append( "V"); }
  else if( n >= 4) { n-= 4; s.append( "IV"); }
  else if( n >= 3) { n-= 3; s.append( "IIV"); }
  else if( n >= 2) { n-= 2; s.append( "II"); }
  else if( n >= 1) { n-= 1; s.append( "I"); }
  
  return s;
}

bool descending( char a, char b)
{
  return (roman(a) >= roman(b));
}

int numberFromRomans( string r)
{
  int n = 0;
  for(int i=0; i<r.size(); i++)
  {
    int j=i+1;
    if( i < r.size()-1) {
      while( j < r.size()-1 && r[i] == r[j]) {
        j++;
      }
      if( descending( r[i], r[j])) {
        n += roman( r[i]);
      } else {
        n -= roman( r[i]);
      }
    } else {
      n += roman( r[i]);
    }
  }
  return n;
}

int main(int argc, char** argv)
{
	clock_t begin = clock();
	
  /* starting code */

  /*
    string line = "XXXXVIIII";
    int n = numberFromRomans( line);
    cout << "================" << endl;
    cout << line << endl;
    string minimalRoman = minimalRomans( n);
    cout << minimalRoman << endl;
    */

  int cnt = 0;
  ifstream inf( "p089_roman.txt");

  string line;
  int linecnt = 0;
  while( std::getline( inf, line)) {
    linecnt++;
    int n = numberFromRomans( line);
    string minimalRoman = minimalRomans( n);
    if( line.size() > minimalRoman.size()) {
      cnt+= (line.size() - minimalRoman.size());
      cout << "n=" << n << " origin roman=" << line << " origin roman size()=" << line.size() << " minimal roman=" << minimalRoman << " minimal roman size()=" << minimalRoman.size() << endl;
    }
  }
  inf.close();
  cout << "cnt=" << cnt << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
