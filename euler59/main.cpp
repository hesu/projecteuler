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

#include <bitset> // http://stackoverflow.com/questions/7349689/c-how-to-print-using-cout-the-way-a-number-is-stored-in-memory/7349767

using namespace std;

unsigned char getCipherCode_e( std::vector<int> c)
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
	return static_cast<unsigned char>(e);
}

unsigned char getEncryptionKey( unsigned char encrypted_e)
{
	cout << "encrypted_e=" << encrypted_e << endl;
	// encrypted_e XOR key = 'e'
	// 'e' XOR key = encrypted_e
	// key = ?
	unsigned char e = 'e';
	for(unsigned char k='a'; k<='z'; k++)
	{
		unsigned char v1 = e^k;
		unsigned char v2 = encrypted_e^k;
		if( v1 == v2) {

			cout << "e^k" << endl;
			unsigned char v = e^k;
			std::bitset<8> x(v);
			std::cout << x << endl;
			
			cout << "encrypted_e^k" << endl;
			unsigned char v2 = encrypted_e^k;
			std::bitset<8> x2(v2);
			std::cout << x2 << endl;
			
			return k;
		}
	}
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

	unsigned char k1 = getEncryptionKey( getCipherCode_e( c1));
	cout << "key1=" << k1 << endl;
	unsigned char k2 = getEncryptionKey( getCipherCode_e( c2));
	cout << "key2=" << k2 << endl;
	unsigned char k3 = getEncryptionKey( getCipherCode_e( c3));
	cout << "key3=" << k3 << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
