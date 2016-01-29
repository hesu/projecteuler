/*
  Problem 39 - Integer right triangles 
*/

#include <iostream>
#include <ctime>
#include <cmath>
#include <map>

using namespace std;

int main(int argc, char** argv)
{
  clock_t begin = clock();
 
	/* starting code */
	std::map<int,int> triangles;
	std::map<int,int>::iterator it;

	for(int a=1; a<=500; a++)
	{
		for( int b=1; b<=500;b++)
		{
			double d = sqrt( a*a+ b*b);
			int c = int(d);
			if( (d == c)) {
				int p = a+b+c;
				if( p <= 1000) {
					it = triangles.find( p);
					if( it != triangles.end()) {
						(it->second)++;
					} else {
						triangles.insert( std::map<int,int>::value_type( p, 1));	
					}
				}
			}
		}
	}

	int max = 0;
	int where = 0;
	for( it = triangles.begin(); it != triangles.end(); ++it)
	{
		if (max < it->second) {
			max = it->second;
			where = it->first;
		}
	}

	cout << "max = " << max << " at " << where << endl;

  /* end of code */

  clock_t end = clock();
  std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
  return 0;
}
