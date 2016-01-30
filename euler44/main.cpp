/*
 	Problem 44 - Pentagon numbers 
*/
#include <iostream>
#include <ctime>
#include <map>

std::map<int,int> pentagonals;

using namespace std;

int main(int argc, char** argv)
{
	clock_t begin = clock();
	/* starting code */
	std::map<int,int>::iterator it;
	std::map<int,int>::iterator exist;
	int nextn = 1;

	while( true) {
		int newp = nextn*(3*nextn-1)/2;

		for( it = pentagonals.end(); it != pentagonals.begin(); --it)
		{
			int diff = newp - it->first;
			exist = pentagonals.find( diff);
			if( exist != pentagonals.end()) {

				int sum = newp + it->first;

				for( int i=nextn+1;;i++)
				{
					int tri = i*(3*i-1)/2;
					exist = pentagonals.find(tri);
					if ( exist == pentagonals.end()) {
						pentagonals.insert( std::map<int,int>::value_type( tri, tri));
					}

					if( sum == tri) {
						cout << "found! newp=" << newp << " with " << it->first << ", so diff=" << newp-it->first << endl;
						goto done;
					}
					if (tri > sum) { break;}
				}

			}
		}
	
		exist = pentagonals.find(newp);
		if ( exist == pentagonals.end()) {
			pentagonals.insert( std::map<int,int>::value_type( newp, newp));
		}
		nextn++;
	}

done:
	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
