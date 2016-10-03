/*
  Problem 66 - Diophantine equation
*/

#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>
#include <algorithm>

#include "BigInt.h"

using namespace std;

int main(int argc, char** argv)
{
  clock_t begin = clock();

  /*
  BigInt n(pow(3, 2));
  BigInt sqr = n.squareRoot();
  cout << "n=" << n.toString() << " sqr=" << sqr.toString() << endl;
  */

  std::vector<int> dvec;
  for(int i=1; i<=1000; i++)
  {
    double sqrted = sqrt( i);
    if( sqrted != ceil(sqrted)) {
      dvec.push_back(i); 
    }
  }

  cout << "dvec.size()=" << dvec.size() << endl;

  BigInt maxX(0);
  int atD;

  for(int i=0; i<dvec.size(); i++)
  {
    //BigInt xSq = BigInt(1) + 
    BigInt d(dvec[i]); 

    for(int y=1;;y++)
    {
      if( y%1000 == 0) { cout << "\t\ty=" << y << endl; }
      BigInt _y(y);
      BigInt ysq = _y * _y;
      BigInt ysqd = ysq * d;
      BigInt xsq = BigInt(1) + ysqd;
      
      BigInt x = xsq.squareRoot();
       // cout << "ysq=" << ysq.toString() << " ysqd=" << ysqd.toString() << " xsq=" << xsq.toString() << endl;
      if (!(x == BigInt(0))) {
        cout << "x=" << x.toString() << " at d=" << d.toString() << " y=" << y << endl;
        
        if (maxX < x) {
          cout << "maxX change" << endl;
          maxX = x;
          atD = dvec[i];
        }

        break;
      } 
    }
  }

  cout << "maxX = " << maxX.toString() << " at d=" << atD << endl;

  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
