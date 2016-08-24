/*
 	Problem 85 - Counting rectangles
*/

#include <iostream>
#include <ctime>

using namespace std;

int countRectangles( int ex, int ey)
{
  int sum = 0;
  for(int x=1; x<=ex; x++)
  {
    for(int y=1; y<=ey; y++)
    {
      sum += (ex - x + 1) * (ey - y + 1); 
    }
  }
  return sum;
}

int abs( int n) { return( n>0 ? n : (-1)*n); }


int main(int argc, char** argv)
{
	clock_t begin = clock();
	/* starting code */

  int GOAL = 2000000;

  int thatx=1;
  int thaty=1;
  int mindiff = GOAL;

  for(int x=1; x<= 1000; x++)
  {
    if( x%100 == 0) { cout << "now x=" << x << endl; }
    for(int y=1; y<=1000; y++)
    {
      int rects = countRectangles( x, y);
      int d = abs( GOAL - rects);

      if( d < mindiff) {
        mindiff = d;
        thatx = x;
        thaty = y;
      }
    }
  }

  cout << "x=" << thatx << " y=" << thaty << " mindiff=" << mindiff << endl;
  cout << "x*y=" << thatx*thaty << endl;
	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}

