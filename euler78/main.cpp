/*
  Problem 78 - Coin partitions
*/

#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>

using namespace std;

void printVec( vector<int> v)
{
  for(int i=0; i<v.size(); i++) cout << v[i] << " ";
  cout << endl;
}

int coinPartitions( int initval, std::vector<int> n, map<vector<int>, bool>& m)
{
  if( n[0] <= 1) { return 0; }
  if( n.size() > initval) {
     return 0;
  }
  
  int ways = 0;

  if( n.size() > 1) {
    // all member 에 대해
    for(int i=1; i<n.size(); i++)
    {
      vector<int> newn(n);
      sort( newn.begin(), newn.end(), greater<int>());
      newn[0]--;
      if( newn[0] <= newn[i]) continue;

      newn[i]++;
      sort( newn.begin(), newn.end(), greater<int>());

      map<vector<int>, bool>::iterator it = m.find( newn);
      if( it == m.end()) {
        m.insert( map<vector<int>, bool>::value_type( newn, true));
      } //else continue;

      //printVec( newn);
      ways += coinPartitions( initval, newn, m);
    }
  }

  // 마지막으로 하나짜리를 빼고 푸쉬 한다면 
  vector<int> newn(n);
  newn[0]--; newn.push_back( 1);
  sort( newn.begin(), newn.end(), greater<int>());
  
  map<vector<int>, bool>::iterator it = m.find( newn);
  if( it == m.end()) m.insert( map<vector<int>, bool>::value_type( newn, true));
  ways += coinPartitions( initval, newn, m);

  return ways;
}

#define MAX 1000000

int main(int argc, char** argv)
{
  clock_t begin = clock();

  int sol = 1;

  while( true) {
    std::vector<int> n; n.push_back( sol);
    map<vector<int>, bool> m;
    coinPartitions( sol, n, m);
    if( m.size()+1 > MAX && m.size()+1 % MAX == 0) {
      break;
    }
    if( sol % 1 == 0) { cout << "try to solve. now=" << sol << " p(now)=" << m.size()+1 << endl; }
    sol++;
  }

  cout << "sol=" << sol << endl;

  //for(map<vector<int>,bool>::iterator it = m.begin(); it!= m.end(); it++) printVec( it->first);

  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
