/*
  Problem 68 - Magic 5-gon ring
*/

#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class GonRing
{
  public:
    GonRing( std::vector<int> t, std::vector<int> r)
    {
      tails.assign( t.begin(), t.end());
      std::sort( tails.begin(), tails.begin() + tails.size());

      rings.assign( r.begin(), r.end());
      std::sort( rings.begin(), rings.begin() + rings.size());
    }
    
    std::vector<std::vector<int>> solutionset()
    {
      do {
        std::vector<std::vector<int>> tsums;
        for(int i=0; i<tails.size(); i++)
        {
          std::vector<int> v;
          v.push_back( tails[i]);

          // push from rings!
          // v.push_back( from Rings)
          v.push_back( rings[i]);
          v.push_back( rings[(i+1)%rings.size()]);
          ///////////////////
          tsums.push_back( v);
        }

        int totalsum = std::accumulate( tsums[0].begin(), tsums[0].end(), 0);
        int made = true;
        for(int i=1; i<tsums.size(); i++)
        {
          if( std::accumulate( tsums[i].begin(), tsums[i].end(), 0) != totalsum) {
            made = false; break;
          }
        }

        if( made) {
          cout << "made & found! total sum=" << totalsum << endl;
          return tsums;
        }

      } while( std::next_permutation( rings.begin(), rings.begin()+rings.size()));

      std::vector<std::vector<int>> empty;
      return empty;
    }

  private:
    std::vector<int> tails;
    std::vector<int> rings;

};

void print_string( std::vector<std::vector<int>> set)
{
  cout << "set.size()=" << set.size() << endl;

  for(int i=0; i<set.size(); i++)
  {
     for(int j=0; j<set[i].size(); j++)
     {
        cout << set[i][j] << " ";
     }
     cout << endl;
  }

}

int main(int argc, char** argv)
{
  clock_t begin = clock();

  std::vector<int> n = { 1, 2, 3, 4, 5, 6 };
  std::vector<GonRing> gr;

  gr.push_back( GonRing( {1,2,3,4,5}, {6,7,8,9,10}));
  gr.push_back( GonRing( {6,7,8,9,10}, {1,2,3,4,5}));
  gr.push_back( GonRing( {1,3,5,7,9}, {2,4,6,8,10}));
  gr.push_back( GonRing( {2,4,6,8,10}, {1,3,5,7,9}));

  for(int i=0; i<gr.size(); i++)
  {
    cout << "gonring for [" << i << "]" << endl;
    std::vector<std::vector<int>> set = gr[i].solutionset();

    if( set.size() > 0) {
      cout << "MAXIMUM : " << endl;
      print_string( set);
    }
  }

  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
