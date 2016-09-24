/*
 	Problem 82 - Path sum: three ways
*/

#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>

using namespace std;

#define MATSIZE 80 
//#define MATSIZE 5

// call : int ps = getPathSum( mat, 0, 4, mat[0][4]);
int getPathSum( int **mat, int row, int col, int sum)
{
//  cout << "mat[" << row << "][" << col << "]=" << mat[row][col] << endl;
  if (col <= 0) { return sum ; }

  // 지금 col, row 에서
  // 이전 col 의 어느 값까지의 최소경로를 찾는다.
  int min = -1;
  int nextrow;

  for(int r=0; r<MATSIZE; r++)
  {
 //   cout << "** check to reach mat[" << r << "][" << col-1 << "]" << "=" << mat[r][col-1] << endl;
    int minval = -1;
    if( r == row) {
      int val = mat[row][col-1] + mat[row][col];
      minval = val;
  //   cout << "r=row. r=" << r << " minval=" << minval << endl;
    } else {
//      cout << "else;" << endl;
      // get foward column path
      int fval = 0;
      if( r > row) {
        for(int i=row+1; i<=r; i++)
        {
          fval += mat[i][col];
        }
      } else {
        for(int i=row-1; i>=r; i--)
        {
          fval += mat[i][col];
        }
      }
      fval += mat[row][col];
      fval += mat[r][col-1];

      // get backward column path
      int bval = 0;
      if( r-1 != 0) {
      if( r > row) {
        for(int i=r-1; i>=row; i--)
        {
          bval += mat[i][col-1];
        }
      } else {
        for(int i=r+1; i<=row; i++)
        {
          bval += mat[i][col-1];
        }
      }
      bval += mat[row][col];
      bval += mat[r][col-1];
      }

      //cout << "  at row " << r << ": fval=" << fval << " bval=" << bval << endl;
      if( minval == -1) { minval = fval; }
      if( minval > fval) { 
        //cout << "minval will be change. minval=" << minval << " fval=" << fval << endl;
        minval = fval; 
      }
      else if( minval > bval) { 
        //cout << "minval will be change. minval=" << minval << " bval=" << bval << endl;
        if( r-1 != 0) {
        minval = bval; 
        }
      }
    }

    if( min == -1 || min > minval) { min = minval; nextrow = r; }

  }
//  cout << "RESULT min=" << min << " nextrow=" << nextrow << endl;
  
  return getPathSum( mat, nextrow, col-1, sum + min - mat[row][col]);
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

  //string fname = "p082_matrix.small.txt";
  string fname = "p082_matrix.txt";
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

//  cout << "MATRIX DEBUG!" << endl;
 // for(int y=0; y<row; y++) { for(int x=0; x<col; x++) cout << mat[y][x] << " "; cout << endl; }

  std::vector<int> pathsums;

  for(int i=0; i<MATSIZE; i++)
  {
    // call : int ps = getPathSum( mat, 0, 4, mat[0][4]);
    int ps = getPathSum( mat, i, MATSIZE-1, mat[i][MATSIZE-1]);
    pathsums.push_back( ps);
  }

  cout << "pathsums.size()=" << pathsums.size() << endl;
  int minsum = pathsums[0];
  for(int i=0; i<pathsums.size(); i++)
  {
    if( pathsums[i] < minsum) minsum = pathsums[i];
  }

  cout << "minsum=" << minsum << endl;

	clock_t end = clock();
	std::cout << "elapsed=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
