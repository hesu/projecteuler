/*
  Problem 78 - Coin partitions
*/

#include <iostream>
#include <ctime>
#include <map>

using namespace std;

#define MAX 1000000

bool max_overed = true;

map<long long int, long long int> waysmap;

long long int pentagonal_number( long long int n)
{
  return (n * ( 3*n - 1) / 2);
}

long long int coin_partition( long long int n)
{
  if( n == 0) return 1;
  if( n == 1) return 1;

  long long int sum = 0;
  int sign = 1;
  
  map<long long int, long long int>::iterator it;
  it = waysmap.find(n);
  if( it != waysmap.end()) { return it->second; }

  for(int i=1;i<n;i++)
  {
    int sign;
    if( i%2 == 0) { sign = -1; } else {sign = 1; }

    int each = pentagonal_number( i);
    int each2 = pentagonal_number( (-1) * i);

    //cout << "n=" << n << " t1=" << each << " t2=" << each2 << " sign=" << sign << endl;
    
    if( each < 0 || n< each) break;
    int val;
      it = waysmap.find( n-each);
      if( it == waysmap.end()) {
        val =  sign * coin_partition(n-each);
      } else{
        val = sign * (it->second);
      }

    sum += val;
    //cout << "\tval=" << val << endl;
    
    if( each2 < 0 || n < each2) break;
    int val2;
      it = waysmap.find( n-each2);
      if( it == waysmap.end()) {
        val2 =  sign * coin_partition(n-each2);
      } else{
        val2 = sign * (it->second);
      }

    sum += val2;
//    cout << "\tval2=" << val2 << endl;
  }


  if( max_overed) {
    sum = sum % ( MAX * 10);
  }

  it = waysmap.find( n);
  if (it == waysmap.end()) {
    waysmap.insert( map<long long int, long long int>::value_type( n, sum));
  }
//  cout << "sum(" << sum << ") for n=" << n << endl;

  return sum;
}

int main(int argc, char** argv)
{
  clock_t begin = clock();

/*
  cout << "cp(1)=" << coin_partition(1) << endl;
  cout << "cp(2)=" << coin_partition(2) << endl;
  cout << "cp(3)=" << coin_partition(3) << endl;
  cout << "cp(4)=" << coin_partition(4) << endl;
  cout << "cp(5)=" << coin_partition(5) << endl;
  cout << "cp(6)=" << coin_partition(6) << endl;
*/ 
  long long int sol=1;
  while(true)
  {
    long long int par = coin_partition( sol);
    if( max_overed && par % MAX == 0) break;
    sol++;
  }
  cout << "sol=" << sol << endl;

  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
