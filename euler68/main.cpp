/*
  Problem 68 - Magic 5-gon ring
*/

#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;


class GonRing
{
  public:
    std::vector<int> tails;
    std::vector<int> rings;

    int solutionset()
    {
      int totalsum = 0;
      return 0;
    }
};

std::vector<GonRing> gonrings;

void combination( std::vector<int> n, int limit, int now, std::vector<int> result)
{
 // cout << "combi : now=" << now << endl;
//  if( now > limit) return;

  if( now >= 0) {
    result.push_back( n[now]);
  }

  //cout << "result.size()=" << result.size() << endl;

  if( result.size() >= limit) {
    // Made combination! do something.
    GonRing g;
    for(int i=0; i<n.size(); i++)
    {
      // if found n[i] in result, push tails
      if( std::find( result.begin(), result.end(), n[i]) != result.end()) {
        g.tails.push_back( n[i]);

      } else {
        g.rings.push_back( n[i]);
      // else push rings
      }
    }
    gonrings.push_back( g);

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

  cout << "sizeof gonrings=" << gonrings.size() << endl;

  for(int i=0; i<gonrings.size(); i++)
  {
    gonrings[i].solutionset(); 
  }

  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
