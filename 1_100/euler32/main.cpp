/*
 	Problem 32 - Pandigital products 
*/
	
// 987 = 654 * 321 (x) 
// 가능한 건 다음경우뿐..
// 4n = 3n * 2n, 2n * 2n, 4n * 1n

#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;
void permutation( std::vector<int>nums, std::vector<int> now)
{
	if (nums.size() == 0) {
		/*
		for(int i=0; i<now.size(); i++)
		{
			cout << now[i] << "-";
		}
		cout << endl;
		*/

		// case 1) 4n = 3n * 2n ?
		int n1 = now[0] * 1000 + now[1] * 100 + now[2] * 10 + now[3] * 1;
		int n2 = now[4] * 100 + now[5] * 10 + now[6] * 1;
		int n3 = now[7] * 10 + now[8] * 1;
		
		if( n1 == n2*n3) { cout << "pandigital n1=" << n1 << " ,n2=" << n2 << " ,n3=" << n3 << endl; }

		// case 2) 4n = 4n * 1n ?
		n2 = now[4] * 1000 + now[5] * 100 + now[6] * 10 + now[7] * 1;
		n3 = now[8] * 1;
		if( n1 == n2*n3) { cout << "pandigital n1=" << n1 << " ,n2=" << n2 << " ,n3=" << n3 << endl; }
		
		return;
	}
	for(int i=0; i<nums.size(); i++)
	{
		std::vector<int> newone( now);
		std::vector<int> newnums( nums);
		int val = newnums[i];
		newone.push_back( val); 
		newnums.erase( newnums.begin() + i);
		permutation( newnums, newone);
	}
}

int main(int argc, char** argv)
{
	clock_t begin = clock();

	/* starting code */
	std::vector<int> nums;
	nums.push_back(1);
	nums.push_back(2);
	nums.push_back(3);
	nums.push_back(4);
	nums.push_back(5);
	nums.push_back(6);
	nums.push_back(7);
	nums.push_back(8);
	nums.push_back(9);
	
	std::vector<int> now;
	permutation( nums, now);

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
