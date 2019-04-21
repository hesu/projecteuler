/*
  Problem 87 - Prime power triples
*/

#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

#define MAX 50000000

std::vector<unsigned long int> squares;
std::vector<unsigned long int> cubes;
std::vector<unsigned long int> fourths;

bool isprime( unsigned long int n)
{
  if( n == 1) return false;
  if( n == 2) return true;

  unsigned long int s = sqrt( n) + 1;
  for(unsigned long int i=s; i>1; i--)
  {
    if (n%i ==0) {
      return false;
    }
  }
  return true;
}

int main(int argc, char** argv)
{
  clock_t begin = clock();

  for(unsigned long int i=1;i<MAX;i++)
  {
    if( !isprime(i)) continue;

    unsigned long int sq = pow( i, 2);
    if( sq > MAX) break;
    squares.push_back( sq);

    unsigned long int cu = pow(i, 3);
    if( cu < MAX) cubes.push_back( cu);

    unsigned long int fo = pow(i, 4);
    if( fo < MAX) fourths.push_back( fo);
  }

  cout << "fourths.size()=" << fourths.size() << endl;
  cout << "cubes.size()=" << cubes.size() << endl;
  cout << "squares.size()=" << squares.size() << endl;

  // Do mainLogic

  std::map<unsigned long int, bool> solutions;

  for(int i=fourths.size()-1; i>=0; i--)
  {
    unsigned long int sum = MAX - 1;
    if( sum >= fourths[i]) {
      unsigned long int sum2 = sum - fourths[i];
      for(int j=cubes.size()-1; j>=0;j--)
      {
        if( sum2 >= cubes[j]) {
          unsigned long int sum3 = sum2 - cubes[j];
          for( int k=squares.size()-1; k>=0; k--)
          {
            if( sum3 >= squares[k]) {

              unsigned long int triple = fourths[i] + cubes[j] + squares[k];
              cout << triple << " " << fourths[i] << " " << cubes[j] << " " << squares[k] << endl;
              std::map<unsigned long int, bool>::iterator it = solutions.find( triple);

              if( it == solutions.end()) {
                solutions.insert( std::map<unsigned long int, bool>::value_type( triple, true));
              }

            }
          }
        }

      }
    }
  }

  cout << "how many?=" << solutions.size() << endl;

  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
