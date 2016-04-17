/*
 	Problem 66 - Diophantine equation
*/
	
#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>
using namespace std;

int getMinX( int d)
{
	for(int i=1;;i++)
	{
		double sqrted = sqrt( pow(i,2)* d + 1);
		if( sqrted == ceil(sqrted)) {
			cout << "D=" << d << " y=" << i << " x=" << sqrted << endl;
			return sqrted;
		}
	}
}

int main(int argc, char** argv)
{
	clock_t begin = clock();
	/* starting code */

	int MAXD = 1000;

	std::vector<int> xvec;
	for(int d=2; d<=MAXD; d++)
	{
		double sqrted = sqrt( d);
		if( sqrted == ceil( sqrted)) { continue; }
		xvec.push_back(getMinX( d));
	}

	int indexD = 0;
	int xmax = xvec[0];
	for(int i=0; i<xvec.size(); i++)
	{
		if( xvec[i] > xmax) {
			indexD = i;
			xmax = xvec[i]; 
		}
	}

	cout << "xmax=" << xmax<< " indexD = " << indexD << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
