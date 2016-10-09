/*
 	Problem 83 - Path sum: four ways
*/

#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int minOf( vector<int> v)
{
  int min = v[0];
  for(int i=0;i<v.size();i++) {
    if( v[i] == -1) continue;
    if( min == -1) min = v[i];
    if( v[i] < min) min = v[i];
  }
  return min;
}

bool adjacent( pair<int,int> a, pair<int,int> b)
{
  if( a.first == b.first) {
    if (a.second + 1 == b.second) return true;
    if (a.second - 1 == b.second) return true;
  }

  if( a.second == b.second) {
    if (a.first+ 1 == b.first) return true;
    if (a.first- 1 == b.first) return true;
  }
  return false;
}

int value( int** mat, int size, pair<int,int> a)
{
  // first : y(row), second : x(col)
  return mat[ a.first][a.second];
}

void printpath( vector<pair<int,int>> path, int** mat)
{
  for(int i=path.size()-1; i>=0; i--)
  {
    cout << "[" << mat[path[i].first][path[i].second] << "]";
    if( i > 0) { cout << "-"; }
  }
  cout << endl;
}

bool inbound( pair<int,int> a, int matsize)
{
  if( a.first >= 0 && a.first <= matsize-1 && a.second >= 0 && a.second <= matsize-1){
    //cout << "inbound true x=" << a.second << " y=" << a.first << endl;
    return true;
  }
    //cout << "inbound false x=" << a.second << " y=" << a.first << endl;
  return false;
}

bool need_discovery( vector<pair<int,int>> visited, pair<int,int> p)
{
  if( find( visited.begin(), visited.end(), p) == visited.end()) return true;
  return false;
}

int getMinPathValue( pair<int,int> now, pair<int,int> goal, int **mat, int** memo, int matsize, vector<pair<int,int>> visited)
{
  if(adjacent( now, goal)) {
    int retval = value( mat, matsize, now) + value( mat, matsize, goal);
  //  cout << "adjacent! nowx=" << now.second << " nowy=" << now.first << " visited=" << visited.size() << " retval=" << retval << endl;
    return retval;
  } else {
   // cout << "nowx=" << now.second << " nowy=" << now.first << " visited=" << visited.size() << endl;
  }

  int northroot = -1, southroot = -1, eastroot = -1, westroot = -1;

  pair<int,int> n = make_pair(now.first-1, now.second);
  pair<int,int> s = make_pair(now.first+1, now.second);
  pair<int,int> e = make_pair(now.first, now.second+1);
  pair<int,int> w = make_pair(now.first, now.second-1);

  
  std::vector<pair<int,int>> visited_north( visited);
  std::vector<pair<int,int>> visited_south( visited);
  std::vector<pair<int,int>> visited_east( visited);
  std::vector<pair<int,int>> visited_west( visited);
  
  // north discover;
  if( inbound( n, matsize) && need_discovery( visited, n)) {
    visited_north.push_back( n);
    //cout << "call north " << endl;
    northroot = getMinPathValue( n, goal, mat, memo, matsize, visited_north);
  }
  
  // south discover;
  if( inbound( s, matsize) && need_discovery( visited, s)) {
    visited_south.push_back( s);
    //cout << "call south" << endl;
    southroot = getMinPathValue( s, goal, mat, memo, matsize, visited_south);
  }
  
  // east discover;
  if( inbound( e, matsize) && need_discovery( visited, e)) {
    visited_east.push_back( e);
    //cout << "call east" << endl;
    eastroot = getMinPathValue( e, goal, mat, memo, matsize, visited_east);
  }
  
  // west discover;
  if( inbound( w, matsize) && need_discovery( visited, w)) {
    visited_west.push_back( w);
    //cout << "call west" << endl;
    westroot = getMinPathValue( w, goal, mat, memo, matsize, visited_west);
  }

  //cout << "n=" << northroot << " s=" << southroot << " e=" << eastroot << " w=" << westroot << endl;
  std::vector<int> minroot = { northroot, southroot, eastroot, westroot };

  if( minOf(minroot) == -1) { 
  //   cout << "unexpected case at (" << now.second << "," << now.first << ")" << endl; 
//     return -1;
  }

  int retval = minOf(minroot) + value(mat, matsize, now);
  cout << "minval at (" << now.second << "," << now.first << ")=" << retval << endl; 

  if( minOf(minroot) == northroot) {
//    cout << "north root" << endl;
    printpath( visited_north, mat);
  }
  if( minOf(minroot) == southroot) {
 //   cout << "south root" << endl;
    printpath( visited_south, mat);
  }
  if( minOf(minroot) == westroot ) {
  //  cout << "west root" << endl;
    printpath( visited_west, mat);
  }
  if( minOf(minroot) == eastroot) {
   // cout << "east root" << endl;
    printpath( visited_east, mat);
  }

  return retval;
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

  pair<int,int> current = make_pair( row-1, col-1);
  pair<int,int> goal = make_pair( 0, 0);

  vector<pair<int,int>> visited;
  visited.push_back( current);

  char from = '0';
  int min = getMinPathValue( current, goal, mat, memo, matsize, visited);
  cout << "min=" << min << endl;

	clock_t end = clock();
	std::cout << "elapsed=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
