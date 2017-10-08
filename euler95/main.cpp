/*
  Problem 95 - Amicable chains
*/

#include <iostream>
#include <ctime>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

#define MAXNUM 1000000

map<int, int> nextNumberMemo;

int getUpperLimit(int n)
{
  return (sqrt(n) + 1);
}

vector<int> getDivisors(int n)
{
  vector<int> v;
  for(int i=1; i<=getUpperLimit(n); i++)
  {
    if(n%i == 0)
    {
      v.push_back(i);
    }
  }
  return v;
}

int nextNumber(int n)
{
  auto memo = nextNumberMemo.find(n);
  if (memo != nextNumberMemo.end())
  {
    return memo->second;
  }

  map<int, bool> m;

  for(int i=1; i<=getUpperLimit(n); i++)
  {
    if(n%i == 0)
    {
      int q = n/i;

      if (i < n) {m.insert(pair<int,bool>(i, true)); }
      if (q < n) {m.insert(pair<int,bool>(q, true)); }
    }
  }

  int next = 0;
  for(auto iter = m.begin(); iter != m.end(); iter++)
  {
    next += iter->first;
  }

  nextNumberMemo.insert(pair<int,int>(n, next));
  return next;
}

int main(int argc, char** argv)
{
  clock_t begin = clock();

  // 1) 수 n의 약수들의 합을 구하는(next number 를 구해내는) 알고리즘을 짠다.
  //  - 계산된 약수는 memoization 해야 겠다.
  // 2) chaining 코드를 짠다.
  // 3) 백만까지 계산한다.

  vector<int> bestLongChain;

  for(int i=1; i<=MAXNUM; i++)
  //for(int i=12496; i<=12496; i++)
  {
//    cout << "\t" << i << endl;
    int n = i;
    vector<int> chain;
    bool needChaining = true;

    chain.push_back(n);
    while(needChaining)
    {
      int nextN = nextNumber(n);
      if(nextN > MAXNUM) break;
      if(nextN <= 1) break;

      if (find(chain.begin(), chain.end(), nextN) != chain.end())
      {
        needChaining = false;
        chain.push_back(nextN);
        break;
      }
      else
      {
        chain.push_back(nextN);
        n = nextN;
      }
    }


    if(!needChaining)
    {
      vector<int> subChain;
      //vector<int> subChain(chain.begin() + cutIndex, chain.end());
      int cutIndex;
      for(int j=0; j<chain.size(); j++)
      {
        if(chain[j] == chain[chain.size()-1]) cutIndex = j;
        if(j >= cutIndex)
        {
          subChain.push_back(chain[j]);
        }
      }

      if(subChain.size() > bestLongChain.size() && subChain[0] == subChain[subChain.size()-1])
      {
        cout << "cutIndex=" << cutIndex << " chain.size()=" << chain.size() << endl;
        bestLongChain = subChain;
        for(int i=0; i<subChain.size()-1; i++) { cout << subChain[i] << "-"; }
        cout << "[" << subChain[subChain.size()-1] << "]" << endl;
        cout << endl;
      }

    }
  }

  int min = bestLongChain[0];
  for(int i=0; i<bestLongChain.size(); i++)
  {
    if(bestLongChain[i] < min)
    {
      min = bestLongChain[i];
    }
  }

  cout << "chain minimal number : " << min << endl;

  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
