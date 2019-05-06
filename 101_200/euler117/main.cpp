/*
  Problem 117 - Red, green and blue tiles
*/

#include <iostream>
#include <ctime>
#include <map>
#include "../../misc/BigInt/BigInt.h"

using namespace std;

map<int, BigInt> nways;

BigInt get_next_tiles_recursion(BigInt prevways, int origlen, int maxlen)
{
  auto iter = nways.find(maxlen-origlen);
  if (iter != nways.end())
    return prevways + iter->second;

  if (maxlen-origlen <= 0)
    return BigInt(0);
  else if (maxlen - origlen == 1)
    return BigInt(1); // 'n'
  else if (maxlen - origlen == 2)
    return BigInt(2); // 'nn', 'rr'
  else if (maxlen - origlen == 3)
    return BigInt(4); // 'nnn', 'rrn', 'nrr', 'ggg'
  else if (maxlen - origlen == 4)
    return BigInt(8);// 'nnnn', 'nnrr', 'rrnn', 'rrrr', 'nrrn', 'nggg', 'gggn', 'bbbb'
  else
  {
    BigInt sum(0);
    sum = sum + get_next_tiles_recursion(prevways, origlen+1, maxlen);
    sum = sum + get_next_tiles_recursion(prevways, origlen+2, maxlen);
    sum = sum + get_next_tiles_recursion(prevways, origlen+3, maxlen);
    sum = sum + get_next_tiles_recursion(prevways, origlen+4, maxlen);
    nways[maxlen-origlen] = sum;
    return prevways + sum;
  }
}

int main(int argc, char** argv)
{
  clock_t begin = clock();

  int length=50;

  BigInt sum(0);
  sum = get_next_tiles_recursion(BigInt(0), 0, length);
  cout << "sum=" << sum.toString() << endl;
  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
