/*
 	Problem 81 - Path sum: two ways
*/

// Related Problems?
// 1) Lattice paths(prob 15)
// 2) Maximum path sum 1(prob 18) 
// 3) Maximum path sum 2(prob 67)

#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;
  
int getMinPathValue( int row, int col, int **mat, int** memo)
{
//  cout << "getMinPathValue() row=" << row << " col=" << col << " val=" << mat[row][col] << endl;
  if( row == 0 && col == 0) { return mat[row][col]; }

  int upper, left;

  if (row-1 < 0) { upper = -1; }
  else if (memo[row-1][col] != 0) { upper = memo[ row-1][col]; }
  else {
    upper = getMinPathValue( row-1, col, mat, memo);
    memo[row-1][col] = upper;
  }
  
  if (col-1 < 0) { left = -1; }
  else if (memo[row][col-1] != 0) { upper = memo[ row][col-1]; }
  else {
    left = getMinPathValue( row, col-1, mat, memo);
    memo[row][col-1] = left;
  }
//  cout << "upper=" << upper << " left=" << left << endl;

  int min = -1;
  if( upper == -1) { min = left; }
  else if( left == -1) { min = upper; }
  else {
    upper < left ? min = upper : min = left;
  }
//  cout << "min=" << min << endl;
  
  return mat[row][col] + min;
}

int main(int argc, char** argv)
{
	clock_t begin = clock();

  int row=80;
  int col=80;

  int **mat = (int**) malloc( sizeof( int*) * row);
  for(int i=0; i<row; i++)
  {
    int* row = (int*) malloc( sizeof( int) * col);
    mat[i] = row;
  }

  //string fname = "p081_matrix.small.txt";
  string fname = "p081_matrix.txt";
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

  cout << "MATRIX DEBUG!" << endl;
  for(int y=0; y<row; y++)
  {
    for(int x=0; x<col; x++)
    {
      cout << mat[y][x] << " ";
    }
    cout << endl;
  }

  // how to?
  int **memo = (int**) malloc( sizeof( int*) * row);
  for(int i=0; i<row; i++)
  {
    int* row = (int*) malloc( sizeof( int) * col);
    for(int j=0; j<col; j++) row[j] = 0;
    memo[i] = row;
  }

  int min = getMinPathValue( row-1, col-1, mat, memo);
  cout << "min=" << min << endl;

	clock_t end = clock();
	std::cout << "elapsed=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
