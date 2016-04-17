/*
 	Problem 66 - Diophantine equation
*/
	
#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>
using namespace std;


std::vector<int> getx( int d, int miny, int maxy)
{
	std::vector<int> x;

	for(int i=miny; i<=maxy; i++)
	{
		double sqrted = sqrt( pow(i,2)* d + 1);
		if( sqrted == ceil(sqrted)) {

			cout << "D=" << d << " y=" << i << " x=" << sqrted << endl;
			x.push_back(sqrted);
		}
	}

	return x;
}

int main(int argc, char** argv)
{
	clock_t begin = clock();
	/* starting code */

	std::vector<int> x = getx( 2, 1, 100);
	cout << "x.size()=" << x.size() << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
