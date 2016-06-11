#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <string.h>
#include <sstream>
#include <fstream>

using namespace std;

std::map<int, std::map<int, int>> sequence;

int main(int argc, char** argv)
{
	clock_t begin = clock();

	/* starting code */
	string line;
	ifstream inf("p079_keylog.txt");

	while (std::getline(inf, line)) {
		int first = line[0] - '0';
		int second = line[1] - '0';
		int third = line[2] - '0';
		cout << first << second << third << endl;

		std::map<int, std::map<int, int>>::iterator it = sequence.find(first);
		if (it == sequence.end()) {
			std::map<int, int> secondMap;
			secondMap.insert(std::map<int, int>::value_type(second, third));
			sequence.insert(std::map<int, std::map<int,int>>::value_type(first, secondMap));
		}

		/*
		for (int i = 0; i < line.length(); i++) cout << "[" << i << "]" << line[i];
		cout << endl;
		*/

		/*
		int n; istringstream convert(line); convert >> n;
		cout << "n=" << n << endl;
		*/
	}

	/*
	ofstream of("output.txt");
	for (int i = 0; i<numbers.size(); i++) {
		BigInt m = BigInt(bmap.begin()->first);
		for (std::map<string, BigInt>::iterator it = bmap.begin(); it != bmap.end(); it++)
		{
			//cout << it->first << endl;
			if ((it->second <= numbers[i]) && m < it->second) {
				m = it->second;
			}
		}

		cout << "max for " << numbers[i].toString() << " = " << m.toString() << endl;
		of << m.toString() << endl;
	}
	of.close();
	*/

	cout << "Press Any Key.." << endl;
	fgetc(stdin);

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
