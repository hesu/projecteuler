/*
  Problem 38 - Pandigital multiples
*/

#include <iostream>
#include <ctime>

using namespace std;


bool isPandigital( char arr[])
{
	if (strlen(arr) != 10) { return false; }

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

void multiplesAttach( char buf[], int n)
{
	buf[0] = '0';
	char* c = &buf[1];
	for(int i=1;; i++)
	{
		int mul = n*i;
		c += sprintf( c, "%d", mul);
		int len = strlen( buf);
		if (len >= 10) { return; }
	}
}

int main(int argc, char** argv)
{
  clock_t begin = clock();
 
	/* starting code */

	// 10000 * 1 = 10000, 10000 * 2 = 20000 (1000020000 : 10개. Pandigital 자리수 초과!)
	for(int i=1; i<9999; i++)
	{
		char s[32] = {0,};
		multiplesAttach( s, i);
		if (isPandigital( s)) {
			cout << "pandigital at i=" << i << " s=" << s << endl;
		}
	}

  /* end of code */
  clock_t end = clock();
  std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
  return 0;
}
