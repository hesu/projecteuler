/*
 	Problem 76 - Counting summations
*/
	
#include <iostream>
#include <ctime>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

std::map<int, int> memo;


int sum = 0;
void countingSummations( std::vector<int> v, int i)
{
  // 아이디어 : 'collapse' 한다고 생각해 보자.
  // 수들이 무너진다는 아이디어.

  if( v[i] > 1) {
    // collapse
    v[i] = v[i]--;
    if (v.size() >= i) { v[i+1]++; }
    else { v.push_back(1); }

    sum++;
    countingSummations( v, i+1);

  } else {
    // move foward
    for(int j=i; j>=0; j--)
    {
      i--;
      if (v[i] > 1) break;
    }

    if( i < 0) return;
    countingSummations( v, i);
  }
}

int main(int argc, char** argv)
{
	clock_t begin = clock();
	
  /* starting code */
  std::vector<int> v;
  v.push_back(2);
  
  countingSummations(v, 0);
  cout << "sum=" << sum << endl;
	
  /* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
