/*
  Problem 38 - Pandigital multiples
*/

#include <iostream>
#include <ctime>

using namespace std;


bool isPandigital( char arr[])
{
	bool swit[10] = {false,};
	for(int i=0; i<10; i++)
	{
		int idx = arr[i] - '0';
		if (swit[idx] == true) { return false; }
		else { swit[idx] = true; }
	}

	for(int i=0; i<10; i++)
	{
		if( swit[i] == false) {return false; }
	}
	return true;
}

int main(int argc, char** argv)
{
  clock_t begin = clock();
 
	/* starting code */

  /* end of code */
  clock_t end = clock();
  std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
  return 0;
}
