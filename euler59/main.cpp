/*
 	Problem 59 - XOR decryption
*/
	
#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <cstdlib> // atoi()
#include <algorithm>

using namespace std;

char getCipherCode_e( std::vector<int> c)
{
	// get 'e' cipher code (most frequent)
	std::map<int,int> frequency;
	for(int i=0; i<c.size(); i++)
	{
		std::map<int,int>::iterator it;
		it = frequency.find( c[i]);
		if( it != frequency.end()) { (it->second)++; }
		else { frequency.insert( std::map<int,int>::value_type( c[i], 1)); }
	}

	int e = 0, maxv = 0;
	for( std::map<int,int>::iterator it = frequency.begin(); it != frequency.end(); it++)
	{
		if ((it->second) > maxv) { e = it->first; maxv = it->second; }
	}

	cout << "max key('e') = " << e << ", maxv=" << maxv << endl;
	return e;
}

int main(int argc, char** argv)
{
	clock_t begin = clock();
	/* starting code */
	
	std::vector<int> cipher;
	
	string line;
	ifstream f("p059_cipher.txt");
	if( f.is_open())
	{
		getline( f, line);
		f.close();
	}

	cout << "line=" << line << endl;

	string wordsDelim = ",";
	size_t lenDelim = wordsDelim.length();
	size_t pos = 0;
	
	while((pos = line.find(wordsDelim)) != std::string::npos) {
		string token = line.substr( 0, pos);
		cipher.push_back(atoi( token.c_str()));
		line.erase( 0, pos + lenDelim);
	}
	cipher.push_back(atoi( line.c_str())); // last

	std::vector<int> c1;
	std::vector<int> c2;
	std::vector<int> c3;

	for(int i=0; i<cipher.size(); i++)
	{
		if( i%3 == 1) { c1.push_back( cipher[i]);
		} else if( i%3 == 2) { c2.push_back( cipher[i]);
		} else { c3.push_back( cipher[i]); }
	}


	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
