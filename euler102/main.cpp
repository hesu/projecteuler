/*
 	Problem 102 - Triangle containtment
*/

#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>

using namespace std;

class Point 
{
  public:
  float x;
  float y;

  Point(float _x, float _y)
  {
    x = _x;
    y = _y;
  }
};

// Is point(x1, y1) and point(x2,y2) are in same side divided by l1-l2 line plane?
bool isSameSide( Point l1, Point l2, Point a, Point b)
{
  float sidea = ((l2.x - l1.x) * (a.y - l1.y) - ( l2.y - l1.y) * ( a.x - l1.x));
  float sideb = ((l2.x - l1.x) * (b.y - l1.y) - ( l2.y - l1.y) * ( b.x - l1.x));
  return (sidea * sideb > 0);
}

bool pointInTriangle( float xp, float yp, float x1, float y1, float x2, float y2, float x3, float y3)
{
  Point a( x1, y1);
  Point b( x2, y2);
  Point c( x3, y3);
  Point origin(0, 0);

  if( isSameSide( a, b, origin, c) && isSameSide( b, c, origin, a) && isSameSide( a, c, origin, b)) {
    return true;
  }

  return false;
}

int main(int argc, char** argv)
{
	clock_t begin = clock();
	
  /* starting code */
//  cout << pointInTriangle( 0, 0, -340, 495, -153, -910, 835, -947) << endl;
 // cout << pointInTriangle( 0, 0, -175, 41, -421, -714, 574, -645) << endl;

  int cnt = 0;
  ifstream inf( "p102_triangles.txt");

  string line;
  while( std::getline( inf, line)) {
    std::vector<float> v;

    string delim = ",";
    size_t lenDelim = delim.length();
    size_t pos = 0;

    while(( pos = line.find( delim)) != std::string::npos) {
      string token = line.substr( 0, pos);
      line.erase( 0, pos + lenDelim);
      v.push_back(atof(token.c_str()));
    }
    v.push_back(atof(line.c_str()));
    if( pointInTriangle( 0, 0, v[0], v[1], v[2], v[3], v[4], v[5])) cnt++;
  }
  inf.close();
  cout << "cnt=" << cnt << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
