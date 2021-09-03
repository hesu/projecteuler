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
