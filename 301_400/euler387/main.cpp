/*
 	Problem 387 - Harshad Numbers
*/
	
#include <iostream>
#include <ctime>
#include <map>
#include <cmath>
#include <string.h>

using namespace std;

map<long int,bool> prime;
map<long int,bool> notprime;

bool isprime(long int n)
{
  if (n == 1) return false;
  auto iter = prime.find(n);
  if (iter != prime.end()) return true;

  iter = notprime.find(n);
  if (iter != notprime.end()) return false;

  if(n == 2) {
    prime[n] = true;
    return true;
  }

  int s = sqrt( n) + 1;
  for(int i=s; i>1; i--)
  {
    if (n%i ==0) 
    { 
      notprime[n] = true;
      return false; 
    }
  }

  prime[n] = true;
  return true;
}

map<long int, bool> srth;
void next_strong_right_truncatable_harshad(long int srth_n, int maxdigit)
{
  char buf[128] = {0,};
  sprintf(buf, "%ld", srth_n);
  int len = strlen(buf);
  
  // scope?
  if (len >= maxdigit) return;
 
  // harshad?
  int digitsum=0;
  for(int i=0; i <len; i++)
  {
    digitsum += buf[i] - 48;
  }
  
  if (srth_n % digitsum != 0)
    return;
 
  // divided results in a prime?
  if (isprime(srth_n / digitsum))
  {
 //   cout << "srth found =" << srth_n << endl;
    srth[srth_n] = true;
  }

  for(int i=0; i<=9; i++)
  {
    buf[len] = i + 48;
    //cout << "srth_n=" << srth_n << ", buf=" << buf << endl;
    long int next = stol(buf);
    //cout << "next=" << next << endl;
    next_strong_right_truncatable_harshad(next, maxdigit);
  }
}

int main(int argc, char** argv)
{
	clock_t begin = clock();

  int pow = 14;
  /* starting code */
  for(int i=1; i<=9;i++)
    next_strong_right_truncatable_harshad(i, pow);

  long int sum = 0;
  for(auto iter = srth.begin(); iter != srth.end(); iter++)
  {
    for(int i=1; i<=9; i++)
    {
      char buf[128] = {0,};
      sprintf(buf, "%ld", iter->first);
      int len = strlen(buf);
      buf[len] = i + 48;

      long int srthp = stol(buf);
      if (isprime(srthp))
      {
//        cout << "srthp: " << srthp<< endl;
        sum += srthp;
      }
    }
  }

  cout << "sum=" << sum << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
