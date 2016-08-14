/*
 	Problem 76 - Counting Summations
*/

#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

int coinsum( std::vector<int> coins, int val)
{
  // c(n, s(m)) = c(n, s(m-1)) + c(n-m, s(m));
  if( coins.size() == 0) return 0;
  if( val < 0 ) return 0;
  if( val == 0) return 1;
  
  std::vector<int> c(coins);
  c.pop_back();
  return coinsum( c, val) + coinsum( coins, val - coins[ coins.size()-1]);
}

int main(int argc, char** argv)
{
	clock_t begin = clock();

	/* starting code */
	std::vector<int> coins;

  for(int i=1; i<=100; i++)
  {
    coins.push_back(i);
  }

  int howmuch = 100;
  int sum = coinsum( coins, howmuch);

  cout << "val=" << howmuch << endl;
  cout << "coin sum=" << sum << endl;
	/* end of code */
	
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
