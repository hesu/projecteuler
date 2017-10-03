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
  if (now == 7) return 15; // CH1 -> R2
  if (now == 22) return 25; // CH2 -> R3
  if (now == 36) return 5; // CH3 -> R1

  cout << "error case! now=" << now << endl;
  return -1;
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

  int now = 0;
  for(int i=0; i<10000000; i++)
  {
    int nroll = 0;

    while(true)
    {
      //Dice d1(6);
      //Dice d2(6);
      Dice d1(4);
      Dice d2(4);

      int val1 = d1.roll();
      int val2 = d2.roll();

      // 1. 말을 옮긴다.
      now += val1 + val2;
      if (now >= 40) now -= 40;

      // 2. 더블 체크
      // 3번 연속 더블시 칸의 체크 없이 바로 감옥행, 종료
      if ((val1 == val2) && (nroll >= 2)) {
        addPoint(tiles, _JAIL);
        now = _JAIL;
        break;
      }

      // 3. 칸의 특수효과 체크
      /// JAIL 칸이면 바로 종료
      if (now == _JAIL) {
        addPoint(tiles, now);
        break;
      }

      /// G2J 이면 JAIL+1 하고 종료.
      if (now == 30) // 30 : G2J
      {
        addPoint(tiles, now);
        addPoint(tiles, _JAIL);
        now = _JAIL;
        break;
      }

      /// 공동 기금 카드 계산
      if (now == 2 || now == 17 || now == 33)
      {
        int ret = communityChestCard(now);
        if (ret >= 0)
        {
          now = ret;
          addPoint(tiles, ret);
          if (ret == _JAIL) {
            break;
          }
        } else {
          addPoint(tiles, now);
        }
      }
      else if (now == 7 || now == 22 || now == 36)
      {
        addPoint(tiles, now);
        /// 찬스카드 계산
        int ret = chanceCard(now);
        if (ret >= 0)
        {
          //찬스카드에서 나온 칸이 커뮤니티 카드칸이라 또 뽑는다
          if (ret == 33)
          {
            now = ret;
            addPoint(tiles, now);
            
            int ret2 = communityChestCard(33);
            if (ret2 >= 0)
            {
              now = ret2;
              addPoint(tiles, now);
              if (ret2 == _JAIL) break;
            } 
          } 
          else {
            now = ret;
            addPoint(tiles, now);
            if (ret == _JAIL) break;
          }
        }
      }
      else 
      {
        /// 그 외의 경우 평범하게 포인트를 더하고 종료한다.
        addPoint(tiles, now);
      }

      // 4. reroll 여부 계산
      if (val1 != val2) break;

      nroll++;
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
  //cout << "example case expect : 102400" << endl;

  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
