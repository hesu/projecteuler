/*
  Problem 39 - Integer right triangles 
*/

#include <iostream>
#include <ctime>

using namespace std;

bool isRightAngle( int a, int b, int c)
{
	return (a*a + b*b == c*c);
}

int getRightAngleTriangles( int a[], int len)
{
	int nRightAngle = 0;
	for(int i=len-2; i>=len/3; i--)
	{
		for(int j=1; j<=(len-i)/2; j++)
		{
			if (isRightAngle( j, len-i-j, i)) {
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
