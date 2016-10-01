/*
  Combination Example
*/

#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

int cnt=0;
void combination( std::vector<int> n, int limit, int now, std::vector<int> result)
{
  if( now >= 0) {
    result.push_back( n[now]);
  }

  if( result.size() >= limit) {
    // Made combination! do something.
    for( std::vector<int>::iterator it = result.begin(); it != result.end(); ++it)
    {
      cout << "[" << *it << "]"; 
      if( it != result.end() -1) { cout << "-"; }
    }
    cout << endl;
    cnt++;
    // end of do something
    return;
  }

  for(int i=now+1; i<n.size();i++)
  {
    combination( n, limit, i, result);
  }
}

int main(int argc, char** argv)
{
  clock_t begin = clock();

  // 1) n 개의 수에서 1/2 n 을 선택하는 로직.
  
  std::vector<int> n = { 1, 2, 3, 4, 5, 6 };

  std::vector<int> c;
  for(int i=0; i< n.size()/2 + 1; i++)
  {
    combination( n, n.size()/2, i, c);
  }

  cout << "6C3 combinations cnt=" << cnt << endl;

  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
