/*
  Problem 96 - Su Doku
*/

#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

class Sudoku
{
  public:
  Sudoku(vector<string> s)
  {
    for(int i=0; i<s.size(); i++)
    {
      for(int j=0;j<s[i].size();j++)
      {
        orig[i][j] = s[i][j] - '0';
      }
    }
  };

  void print()
  {
    for(int i=0; i<9;i++)
    {
      for(int j=0;j<9;j++) cout << orig[i][j] << " ";
      cout << endl;
    }
  }

  bool solve( std::vector<pair<int,int>> filled, std::map<pair<int,int>, vector<int>> incorrect) 
  {
    int i, j;
    int minzero = findStartingPoint( orig, &i, &j);
    if( minzero == 0) { 
      cout << "sudoku solved!" << endl; 
      print(); 
      return true; 
    } 
    
    cout << "try solve i:" << i << " j:" << j << endl;

    vector<int> fill = determine( orig, i, j, incorrect);

    if (fill.size() > 0) {
      for(int vi=0; vi<fill.size(); vi++)
      {
        cout << "vi=" << vi << " fill.size()=" << fill.size() << endl;
        cout << "fill at [" << i << "] [" << j << "] : " << fill[vi] << endl;
        filled.push_back( make_pair(i,j));
        orig[i][j] = fill[vi];
        bool res = solve( filled, incorrect);
        if( res == true) return res;
        else{ cout << "Try Another" << endl; }
      }
      filled.pop_back();
      return false;
    } else {
      cout << "can't solve with previous filled" << endl;
      std::pair<int,int> last = filled[ filled.size()-1];

      // Add Error Map
      cout << "AddErrorMap" << endl;
      std::map<pair<int,int>, vector<int>>::iterator it = incorrect.find( last);

      if( it == incorrect.end()) {
        std::vector<int> mapv;
        mapv.push_back( orig[ last.first][last.second]);
        std::pair<int,int> key = make_pair( last.first, last.second);
      // incorrect.insert( map<pair<int,int>,vector<int>>::value_type( key, mapv));
      } else {
        it->second.push_back( orig[ last.first][last.second]);
      }
     
      cout << "Clear This incorrect path" << endl;
      orig[ last.first][last.second] = 0;
      filled.pop_back();
      return false;
    }
  }

  private:
    int orig[9][9];
    int solved[9][9];
    int memo[9][9];

    vector<int> determine( int arr[9][9], int i, int j, std::map<pair<int,int>, vector<int>> incorrect)
    {
      vector<int> vec;

      // value to 1 ~ 9
      for(int v=1; v<=9; v++)
      {
        // 0) is in incorrect map?
        std::map<pair<int,int>, vector<int>>::iterator it = incorrect.find( make_pair(i, j));
        if( it != incorrect.end()){
          cout << "v=" << v << endl;
          if( find( it->second.begin(), it->second.end(), v) != it->second.end()) continue;
        }

        // 1) 3by3 block has value?
        int k=i/3;
        int l=j/3;
        int ir=i%3;
        int jr=j%3;

        bool ok = true;
        for(int ii=0; ii<3; ii++)
        {
          if( ok) {
          for(int jj=0; jj<3; jj++)
          {
            if( ii == ir && jj == jr) continue;
            int checkat = arr[ k*3 + ii][ l*3 + jj];
            if (checkat == v) { ok = false; break; }
          }
          }
        }

        if( !ok) continue;

//cout << "vert" << endl;
        // 2) vertical has value?
        for(int vi=0; vi<9; vi++)
        {
          if(arr[vi][j] == v) { ok = false; break; }
        }

      if( !ok) continue;

//cout << "hori" << endl;
        // 3) horizontal has value?
        for(int hj=0; hj<9; hj++)
        {
          if(arr[i][hj] == v) { ok = false; break; }
        }

      if( !ok) continue;

        vec.push_back(v); 
      }
      return vec;
    }
  
    int findStartingPoint( int arr[9][9], int* i, int* j)
    {
      int minzero = 9;

      int allsolved = true;
      for(int wi=0; wi<9;wi++)
      {
        if( allsolved) {
          for(int wj=0; wj<9; wj++) { if( arr[wi][wj] == 0) {allsolved = false; break;}}
        }
      }
      if( allsolved) { cout << "allsolved;" << endl; return 0; }

      // find zero 3 by 3 block
      for(int k=0;k<3;k++)
      {
        for(int l=0;l<3;l++)
        {
          int nzero = 0;
          int mini,minj;
          for(int i=0;i<3;i++)
          {
            for(int j=0;j<3;j++) {
              if(arr[k*3 + i][l*3 + j] == 0) { nzero++; mini = k*3 + i; minj = l*3 + j;}
            }
          }

          if( nzero < minzero && nzero != 0) { minzero = nzero; *i = mini; *j = minj; }
        }
      }

      // find horizontal
      for(int hi=0; hi<9;hi++)
      {
        int nzero = 0;
        int mini, minj;
        for(int hj=0; hj<9; hj++)
        {
          if(arr[hi][hj] == 0) { nzero++; mini = hi; minj = hj;}
        }
        if( nzero < minzero && nzero != 0) { minzero = nzero; *i = mini; *j = minj; }
      }

      // find vertical
      for(int vj=0; vj<9;vj++)
      {
        int nzero = 0; 
        int mini, minj;
        for(int vi=0; vi<9; vi++)
        {
          if(arr[vi][vj] == 0) { nzero++; mini = vi; minj = vj;}
        }
        if( nzero < minzero && nzero != 0) { minzero = nzero; *i = mini; *j = minj; }
      }
      return minzero;
    }

};

int main(int argc, char** argv)
{
	clock_t begin = clock();
	
  /* starting code */

  ifstream inf( "p096_sudoku.small.txt");
  //ifstream inf( "p096_sudoku.txt");

  vector<string> sv;

  string line;
  int linecnt = 0;
  while( std::getline( inf, line)) {
    linecnt++;
    cout << "line=" << line << endl;

    if( linecnt % 10 == 1) {
      sv.clear();
      for(int i=0;i<9;i++)
      {
         std::getline(inf, line);
         sv.push_back( line);
         linecnt++;
      }

      vector<pair<int,int>> filled;
      map<pair<int,int>, vector<int>> incorrect;
      Sudoku sdk = Sudoku(sv);
      sdk.print();
      bool b = sdk.solve(filled, incorrect);
      cout << "solved? : " << b << endl;
    }
  }
  inf.close();

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
