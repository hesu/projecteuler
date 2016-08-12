/*
 	Problem 76 - Counting summations
*/
	
#include <iostream>
#include <ctime>
#include <algorithm>
#include <vector>

using namespace std;

void printv( std::vector<int> v)
{
  for(int i=0; i<v.size(); i++) cout << v[i] << "-";
  cout << endl;
}

int sum = 0;
void countingSummations( std::vector<int> &v, int i)
{
  // 아이디어 : 'collapse' 한다고 생각해 보자.
  // 수들이 무너진다는 아이디어.

  // 현재 풀이에서는 몇 가지 경우를 놓친다.
  // 좋은 방법이 없을까? 
  // 1씩만 무너지는게 문제일 것 같은데.

  if( v[i] > 1) {
    // collapse
    int c = 1; // how much collapse at this time
    v[i] -= c;

    // where to add? 
    if ((v.size() > i+1) && (v[i+1]+c <= v[i]))  { 
      cout << "v.size=" << v.size() << " idx=" << i << endl;
      v[i+1] += c;
    } else { 
      cout << "pushback " << c << endl;
      v.push_back(c); 
    }

    printv( v);
    sum++;

    std::vector<int> newv(v);
    countingSummations( newv, i+1);

  } else {
    // move foward
    for(int j=i; j>=0; j--)
    {
      i--;
      if (v[i] > 1) break;
    }

    if( i < 0) return;
    std::vector<int> newv(v);
    countingSummations( newv, i);
  }
}

int main(int argc, char** argv)
{
	clock_t begin = clock();
	
  /* starting code */
  std::vector<int> v;
  v.push_back(6);
  
  countingSummations(v, 0);
  cout << "sum=" << sum << endl;
	
  /* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
