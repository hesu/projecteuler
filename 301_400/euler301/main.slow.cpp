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
bool is_lose(BigBinary& n1, BigBinary& n2, BigBinary& n3)
{
  BigBinary n1n2 = n1._xor(n2);

  if (n1n2.size() != n3.size())
    return false;

  for(int i=0; i < n1n2.size(); i++)
  {
    if (n1n2.get(i) != n3.get(i))
      return false;
  }
  //BigBinary n1n2n3 = n1n2._xor(n3);
 // cout  << "n1=" << n1.str() << " n2=" << n2.str() << " n1n2=" << n1n2.str() << " n3=" << n3.str() << " n1n2n3=" << n1n2n3.str() << endl;

  return true;
}

bool is_limit_over(BigBinary& n1)
{
  int logn = 30;
  if (n1.size() <= logn)
    return false;
  
  return true;
}

BigBinary add(BigBinary& n1, BigBinary& n2)
{
  BigBinary ret("");
  int max_size = max(n1.size(), n2.size());

  int carry = 0;
  for(int i=0; i < max_size; i++)
  {
    int sum_at = n1.get(i) + n2.get(i) + carry;
    int r = sum_at % 2;

    ret.push_back(r);
    if (sum_at >= 2)
      carry = 1;
    else
      carry = 0;
  }

  if (carry > 0)
  {
    ret.push_back(carry);
  }

  return ret;

}


int main(int argc, char** argv)
{
	clock_t begin = clock();

  /* starting code */

  /* 1,2,3 (lose)
  BigBinary n1("01");
  BigBinary n2("10");
  BigBinary n3("11");
  */
  
  /* 1,2,4 (win)
  BigBinary n1("01");
  BigBinary n2("10");
  BigBinary n3("100")
  */
  
  /* 3,5,6 (lose)
  BigBinary n1("11");
  BigBinary n2("101");
  BigBinary n3("110");
  */
  
  /* 4,9,20 (win)
  BigBinary n1("100");
  BigBinary n2("1001");
  BigBinary n3("10100");
  cout << "lose? : " << is_lose(n1, n2, n3) << endl;

  BigBinary addret = add(n1, n2);
  BigBinary addret2 = add(addret, n3);
  cout << "n1=" << n1.str() << " n2=" << n2.str() << " addret = " << addret.str() << endl;
  cout << "n3=" << n3.str() << " addret2 = " << addret2.str() << endl;
  */

  int logn = 0;
  unsigned int howmany = 0;
  BigBinary base("1");
  while(is_limit_over(base) == false)
  {
    BigBinary base_2n = add(base, base);
    BigBinary base_3n = add(base_2n, base);
  

    if (is_lose(base, base_2n, base_3n))
    {
//      cout << "base=" << base.str() << " base_2n=" << base_2n.str() << " base_3n= " << base_3n.str() << endl;
      howmany++;
    }
    else
    {
    }

    BigBinary inc("1");
    base = add(base, inc); 
    //cout << "new_base=" << base.str() << endl;

    int this_logn = base.str().size();
    if (logn != this_logn)
    {
      cout << "logn = " << this_logn << endl;
      logn = this_logn;
    }
  }

  howmany++; // n=2^30 인 경우
  cout << "howmany = " << howmany << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
