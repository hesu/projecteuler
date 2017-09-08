/*
  Problem 84 - Monopoly Odds
*/

#include <iostream>
#include <ctime>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

#include "BigInt.h"

#define _JAIL 10

using namespace std;

class Dice
{
  public :
    Dice(int _space)
    {
      space = _space; 
    };

    int roll()
    {
      return (rand() % space) + 1;
    }

  private :
    int space;
};
  
vector<string> names = {
  "GO", "A1", "CC1", "A2", "T1",  "R1", "B1", "CH1", "B2", "B3", "JAIL", 
  "C1", "U1", "C2", "C3", "R2", "D1", "CC2", "D2", "D3", "FP",
  "E1", "CH2", "E2", "E3", "R3", "F1", "F2", "U2", "F3", "G2J",
  "G1", "G2", "CC3", "G3", "R4", "CH3", "H1", "T2", "H2"
};

struct sortSet {
  bool operator() (const pair<int,int> &left, const pair<int, int> &right)
  {
    return left.second < right.second;
  }
};

void addPoint( map<int,int>& m, int idx)
{
  auto it = m.find(idx);
  if( it != m.end())
    (it->second)++;
}
        
int communityChestCard(int now)
{
  // 1/16 : 출발지, 1/16 : 감옥.

  int prob = (rand() % 16) + 1;
  switch (prob)
  {
    case 1 :
      return 0;
    case 2 :
      return _JAIL;
  }
  return -1;
}

int getNextR(int now)
{
  if (now <= 4 || now >= 36) { return 5; }
  if (now >= 5 || now <= 14) { return 15; }
  if (now >= 15 || now <= 24) { return 25; }
  if (now >= 15 || now <= 24) { return 25; }
  if (now >= 25 || now <= 34) { return 35; }
}

int getNextU(int now)
{
  if (now <= 11 || now >= 29) { return 12; }
  return 28;
}

int get3StepBack(int now)
{
  if (now <= 2) { return 40 - 3 + now; }
  return (now - 3);
}

int chanceCard(int now)
{
  // 1/16 : 출발지
  // 1/16 : 감옥
  // 1/16 : C1
  // 1/16 : E3
  // 1/16 : H2
  // 1/16 : R1
  // 2/16 : Next R
  // 1/16 : Next U
  // 1/16 : now-3

  int prob = (rand() % 16) + 1;
  switch (prob)
  {
    case 1:
      return 0;
    case 2:
      return _JAIL;
    case 3:
      return 11; // C1
    case 4:
      return 24; // E3
    case 5:
      return 39; // H2
    case 6:
      return 5; // R1
    case 7:
      return getNextR(now);
    case 8:
      return getNextR(now);
    case 9:
      return getNextU(now);
    case 10:
      return get3StepBack(now);
  }
  return -1;
}

int main(int argc, char** argv)
{
  clock_t begin = clock();
  
  map<int, int> tiles;
  for(int i=0; i<names.size(); i++)
  {
    tiles.insert(map<int, int>::value_type(i, 0));
  }

  // 1부터 40까지의 각 점에서 주사위를 던졌을 때 각 점에 도착할 확률을 계산한다.
  // 6면체로 계산해서 예제의 답과 같은지 먼저 비교해 본다.
  for( auto it = tiles.begin(); it != tiles.end(); it++)
  {
    for(int i=0; i<1000000; i++)
    {
    int nroll = 0;

    int now = (it->first);

    while(true)
    {
      Dice d1(6);
      Dice d2(6);

      int val1 = d1.roll();
      int val2 = d2.roll();

      // 1. 말을 옮긴다.
      now += val1 + val2;
      if (now >= 40) now -= 40;

      // 2. 3번 연속 더블시 칸의 체크 없이 바로 감옥행, 종료
      if ((val1 == val2) && (nroll >= 2)) {
        addPoint(tiles, _JAIL);
        break;
      }

      // 3. 칸의 특수효과 체크
      /// JAIL 칸이면 바로 종료
      if (now == _JAIL) {
        addPoint(tiles, now);
        break;
      }

      /// G2J 이면 G2J+1, JAIL+1 하고 종료.
      if (now == 30) // 30 : G2J
      {
        addPoint(tiles, now);
        addPoint(tiles, _JAIL);
        break;
      }

      /// 공동 기금 카드 계산
      if (now == 2 || now == 17 || now == 33)
      {
        addPoint(tiles, now);
        
        int ret = communityChestCard(now);
        if (ret >= 0)
        {
          addPoint(tiles, ret);
          if (ret == _JAIL) break;
        }
      }

      /// 찬스카드 계산
      if (now == 7 || now == 22 || now == 26)
      {
        addPoint(tiles, now);
        int ret = chanceCard(now);
        if (ret >= 0)
        {
          addPoint(tiles, ret);
          if (ret == _JAIL) break;
        }
      }

      /// 그 외의 경우 평범하게 포인트를 더하고 종료한다.
      addPoint(tiles, now);

      // 4. reroll 여부 계산
      if (val1 != val2)
      {
        break;
      }
      nroll++;
    }
    }
  }

  vector<pair<int,int>> rank;

  for(auto it = tiles.begin(); it != tiles.end(); it++)
  {
    //cout << "it->first=" << it->first << " it->second=" << it->second << endl;
    rank.push_back(make_pair(it->second, it->first));
  }

  cout << "rank.size()=" << rank.size() << endl;
//  sort(rank.begin(), rank.end(), sortSet());
  sort(rank.begin(), rank.end(), [](const pair<int, int>&left, const pair<int,int>&right) {
    return (left.first > right.first);
  });

  for(int i=0; i<rank.size(); i++)
  {
    cout << "visited=" << rank[i].first << "\tkey=" << rank[i].second << endl;
  }

  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
