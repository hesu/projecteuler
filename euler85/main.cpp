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

int main(int argc, char** argv)
{
	clock_t begin = clock();
	/* starting code */

  int GOAL = 2000000;
  int diff = GOAL;

  int thatx = 1;
  int thaty = 1;

  bool done = false;
  for(int x=1; !done; x++)
  {
    for(int y=1; !done; y++)
    {
      int rects = countRectangles( x, y);

      int thisDiff = GOAL - rects;
      if( thisDiff < 0) { // over
        done = true;
        break;
      }

    }
  }


	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}

