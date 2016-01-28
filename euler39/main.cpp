/*
  Problem 39 - Integer right triangles 
*/

#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

bool isRightAngle( int a, int b, int c)
{
	return (a*a + b*b == c*c);
}

void printArr( int a[]) 
{
	for(int i=0; i<3;i++)
	{
		cout << "[" << a[i] << "] ";
	}
	cout <<endl;
}

int getRightAngleTriangles( int a[], int len)
{
	int nRightAngle = 0;
	for(int i=1; i<len; i++)
	{
		for(int j=1; j<len-i; j++)
		{
			std::vector<int> abc;
			abc.push_back( i);
			abc.push_back( j);
			abc.push_back( len-i-j);
			std::sort( abc.begin(), abc.end());

			if (isRightAngle( abc[0], abc[1], abc[2])) {
				nRightAngle++;	
			}
		}
	}
	return nRightAngle;
}

int main(int argc, char** argv)
{
  clock_t begin = clock();
 
	/* starting code */
	int arr[3] = {0,};

	int maxtriangles = 0;
	int maxlen = 0;
	for(int i=3; i<=1000; i++)
	{
		cout << "i=" << i << endl;
		int triangles = getRightAngleTriangles( arr, i); 
		if (triangles > maxtriangles) {
			maxtriangles = triangles;
			maxlen = i;
		}
	}

	cout << "maxtriangles = " << maxtriangles << " at " << maxlen << endl;
  /* end of code */

  clock_t end = clock();
  std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
  return 0;
}
