/*
 	Problem 62 - Cubic permutations
*/
	
#include <iostream>
#include <ctime>
#include <map>
#include <array>
#include <vector>
#include <string.h>
#include <cmath>

using namespace std;

std::map< std::array<int,10>, vector<unsigned long int>> cubemap;

int main(int argc, char** argv)
{
	clock_t begin = clock();
	/* starting code */
	for(int i=1;; i++)
	{
		char buf[1024] = {'0',};
		unsigned long int cubenum = pow(i, 3);
		sprintf( buf, "%lu", cubenum);

		std::array<int, 10> arr = {0,0,0,0,0,0,0,0,0,0};
		for(int j=0; j<strlen(buf); j++)
		{
			int val = buf[j] - '0';
			arr[val]++;
		}

		// dbg
		/*
		for( const auto&s : arr) std::cout << s << ' ';
		cout << endl;
		*/
		
		auto it = cubemap.find( arr);
		if( it == cubemap.end()) {
			std::vector<unsigned long int> v;
			v.push_back( cubenum);
			cubemap.emplace( arr, v);
		} else {
			it->second.push_back( cubenum);

			if (it->second.size() == 5) {
				cout << "found! i=" << i << endl;
				unsigned long int mincub;
				for(int j=0; j<it->second.size(); j++)
				{
					if( j == 0) { 
						mincub = it->second[j]; 
					} 
					if( mincub > it->second[j]) {
						mincub = it->second[j];	
					}
				}
				cout << "mincub=" << mincub << endl;
				break;
			} 
		}
	}

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
