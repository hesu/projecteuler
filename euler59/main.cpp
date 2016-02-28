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

using namespace std;

int getCipherCode_e( std::vector<int> c)
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
//	return static_cast<int>(e);
	return e;
}

int getEncryptionKey( int encrypted_e)
{
	cout << "encrypted_e=" << encrypted_e << endl;
	// encrypted_e XOR key = 'e'
	// 'e' XOR key = encrypted_e
	// key = ?
	int e = 'e';
	for(int k='a'; k<='z'; k++)
	{
		int v1 = e^k;
		int v2 = encrypted_e^k;
		if( (v2 == e) && ( v1 == encrypted_e)) {
			cout << "e^k=" << v1 << endl;
			cout << "encrypted_e^k=" << v2 << endl;
			cout << "k=" << k << endl;
			return k;
		} else {
			cout << "not same with k '" << k << "'(" << char(k) << ")" << " 'e'^k=" << v1 << " encrypted 'e'^k=" << v2 << endl;
		}
	}
	cout << "return '?'" << endl;
	return '?';
}

int main(int argc, char** argv)
{
	clock_t begin = clock();
	/* starting code */

	/*
	int A = 'A';
	int star = '*';
	int k= 'k';
	int ixor;

	cout << "A=" << A << " star=" << star << " k=" << k << endl;
	ixor = A ^ star;
	cout << "A XOR star = " << ixor << endl;
	ixor = k ^ star;
	cout << "k XOR star = " << ixor << endl;
	*/

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

	cout << "chars cipher = " << cipher.size() << endl;

	std::vector<int> c1;
	std::vector<int> c2;
	std::vector<int> c3;
	for(int i=0; i<cipher.size(); i++)
	{
		if( i%3 == 1) { c1.push_back( cipher[i]);
		} else if( i%3 == 2) { c2.push_back( cipher[i]);
		} else { c3.push_back( cipher[i]); }
	}
	cout << "chars c1 = " << c1.size() << endl;
	cout << "chars c2 = " << c2.size() << endl;
	cout << "chars c3 = " << c3.size() << endl;

	int k1 = getEncryptionKey( getCipherCode_e( c1));
	cout << "key1=" << k1 << endl;
	int k2 = getEncryptionKey( getCipherCode_e( c2));
	cout << "key2=" << k2 << endl;
	int k3 = getEncryptionKey( getCipherCode_e( c3));
	cout << "key3=" << k3 << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
