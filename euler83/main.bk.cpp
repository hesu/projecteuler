/*
 	Problem 83 - Path sum: four ways
*/

#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>
#include <algorithm>

#include <climits>

using namespace std;

struct memo_s{
  // from
  int n;
  int s;
  int e;
  int w;
};
typedef struct memo_s memo_t;

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

int getMinPathValue( pair<int,int> now, pair<int,int> goal, int **mat, memo_t** memo, int matsize, vector<pair<int,int>> visited, int depth)
{
  if(adjacent( now, goal)) {
    int retval = value( mat, matsize, now) + value( mat, matsize, goal);
  //  cout << "adjacent! nowx=" << now.second << " nowy=" << now.first << " visited=" << visited.size() << " retval=" << retval << endl;
    return retval;
  } else {
   // cout << "nowx=" << now.second << " nowy=" << now.first << " visited=" << visited.size() << endl;
  }

  int northroot = -1, southroot = -1, eastroot = -1, westroot = -1;
  
  if( memo[now.first][now.second].n < INT_MAX ) { northroot = memo[now.first][now.second].n; }
  if( memo[now.first][now.second].s < INT_MAX ) { southroot = memo[now.first][now.second].s; }
  if( memo[now.first][now.second].e < INT_MAX ) { eastroot = memo[now.first][now.second].e; }
  if( memo[now.first][now.second].w < INT_MAX ) { westroot = memo[now.first][now.second].w; }

  pair<int,int> n, s, e, w;
  std::vector<pair<int,int>> visited_north, visited_south, visited_east, visited_west;
  
  // north discover;
  if( northroot == -1 && inbound( n, matsize) && need_discovery( visited, n)) {
    n = make_pair(now.first-1, now.second);
    visited_north = visited;
    visited_north.push_back( n);
    //cout << "call north " << endl;
    northroot = getMinPathValue( n, goal, mat, memo, matsize, visited_north, depth+1);
  }
  
  // south discover;
  if( southroot == -1 && inbound( s, matsize) && need_discovery( visited, s)) {
    s = make_pair(now.first+1, now.second);
    visited_south = visited;
    visited_south.push_back( s);
    //cout << "call south" << endl;
    southroot = getMinPathValue( s, goal, mat, memo, matsize, visited_south, depth+1);
  }
  
  // east discover;
  if( eastroot == -1 && inbound( e, matsize) && need_discovery( visited, e)) {
    e = make_pair(now.first, now.second+1);
    visited_east = visited;
    visited_east.push_back( e);
    //cout << "call east" << endl;
    eastroot = getMinPathValue( e, goal, mat, memo, matsize, visited_east, depth+1);
  }
  
  // west discover;
  if( westroot == -1 && inbound( w, matsize) && need_discovery( visited, w)) {
    w = make_pair(now.first, now.second-1);
    visited_west = visited;
    visited_west.push_back( w);
    //cout << "call west" << endl;
    westroot = getMinPathValue( w, goal, mat, memo, matsize, visited_west, depth+1);
  }

  //cout << "n=" << northroot << " s=" << southroot << " e=" << eastroot << " w=" << westroot << endl;
  std::vector<int> minroot = { northroot, southroot, eastroot, westroot };

  if( minOf(minroot) == -1) { 
     cout << "no-way out at (" << now.second << "," << now.first << ")" << endl; 
     return -1;
  }

  if( northroot != -1 && northroot < memo[now.first][now.second].n) { memo[ now.first][now.second].n = northroot; }
  if( southroot != -1 && southroot < memo[now.first][now.second].s) { memo[ now.first][now.second].s = southroot; }
  if( eastroot != -1 && eastroot < memo[now.first][now.second].e) { memo[ now.first][now.second].e = eastroot; }
  if( westroot != -1 && westroot < memo[now.first][now.second].w) { memo[ now.first][now.second].w = westroot; }

  int retval = minOf(minroot) + value(mat, matsize, now);
  return retval;
}

int main(int argc, char** argv)
{
	clock_t begin = clock();

  int matsize = 5;
  string fname = "p083_matrix.small.txt";
  //int matsize = 80;
  //string fname = "p083_matrix.txt";
  int row=matsize, col=matsize;

  int **mat = (int**) malloc( sizeof( int*) * row);
  for(int i=0; i<row; i++)
  {
    int* row = (int*) malloc( sizeof( int) * col);
    mat[i] = row;
  }

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

  memo_t **memo = (memo_t**) malloc( sizeof( memo_t*) * row);
  for(int i=0; i<row; i++)
  {
    memo_t* row = (memo_t*) malloc( sizeof( memo_t) * col);
    for(int j=0; j<col; j++) {
      row[j].n = INT_MAX;
      row[j].s = INT_MAX;
      row[j].e = INT_MAX;
      row[j].w = INT_MAX;
    }
    memo[i] = row;
  }
 
 /*
  int **memo = (int**) malloc( sizeof( int*) * row);
  for(int i=0; i<row; i++)
  {
    int* row = (int*) malloc( sizeof( int) * col);
    for(int j=0; j<col; j++) row[j] = 0;
    memo[i] = row;
  }
  */

  pair<int,int> current = make_pair( row-1, col-1);
  pair<int,int> goal = make_pair( 0, 0);

  vector<pair<int,int>> visited;
  visited.push_back( current);

  int min = getMinPathValue( current, goal, mat, memo, matsize, visited, 0);
  cout << "min=" << min << endl;

	clock_t end = clock();
	std::cout << "elapsed=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
