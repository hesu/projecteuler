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

int main(int argc, char** argv)
{
	clock_t begin = clock();

  int row=5;
  int col=5;

  int **mat = (int**) malloc( sizeof( int*) * row);
  for(int i=0; i<row; i++)
  {
    // TODO malloc
    int* row = (int*) malloc( sizeof( int) * col);
    mat[i] = row;
  }

  string fname = "p081_matrix.small.txt";
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


  cout << "DEBUG!" << endl;
  for(int y=0; y<row; y++)
  {
    for(int x=0; x<col; x++)
    {
      cout << mat[y][x] << " ";
    }
    cout << endl;
  }

	clock_t end = clock();
	std::cout << "elapsed=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
