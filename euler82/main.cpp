/*
  Problem 82 - Path sum: three ways
*/

#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>

using namespace std;

#define MATSIZE 80

#define INTMAX 1073731824

int getMin(int a, int b, int c)
{
  int m;

  if( a < b) { m = a; }
  else m = b;

  if( m > c) { m = c; }
  return m;
}

// call : int ps = getPathSum( mat, 0, 4, mat[0][4]);
int getPathSum( int **mat, int ** refmat, int row, int col)
{
//  cout << "mat[" << row << "][" << col << "]=" << mat[row][col] << endl;
  // 지금 col, row 에서
  // 이전 col 의 어느 값까지의 최소경로를 찾는다.
  int min = -1;
  int nextrow;

  for(int r=0; r<MATSIZE; r++)
  {
//    cout << "** check to reach mat[" << r << "][" << col-1 << "]" << "=" << mat[r][col-1] << endl;
    int minval = INTMAX;
      
    // get foward column path
    int fval = 0;
      if( r > row) {
        for(int i=row+1; i<=r; i++)
        {
          fval += refmat[i][col];
        }
      } else {
        for(int i=row-1; i>=r; i--)
        {
          fval += refmat[i][col];
        }
      }
      fval += refmat[row][col];
      fval += mat[r][col+1];

      // get backward column path
      int bval = 0;
      if( r > row) {
        for(int i=r-1; i>=row; i--)
        {
          bval += refmat[i][col+1];
        }
      } else {
        for(int i=r+1; i<=row; i++)
        {
          bval += refmat[i][col+1];
        }
      }
     bval += refmat[row][col];
     bval += mat[r][col+1];

      int rval = 0;
      if( r == row) {
        rval = mat[r][col+1] + refmat[row][col];
      }

      if( rval == 0) rval = INTMAX;      
      if( bval == 0) bval = INTMAX;      
      if( fval == 0) fval = INTMAX;      

      minval = getMin( rval, bval, fval);

    if( min == -1 || min > minval) { 
      min = minval; nextrow = r; 
      }

    }


  //cout << "RESULT min=" << min << " nextrow=" << nextrow << endl;
  //cout << " next : row=" << nextrow << " col=" << col-1 << endl;
  //cout << "\t return min=" << min << endl;
  return min; 
  //return getPathSum( mat, nextrow, col-1, sum + min - mat[row][col]);
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

  //std::vector<int> pathsums;

  //int ps = getPathSum( mat, 0, 4, mat[0][4]);
  //int ps = getPathSum( mat, 0, 4, mat[0][0]);
  //cout << "ps=" << ps << endl;

  int **minmat = (int**) malloc( sizeof( int*) * row);
  for(int i=0; i<row; i++)
  {
    int* row = (int*) malloc( sizeof( int) * col);
    minmat[i] = row;

    for(int c=0; c<col; c++)
    {
      minmat[i][c] = 0;
    }
  }

  for(int j=0; j<row; j++)
  {
    minmat[j][col-1] = mat[j][col-1];
  }

  for(int i=col-2; i>=0; i--)
  {
    for(int j=row-1; j>=0; j--)
    {
      //int getPathSum( int **mat, int row, int col, int sum)
      minmat[j][i] = getPathSum( minmat,mat,j,i);
   //   cout << " minmat[" << j<< "][" << i<<"]=" << minmat[j][i] << endl;
    }
  }
 
// cout << endl;
 // cout << "MATRIX DEBUG!" << endl;
  //for(int y=0; y<row; y++) { for(int x=0; x<col; x++) cout << mat[y][x] << " "; cout << endl; }


  //cout << "MIN MATRIX DEBUG!" << endl;
  //for(int y=0; y<row; y++) { for(int x=0; x<col; x++) cout << minmat[y][x] << " "; cout << endl; }


  int sol = INTMAX;
  for(int i=0; i<row-1; i++)
  {
    if( sol > minmat[i][0]) { sol = minmat[i][0]; }
  }

  cout << "sol=" << sol << endl;

  clock_t end = clock();
  std::cout << "elapsed=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
