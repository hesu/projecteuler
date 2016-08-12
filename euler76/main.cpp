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
bool flatLowerMost = false;

void countingSummations( std::vector<int> &v, int i)
{
  // 아이디어 : 'collapse' 한다고 생각해 보자.
  // 수들이 무너진다는 아이디어.

  if( v[i] > 1) {
    // 1~c 까지 무너지게 하니까 케이스들이 중복된다.
    // 중복 케이스를 빼낼 방법?
    // 한번 1로 all collapsed 가 되면.. 그 이후부터는 같은높이의 계단 collapsed 만 체크하면 될거같다.
    // flatLowerMost 를 만들었으니 체크해보자.

    // c : how much collapse at this time
    for(int c=1; c<= v[i]/2; c++) {
      v[i] -= c;
  
      // where to add? 
      if ((v.size() > i+1) && (v[i+1]+c <= v[i]))  { 
      //  cout << "v.size=" << v.size() << " idx=" << i << endl;
        v[i+1] += c;
      } else { 
       // cout << "pushback " << c << endl;
        v.push_back(c); 
      }
 
      if (flatLowerMost) {
        // sum++ only flat case
        // http://stackoverflow.com/questions/20287095/checking-if-all-elements-of-a-vector-are-equal-in-c
        if ( std::adjacent_find( v.begin(), v.end(), std::not_equal_to<int>() ) == v.end() ){
          if (v[i] == 1) return;
          printv( v);
          sum++;
        }
      } else {
        printv( v);
        sum++;
      }
  
      std::vector<int> newv(v);
      countingSummations( newv, i+1);
    }

  } else {
    printv( v);
    //cout << "infinite loop? i=" << i << endl;
    // move foward

    while( v[i] <= 1) {
      i--;

      if( i < 0) { flatLowerMost = true; return; }
    }

    std::vector<int> newv(v);
    return countingSummations( newv, i);
  }
}

int main(int argc, char** argv)
{
	clock_t begin = clock();
	
  /* starting code */
  std::vector<int> v;
  v.push_back(8);
  
  countingSummations(v, 0);
  cout << "sum=" << sum << endl;
	
  /* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
