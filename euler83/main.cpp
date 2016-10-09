/*
 	Problem 83 - Path sum: four ways
*/

#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>

using namespace std;

int minOf( vector<int> v)
{
  int min = v[0];
  for(int i=0;i<v.size();i++) {
    if( v[i] == -1) continue;
    if( v[i] < min) min = v[i];
  }
  return min;
}

int getMinPathValue( int nowrow, int nowcol, int row, int col, int **mat, int** memo, int matsize)
{
//  cout << "getMinPathValue() row=" << row << " col=" << col << " val=" << mat[row][col] << endl;
  
  // 종료조건
  if( nowrow == row && nowcol + 1 == col) {
    return mat[nowrow][nowcol] + mat[row][col];
  }
  
  if( nowrow == row && nowcol - 1 == col) {
    return mat[nowrow][nowcol] + mat[row][col];
  }

  if( nowrow + 1 == row && nowcol == col) {
    return mat[nowrow][nowcol] + mat[row][col];
  }
  
  if( nowrow - 1 == row && nowcol == col) {
    return mat[nowrow][nowcol] + mat[row][col];
  }


  // 점화식
  int north = -1, west = -1, east = -1, south = -1;
  // get north
  if( row > 0) {
    north = getMinPathValue( nowrow, nowcol, row-1, col, mat, memo, matsize);
  }

  // get south
  if( row < matsize-1) {
   south = getMinPathValue( nowrow, nowcol, row+1, col, mat, memo, matsize);
  }

  // get west
  if( col > 0) {
    west = getMinPathValue( nowrow, nowcol, row, col-1, mat, memo, matsize);
  }
  
  // get east 
  if( col < matsize-1) {
    east = getMinPathValue( nowrow, nowcol, row, col+1, mat, memo, matsize);
  }

  vector<int> v = { north, west, east, south };
  int min = minOf( v );
  return mat[row][col] + min;
}

int main(int argc, char** argv)
{
	clock_t begin = clock();

  int matsize = 5;
  //int row=80;
  //int col=80;
  int row=matsize, col=matsize;

  int **mat = (int**) malloc( sizeof( int*) * row);
  for(int i=0; i<row; i++)
  {
    int* row = (int*) malloc( sizeof( int) * col);
    mat[i] = row;
  }

  string fname = "p083_matrix.small.txt";
  //string fname = "p083_matrix.txt";
  ifstream inf(fname);
  string line;
 
  int irow = 0;
  while( std::getline( inf, line)) {
    cout << "line=" << line << endl;
    
    // Tokenize 
    string delim = ",";
    size_t lenDelim = delim.length();
    size_t pos = 0;

    int icol = 0;
    while(( pos = line.find( delim)) != std::string::npos) {
      string token = line.substr( 0, pos);
 //     cout << "token=" << token << " "; 
      line.erase( 0, pos + lenDelim);
      
      mat[irow][icol] = atoi( token.c_str());
      icol++;
    } 

//    cout << "last=" << line << endl;
    mat[irow][icol] = atoi( line.c_str());
    irow++;
  }
  inf.close();

  /*
  cout << "MATRIX DEBUG!" << endl;
  for(int y=0; y<row; y++)
  {
    for(int x=0; x<col; x++)
    {
      cout << mat[y][x] << " ";
    }
    cout << endl;
  }
  */

  int **memo = (int**) malloc( sizeof( int*) * row);
  for(int i=0; i<row; i++)
  {
    int* row = (int*) malloc( sizeof( int) * col);
    for(int j=0; j<col; j++) row[j] = 0;
    memo[i] = row;
  }

  int min = getMinPathValue( 0, 0, row-1, col-1, mat, memo, matsize);
  cout << "min=" << min << endl;

	clock_t end = clock();
	std::cout << "elapsed=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
