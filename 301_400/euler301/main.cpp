/*
 	Problem 341 - Nim
*/
	
#include <iostream>
#include <sstream>
#include <ctime>
#include <vector>
#include <list>
#include <fstream>
#include <string.h>
#include "../../misc/BigInt/BigInt.h"

using namespace std;

class BigBinary
{
  private:
    vector<int> dg; // 내부적으로는 역순으로 관리함 - 2는 01, 4는 001

  public:

    BigBinary(const char* x)
    {
      int len = strlen(x);

      for(int i=len-1; i >=0 ; i--)
      {
        int digit = x[i] - '0';
//        cout << digit << endl;
        dg.push_back(digit);
      }
    }

    int push_back(int n)
    {
      dg.push_back(n);
    }

    int get(int n)
    {
      if (dg.size() <= n)
        return 0;

      return dg[n];
    }

    int size() { return dg.size(); }

    BigBinary _xor(BigBinary& other)
    {
      BigBinary ret("");

      int max_size = max(size(), other.size());

      for(int i=0; i < max_size; i++)
      {
        int n_this = get(i);
        int n_other = other.get(i);

        if (n_this == n_other)
          ret.push_back(0);
        else
          ret.push_back(1);
      }

      return ret;
    }

    bool is_zero()
    {
      if (dg.size() == 0) return true;

      for(int i=0; i < dg.size(); i++)
        if (dg[i] != 0) return false;
      
      return true;
    }

    string str()
    {
      stringstream ss;
      for(int i=dg.size()-1; i>=0; i--)
      {
        ss << dg[i];
      }

      return ss.str();
    }
};

// Nim 의 필승 전략은 내 턴을 종료했을 때 각 돌무더기의 수를 XOR 연산한 결과가 0이 되도록 돌을 덜어내는 것이다.
// 내 턴에서 돌을 덜기 전 XOR 연산 결과가 이미 0 이라면 바로 진 상태이다.
bool is_lose(unsigned int n1, unsigned int n2, unsigned int n3)
{
  return ((n1 ^ n2 ^ n3) == 0);
}

int main(int argc, char** argv)
{
	clock_t begin = clock();

  /* starting code */

  int exponent = 30;
  int lose = 0;

  unsigned int limit = 1 << exponent; // 2^30

  for(unsigned int i=limit; i>0; i--)
  {
    if (is_lose(i, 2*i, 3*i))
      lose++;
  }

  cout << "lose=" << lose << endl;


	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
