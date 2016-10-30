/*
  Problem 84 - Monopoly Odds
*/

#include <iostream>
#include <ctime>
#include <map>

using namespace std;

class Dices
{

};

int main(int argc, char** argv)
{
  clock_t begin = clock();

  string map[40] = { "GO", "A1", "CC1", "A2", "T1",  "R1", "B1", "CH1", "B2", "B3", "JAIL", 
  "C1", "U1", "C2", "C3", "R2", "D1", "CC2", "D2", "D3", "FP",
  "E1", "CH2", "E2", "E3", "R3", "F1", "F2", "U2", "F3", "G2J",
  "G1", "G2", "CC3", "G3", "R4", "CH3", "H1", "T2", "H2"};

  // 확률을 어떻게 구해야 할지 잘 감이 안오는데,
  // 일단 모든 40개의 점에서 따져본 이동확률의 합 - 이 전체 표본이 될 거 같음.
  // 즉 한 점의 확률이 100 이고, 이게 40개 모이니까 전체 표본 크기는 4000. 이중에 각각의 점의 비율을 구하는 것.


  // 주사위가 (일단은) 6면체인데 면체가 바뀔 것도 고려해야 하고.
  // 더블의 규칙도 있음.

  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
