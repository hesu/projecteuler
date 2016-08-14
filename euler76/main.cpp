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

void countingSummations( std::vector<int> &v, int i, int depth)
{
  for(int j=i; j>=0; j--) {
  
  if( v[j] > 1) {
    // c : how much collapse at this time
    int val = v[j];
    for(int c=1; c< val/2+1; c++) {
      
      std::vector<int> newv(v);

      //for(int d=0; d<depth; d++) cout << " ";
      //cout << "howmuchcollapsed? : " << c << endl;

      newv[j] -= c;
  
      // where to add? 
      if ((newv.size() > j+1) && (newv[j+1]+c <= newv[j]))  { 
      //  cout << "v.size=" << v.size() << " idx=" << i << endl;
        newv[j+1] += c;
      } else { 
       // cout << "pushback " << c << endl;
        newv.push_back(c); 
      }
 
      if (flatLowerMost) {
        // sum++ only flat case
        // http://stackoverflow.com/questions/20287095/checking-if-all-elements-of-a-vector-are-equal-in-c
        if ( std::adjacent_find( newv.begin(), newv.end(), std::not_equal_to<int>() ) == newv.end() ){
          if (newv[j] == 1) return;
          printv( newv);
          sum++;
        }
      } else {
        printv( newv);
        sum++;
      }
  
      countingSummations( newv, j+1 , depth++);
    }
  } else {
//    cout << "j=" << j << " v[j]=" << v[j] << " depth=" << depth << endl;
  }

  }
}

int main(int argc, char** argv)
{
	clock_t begin = clock();
	
  /* starting code */

  int number = 8;
  
  std::vector<int> v;
  v.push_back(number);
  countingSummations(v, 0, 0);
  cout << "sum of " << number << " : " << sum << endl;
	
  /* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
