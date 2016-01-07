/*
  Problem 36 - Double-base palindromes 
*/

#include <iostream>
#include <ctime>
#include <stdio.h>
#include <string.h>

using namespace std;

bool is_palindromic( char arr[], int size)
{
	for(int i=0; i<(size/2)+1; i++)
	{
		if(arr[i] != arr[size-1-i]) {return false;}
	}
	return true;
}

void oct_to_bin( char o[], int osize, char b[])
{
	char *cp = b;

	for(int i=0; i<osize; i++)
	{
		if (o[i] == '0') { cp += sprintf( cp, "%s", "000"); }
		else if(o[i] == '1') { 
			if (i != 0) {
				cp += sprintf( cp, "%s", "001");
			} else {
				cp += sprintf( cp, "%s", "1");
			}
		}
		else if(o[i] == '2') { 
			if (i != 0) {
				cp += sprintf( cp, "%s", "010");
			} else {
				cp += sprintf( cp, "%s", "10");
			}
		}
		else if(o[i] == '3') { 
			if (i != 0) {
				cp += sprintf( cp, "%s", "011");
			} else {
				cp += sprintf( cp, "%s", "11");
			}
		}
		else if(o[i] == '4') { cp += sprintf( cp, "%s", "100");}
		else if(o[i] == '5') { cp += sprintf( cp, "%s", "101");}
		else if(o[i] == '6') { cp += sprintf( cp, "%s", "110");}
		else if(o[i] == '7') { cp += sprintf( cp, "%s", "111");}
	}
}

int main(int argc, char** argv)
{
  clock_t begin = clock();

  /* starting code */
	int sum = 0;
	for(int i=0; i<100 * 10000; i++)
	{
		char oct[1024] = {0,};
		sprintf( oct, "%o",i);

		char bin[1024] = {0,};
		oct_to_bin( oct, 1024, bin);
		
		char dec[1024] = {0,};
		sprintf( dec, "%d", i);

		if( is_palindromic( dec, strlen(dec)) && is_palindromic( bin, strlen(bin))) {
			cout << "i=" << i << " dec=" << dec << " bin=" << bin << " oct=" << oct << endl;
			sum += i;
		}
	}

	cout << "sum=" << sum << endl;
  /* end of code */
  clock_t end = clock();
  std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
  return 0;
}
