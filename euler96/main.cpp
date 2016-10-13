/*
  Problem 96 - Su Doku
*/

#include <iostream>
#include <ctime>

using namespace std;

int main(int argc, char** argv)
{
  clock_t begin = clock();

  int sol = 0;
  cout << "solution=" << sol << endl;

  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
