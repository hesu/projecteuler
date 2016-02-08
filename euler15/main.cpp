/*
 * Problem 15 : Lattice paths
 */

#include <iostream>

using namespace std;

unsigned long long int latticepath( unsigned long long int p[][21], int y, int x)
{
	unsigned long long int val = p[y][x];

	cout << "x:" << x << " y:" << y << " val:" << p[y][x] << endl;
	if( val == 0) {
		unsigned long long int retval = latticepath( p, y, x+1) + latticepath( p, y+1, x);
		p[y][x] = retval;

		if (retval < 0) {
			cout << "overflow at y:" << y << " x:" << x << endl;
		}
		return retval;
	} else {
		return val;
	}
}

int main()
{
	unsigned long long int path[21][21] = {0,};
	for(int i=0; i<21; i++)
	{
		path[20][i] = 1;
		path[i][20] = 1;
	}

	unsigned long long int npath = latticepath( path, 0, 0);

	// print
	for(int y=0; y<21; y++)
	{
		for(int x=0; x<21; x++)
		{
			cout << path[y][x] << " ";
		}
		cout << endl;
	}

	cout << "npath=" << npath << endl;

	return 0;
}
