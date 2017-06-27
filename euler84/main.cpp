/*
  Problem 84 - Monopoly Odds
*/

#include <iostream>
#include <ctime>
#include <map>
#include <vector>

#include "BigInt.h"

using namespace std;

class Dice
{
  public :
    map<int, Fraction> roll();
};

// 주사위는 최대 3번까지 던질 수 있다.
// 여기서는 rand 를 쓰는 게 아니라.. 어떤 경우의 수를 펼쳐놓은 것(map 같은?) 을 보고 싶은데..
// 3번까지 던졌을 때 각 2~35(=12+12+11) 점 까지 도착할 모든 확률표.
map<int, Fraction> Dice::roll()
{
  map<int, Fraction> result;
  return result;
}

int main(int argc, char** argv)
{
  clock_t begin = clock();

  string map[40] = { "GO", "A1", "CC1", "A2", "T1",  "R1", "B1", "CH1", "B2", "B3", "JAIL", 
  "C1", "U1", "C2", "C3", "R2", "D1", "CC2", "D2", "D3", "FP",
  "E1", "CH2", "E2", "E3", "R3", "F1", "F2", "U2", "F3", "G2J",
  "G1", "G2", "CC3", "G3", "R4", "CH3", "H1", "T2", "H2"};

  // 1부터 40까지의 각 점에서 주사위를 던졌을 때 각 점에 도착할 확률을 계산한다.
  // 40개를 계산하여 더하면 모든 케이스.
  // 모든 케이스에서 각 점에 도착할 확률을 구해낸다.
  // 6면체로 계산해서 예제의 답과 같은지 먼저 비교해 본다.
  // TODO


  // 주사위가 (일단은) 6면체인데 면체가 바뀔 것도 고려해야 하고.
  // 더블의 규칙도 있음.

  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
