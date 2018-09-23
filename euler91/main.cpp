/*
 	Problem 91 - Right triangles with integer coordinates
*/
	
#include <iostream>
#include <ctime>
#include <map>
using namespace std;

typedef struct _coordinate
{
  int x;
  int y;
} coordinate;

map<int, pair<coordinate, coordinate>> g_shapes;

int getshapes(int n)
{
  if (n == 0)
    return 0;

  int shapes = 0;

  for(int i = 0; i <= n; i++)
  {
    /* TODO */
  }

  return shapes + getshapes(n-1);
}

int main(int argc, char** argv)
{
	clock_t begin = clock();

  /* starting code */
  int val = getshapes(50);
  cout << "val=" << val << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
