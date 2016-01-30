/*
 	Problem 42 - Coded triangle numbers 
*/
	
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <map>

using namespace std;

std::map<int,int> triangleNum;

bool isTriangleNum( int n)
{
	std::map<int,int>::iterator it = triangleNum.find(n);
	if( it != triangleNum.end()) return true;
	
	for(int i=1;; i++)
	{
		int tn = i*(i+1)/2;
		if ( n < tn) break; 
		if ( n == tn) {
			triangleNum.insert( std::map<int,int>::value_type( tn, tn));
			return true;	
		}
	}
	return false;
}

bool isTriangleWord( std::string s)
{
	int sum = 0;
	// skip first & last '"'
	for(unsigned int i=1; i<s.size()-1; i++)
	{
		sum += s[i] - 'A' + 1;
		//cout << "s[i]=" << s[i] << " to int=" << int(s[i]) - int('A') << endl;
	}
	//cout << "s=" <<s << " sum=" << sum << endl;
	return isTriangleNum( sum);
}

int main(int argc, char** argv)
{
	clock_t begin = clock();
	/* starting code */
	int nTriangleWords = 0;
	
	string line;
	ifstream f("p042_words.txt");
	if(f.is_open())
	{
		getline( f, line);
		f.close();
	}

	string wordsDelim = ",";
	size_t lenDelim = wordsDelim.length();
	size_t pos = 0;

	while((pos = line.find(wordsDelim)) != std::string::npos) {
		string token = line.substr( 0, pos);

		if( isTriangleWord( token)) {
			nTriangleWords++;
		}

		line.erase( 0, pos + lenDelim); 
	}

	cout<< "nTriangleWords=" << nTriangleWords << endl;
	cout << "SKY is triangle word? " << isTriangleWord( "\"SKY\"") << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
