/*
 	Problem 86 - Cuboid route
*/

#include <iostream>
#include <ctime>
#include <cmath>
#include <tuple>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

map<int,int> memo;

typedef tuple<int,int,int> triangle_key;

bool is_square_number(long double x)
{
  long double sr = sqrt(x);
  return ((sr - floor(sr)) == 0);
}

// route(x^ + (y+z)^) == integer?
bool is_cuboid_route(int x, int y, int z)
{
  return is_square_number(x*x + (y+z)*(y+z));
}


int get_cuboid_route_of(int max)
{
  if(max <= 1) return 0;

  auto iter = memo.find(max);
  if (iter != memo.end())
    return iter->second;

  map<triangle_key, bool> checked;

  int route_on_max = 0;
  for(int x=1; x <= max; x++)
  {
    for(int y=x; y <= max; y++)
    {
      vector<int> v = {x,y,max};
      sort(v.begin(), v.end());
      triangle_key t;
      t = make_tuple(v[0], v[1], v[2]);

      if(checked.find(t) == checked.end())
      {
        checked[t] = true;
      
        if (is_cuboid_route(max, x, y))
        {
//          cout << "cuboid "<< max << ": (" << max << "," << x << "," << y << ")" << endl;
          route_on_max++;
        }
      }
    }
  }

  int ret = route_on_max + get_cuboid_route_of(max-1);
  memo[max] = ret;
  return ret;
}

int main(int argc, char** argv)
{
	clock_t begin = clock();
	/* starting code */
  //bool b = is_cuboid_route(6, 3, 5);
  //cout << "is_square_number=" << b << endl;

/*
  int MAX = 100;
  int routes = get_cuboid_route_of(MAX);
  cout << MAX << " of cuboid.size=" << routes << endl;
  */

  for(int i=1;; i++)
  {
    int routes = get_cuboid_route_of(i);
    memo[i] = routes;

   // if (i % 1000 == 0)
    {
      cout << i << " of cuboid.size()=" << routes << endl;
    }

    if (routes >= 100 * 10000)
    {
      cout << "solution : " << i << " of cuboid.size()=" << routes << endl;
      break;
    }
  }

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}

