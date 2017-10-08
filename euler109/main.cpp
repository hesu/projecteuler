/*
  Problem 109 - Darts
*/

#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

class SingleScore
{
  public :
  SingleScore(int _n, int _mul)
  {
    n = _n;
    mul = _mul;
  }

  int n;
  int mul;
};

class Checkout
{
  // 나중에 out 이 같고, others 의 구성비가 같으면 같은 Checkout
  public :
  SingleScore out;
  vector<SingleScore> others; 
};

int nCheckout(int nowScore)
{
  //nCheckout 재귀 호출 형태가 될듯 
  int n = 0;
  if(nowScore >= 25)
  {
  }

  for(int i=20; i>=1; i--)
  {
  }

  return n;
}

int main(int argc, char** argv)
{
  clock_t begin = clock();

  // 1~20 : single, double, triple
  // 25 : single, double
  //
  // 마지막 아웃에 따라 구분됨. 
  // * (1더블-2더블아웃 != 2더블-1더블아웃)
  // * (1싱글-1트리플-1더블아웃 == 1트리플-1싱블-1더블아웃)
  // 
  // 0 점은 고려하지 않음

  int c = nCheckout(6);
  cout << "checkout for 6=" << c << endl;

  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
