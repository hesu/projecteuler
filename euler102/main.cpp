/*
 	Problem 102 - Triangle containtment
*/

#define _USE_MATH_DEFINES
#include <math.h>
	
#include <iostream>
#include <ctime>
#include <cmath>

#include <fstream>
#include <vector>

using namespace std;

class Vector
{
  private:
    float x;
    float y;
  public:
    Vector( float _x1, float _y1, float _x2, float _y2)
    {
      x = _x1 - _x2;
      y = _y1 - _y2;
    }

    float getx() { return x;}
    float gety() { return y;}
    float getsize() { return sqrt( x*x + y*y); }

    float getBetweenAngle( Vector v) 
    { 
      return acos( (x * v.getx() + y * v.gety()) / (getsize() * v.getsize()));
    }
};

bool samecompare( float a, float b)
{
  float diff= a-b;
  if( diff < 0) diff *= -1;

  if( diff < 0.00001) return true;
  return false;
}

bool pointInTriangle( float xp, float yp, float x1, float y1, float x2, float y2, float x3, float y3)
{
  Vector v1(x1, y1, xp, yp);
  Vector v2(x2, y2, xp, yp);
  Vector v3(x3, y3, xp, yp);

  float a1 = v1.getBetweenAngle( v2);
  float a2 = v2.getBetweenAngle( v3);
  float a3 = v3.getBetweenAngle( v1);
  float theta = a1+a2+a3;
//  cout << "a1=" << a1 << " a2=" << a2 << " a3=" << a3 << " theta=" << theta << " 2PI=" << 2*M_PI << endl;

  if (samecompare((float)theta ,(float)2*M_PI)) return true;
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

  string save;
  string line;
  while( std::getline( inf, line)) {
    save = line;
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

    if( pointInTriangle( 0, 0, v[0], v[1], v[2], v[3], v[4], v[5])) {
      cout << "line=" << save << " pointInTriangle" << endl;
      cnt++;
    } else {
      cout << "line=" << save << endl;
    }
  }
  inf.close();

  cout << "cnt=" << cnt << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
