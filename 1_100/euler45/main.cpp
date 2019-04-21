/*
 	Problem 45 - Triangular, pentagonal, and hexagonal 
*/
#include <iostream>
#include <ctime>

using namespace std;

unsigned int getTriangular( unsigned int n)
{
	return n*(n+1)/2;
}

unsigned int getPentagonal( unsigned int n)
{
	return n*(3*n-1)/2;
}

unsigned int getHexagonal( unsigned int n)
{
	return n*(2*n-1);
}

int main(int argc, char** argv)
{
	clock_t begin = clock();

	/* starting code */
	unsigned int h = 143 + 1;
	unsigned int p = 165;
	unsigned int t = 285;

	unsigned int hn = getHexagonal( h);
	unsigned int pn = getPentagonal( p);
	unsigned int tn = getTriangular( t);

	while( true) {
		if ((hn == pn) && (hn == tn)) {
			break;
		}

		if( hn < pn) {
			while( hn < pn) {
				h++;
				hn = getHexagonal( h);
			}
			continue;
		}
		
		if( pn < tn) {
			while( pn < tn) {
				p++;
				pn = getPentagonal( p);
			}
		}

		if( tn < hn) {
			while( tn < hn) {
				t++;
				tn = getTriangular( t);
			}
		}
	}

	/* end of code */
	cout << "found number '" << hn << "' at h=" << h << ", p=" << p << ", t=" << t << endl;

	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
