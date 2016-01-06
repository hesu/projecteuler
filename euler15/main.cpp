/*
 	Problem 15
	Lattice paths
*/

#include <iostream>
#include <cmath>
#include <cstring>
#include <stdio.h>
#include <string.h>

using namespace std;

void getpath( int* map[20])
{

}

int main(int argc, char** argv)
{
	int paths[20][20] = {0,};

	for(int y=0; y<20; y++)
	{
		for(int x=0; x<20; x++)
		{
			if (y == 19)  paths[y][x] = 1;
			else if ( x == 19 ) paths[y][x] = 1;
			else paths[y][x] = 0;
		}
	}



	return 0;
}

