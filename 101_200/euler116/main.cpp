/*
  Problem 116 - Red, green or blue tiles
*/

#include <iostream>
#include <ctime>
#include <map>
#include "../../misc/BigInt/BigInt.h"

using namespace std;

map<int, BigInt> nways_red;
map<int, BigInt> nways_green;
map<int, BigInt> nways_blue;

BigInt get_next_tiles_recursion(char color, BigInt prevways, int origlen, int maxlen)
{
  if (maxlen-origlen <= 0)
    return BigInt(0);

  if (color == 'r')
  {
    auto iter = nways_red.find(maxlen-origlen);
    if (iter != nways_red.end()) 
      return iter->second;

    if (maxlen - origlen == 1)
      return BigInt(1); // n
    else if(maxlen - origlen == 2)
      return BigInt(2); // nn, rr
    else
    {
      BigInt sum(0);
      sum = sum + get_next_tiles_recursion(color, prevways+BigInt(1), origlen+1, maxlen);
      sum = sum + get_next_tiles_recursion(color, prevways+BigInt(2), origlen+2, maxlen);

      nways_red[maxlen-origlen] = sum;
      return sum;
    }
  }
  else if (color == 'g')
  {
    auto iter = nways_green.find(maxlen-origlen);
    if (iter != nways_green.end()) 
      return iter->second;
    
    if (maxlen - origlen <= 2)
      return BigInt(1); // n, nn
    else if(maxlen - origlen == 3)
      return BigInt(2); // nnn, ggg
    else
    {
      BigInt sum(0);

      if (maxlen - (origlen+1) >= 3)
        sum = sum + get_next_tiles_recursion(color, prevways+BigInt(1), origlen+1, maxlen);
      
      sum = sum + get_next_tiles_recursion(color, prevways+BigInt(2), origlen+3, maxlen);
      nways_green[maxlen-origlen] = sum;
      return sum;
    }
  }
  else if (color == 'b')
  {
    auto iter = nways_blue.find(maxlen-origlen);
    if (iter != nways_blue.end()) 
      return iter->second;
    
    if (maxlen - origlen <= 3)
      return BigInt(1); // n, nn, nnn
    else if(maxlen - origlen == 4)
      return BigInt(2); // nnnn, bbbb
    else
    {
      BigInt sum(0);
      if (maxlen - (origlen+1) >= 4)
        sum = sum + get_next_tiles_recursion(color, prevways+BigInt(1), origlen+1, maxlen);
      
      sum = sum + get_next_tiles_recursion(color, prevways+BigInt(2), origlen+4, maxlen);
      nways_blue[maxlen-origlen] = sum;
      return sum;
    }
  }
  else
    return BigInt(0);
}

int main(int argc, char** argv)
{
  clock_t begin = clock();

  int length=50;

  BigInt all_grey(1);
  BigInt rsum(0);
  rsum = get_next_tiles_recursion('r', BigInt(0), 0, length) - all_grey;
  cout << "red sum=" << rsum.toString() << endl;
  
  BigInt gsum(0);
  gsum = get_next_tiles_recursion('g', BigInt(0), 0, length) - all_grey;
  cout << "green sum=" << gsum.toString() << endl;
  
  BigInt bsum(0);
  bsum = get_next_tiles_recursion('b', BigInt(0), 0, length) - all_grey;
  cout << "blue sum=" << bsum.toString() << endl;

  BigInt allsum = rsum + gsum + bsum;
  cout << "sol=" << allsum.toString() << endl;

  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
