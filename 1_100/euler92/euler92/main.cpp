#include <iostream>
#include <ctime>
#include <string>
#include <map>
#include <vector>

#define MAX 10000000

using namespace std;

std::map<int, int> smap;

int squareChains(int n, std::vector<int> chain)
{
	if (n == 1 || n == 89) {
		// End condition : memo vector
		for (int vi = 0; vi < chain.size(); vi++)
		{
			std::map<int,int>::iterator it = smap.find(chain[vi]);
			if (it == smap.end()) {
				smap.insert(std::map<int, int>::value_type(chain[vi], n));
			}
		}
		return n;
	}

	std::map<int, int>::iterator it = smap.find(n);
	if (it != smap.end()) {
		int retVal = it->second;
		return retVal;
	}

	int squareDigitSum = 0;
	string s = std::to_string(n);
	for (int i = 0; i < s.length(); i++)
	{
		int val = s[i] - '0';
		squareDigitSum += val*val;
	}
	chain.push_back(squareDigitSum);
	return squareChains(squareDigitSum, chain);
}

int main(int argc, char** argv)
{
	clock_t begin = clock();
	/* Starting Code */
	
	int cnt = 0;
	for (int i = 1; i <= MAX; i++)
	{
		cout << "i=" << i << endl;
		std::vector<int> chain;
		if (squareChains(i, chain) == 89) cnt++;
		//cout << i << " : digitsum=" << n << endl;
	}
	cout << "cnt=" << cnt << endl;

	/* End of Code */
	clock_t end = clock();
	cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << endl;
	cout << "Press Any Key.." << endl;
	fgetc(stdin);
	return 0;
}
