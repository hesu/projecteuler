/*
 	Problem 82 - Path sum: three ways
*/

#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>

using namespace std;


#define MATSIZE 5

int getPathSum( int **mat, int col, int yrow, int sum)
{
  if (col <= 0) { return sum ; }


  // 지금 col, yrow 에서
  // 이전 col 의 어느 값까지의 최소경로를 찾는다.
  int min = -1;

  for(int r=0; r<MATSIZE; r++)
  {
    int minval = -1;
    if( r == yrow) {
      minval = mat[col-1][r] + mat[col][yrow];
      cout << "found!" << endl;
    }

    if( min == -1) min = minval;
    else if( minval > min) min = minval;
  }
 
  return getPathSum( mat, col-1, yrow, sum);
}

int main(int argc, char** argv)
{
	clock_t begin = clock();

  int row=MATSIZE; // 80;
  int col=MATSIZE; // 80;

  int **mat = (int**) malloc( sizeof( int*) * row);
  for(int i=0; i<row; i++)
  {
    int* row = (int*) malloc( sizeof( int) * col);
    mat[i] = row;
  }

  string fname = "p082_matrix.small.txt";
  ifstream inf(fname);
  string line;
 
  int irow = 0;
  while( std::getline( inf, line)) {
    //cout << "line=" << line << endl;
    string delim = ",";
    size_t lenDelim = delim.length();
    size_t pos = 0;

    int icol = 0;
    while(( pos = line.find( delim)) != std::string::npos) {
      string token = line.substr( 0, pos);
      line.erase( 0, pos + lenDelim);
      
      mat[irow][icol] = atoi( token.c_str());
      icol++;
    } 

    mat[irow][icol] = atoi( line.c_str());
    irow++;
  }
  inf.close();

  cout << "MATRIX DEBUG!" << endl;
  for(int y=0; y<row; y++) { for(int x=0; x<col; x++) cout << mat[y][x] << " "; cout << endl; }

  std::vector<int> pathsums;

  int yrow = 0;
  int ps = getPathSum( mat, col, yrow, 0);
  cout << "ps=" << ps << endl;
/*
  for(int left=0; left<row; left++)
  {
    for(int right=0; right<row; right++)
    {

      int **memo = (int**) malloc( sizeof( int*) * row);
      for(int i=0; i<row; i++)
      {
        int* row = (int*) malloc( sizeof( int) * col);
        for(int j=0; j<col; j++) row[j] = 0;
        memo[i] = row;
      }

      // LOGIC TODO

      for(int i=0; i<row; i++) { free( memo[i]);}
      free(memo);
    }
  }
  */

	clock_t end = clock();
	std::cout << "elapsed=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
