/*
 	Problem 76 - Counting Summations
*/

#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;


unsigned int memo[100][100] = {0};

unsigned int coinsum( std::vector<int> coins, int val)
{
  // c(n, s(m)) = c(n, s(m-1)) + c(n-m, s(m));
  if( coins.size() == 0) return 0;
  if( val < 0 ) return 0;
  if( val == 0) return 1;

  unsigned int a;

  int idxa = coins[ coins.size() - 2];
  if( memo[ idxa][ val] != 0) {
    a = memo[ idxa][ val];
  } else {
    std::vector<int> c(coins);
    c.pop_back();
    a = coinsum( c, val);
  }

  unsigned int b;

  int idxb = coins[ coins.size()-1];
  if( memo[ idxb][ val - idxb] != 0) {
    b = memo[ idxb][ val - idxb]; 
  } else {
    b = coinsum( coins, val - idxb);
  }
  
  unsigned int ret = a + b;
  if( memo[ idxb][ val] == 0) { 
    cout << "coins.size()-1=" << idxb << " val=" << val << " for ret=" << ret << endl;
    memo[ idxb][ val] = ret; 
  }

  return ret;
}

int main(int argc, char** argv)
{
	clock_t begin = clock();

	/* starting code */
	std::vector<int> coins;

  for(int i=1; i<=99; i++) coins.push_back(i);

  int howmuch = 100;
  unsigned int sum = coinsum( coins, howmuch);

  cout << "val=" << howmuch << endl;
  cout << "coin sum=" << sum << endl;
	/* end of code */
	
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
