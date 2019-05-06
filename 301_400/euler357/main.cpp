/*
 	Problem 351 - Prime generating integers

  Consider the divisors of 30: 1,2,3,5,6,10,15,30.
  It can be seen that for every divisor d of 30, d+30/d is prime.
  Find the sum of all positive integers n not exceeding 100 000 000
  such that for every divisor d of n, d+n/d is prime.
*/
	
#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

map<int,bool> prime;
map<int,bool> notprime;

bool isprime( int n)
{
  if (n == 0) return false;
  if (n == 1) return true;
  
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

bool getdiv( int n)
{
  int s = sqrt(n);
  
  vector<int> divs;
  for(int i=1; i<=s && i<=n; i++)
  {
    //cout << "n=" << n << ", i=" << i << endl;
    if (n%i == 0)
    {
      divs.push_back(i);
      if (i != n/i)
        divs.push_back(n/i);
    }
  }

  for(int i=0; i<divs.size(); i++)
  {
    int val = divs[i] + n/divs[i];
    if (isprime(val) == false)
      return false;
  }

  return true;
}

int main(int argc, char** argv)
{
	clock_t begin = clock();

  /* starting code */
  unsigned int sum = 0;

  int MAX = 100 * 1000 * 1000;
  //int MAX = 30;
  map<int, map<int, bool>> divides;
  for(int i = 1; i <= MAX; i++)
  {
    if (i%100000 == 0)
      cout << "i=" << i << endl;

    bool is = getdiv(i);
    if (is)
    {
//      cout << "matched i : " << i << endl;
      sum += i;
    }
  }

  cout << "sum=" << sum << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
