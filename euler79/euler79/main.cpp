#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <string.h>
#include <sstream>
#include <fstream>

using namespace std;

std::vector<int> findShortest(std::map<int, std::vector<int>> seq, std::map<int, std::vector<int>>::iterator seqit, std::vector<int> now, int startAt)
{
	cout << "findShortest!" << endl;
	if (now.size() == 0) {
		cout << "first!" << endl;
		now.push_back(seqit->first);
		for (int i = 0; i < seqit->second.size(); i++){ now.push_back(seqit->second[i]);}

		for (int i = 0; i < now.size(); i++) cout << now[i] << " ";
		cout << endl;

		return findShortest(seq, ++seqit, now, 1);
	} else {
		if (startAt >= now.size()) {
			cout << "need to sequence change. size=" << now.size() << " seqit->first=" << seqit->first << " seq.begin()->first=" << seq.begin()->first << " seq.end()->first" << seq.end()->first << endl;
			// END condition
			if (seqit->first == seq.begin()->first) { return now; }
			
			// check next sequence rule
			std::vector<int>::iterator vit = find(now.begin(), now.end(), seqit->first);
			if (vit == now.end()) {
				now.insert(now.begin(), seqit->first);
				return findShortest(seq, ++seqit, now, 1);
			}
			return findShortest( seq, ++seqit, now, startAt);
		}

			for (int j = startAt + 1; j < now.size(); j++)
			{
				std::map<int, std::vector<int>>::iterator jseq = seq.find(now[j]);
				if (jseq == seq.end()) { continue; }

				std::vector<int>::iterator vit = find(jseq->second.begin(), jseq->second.end(), now[startAt]);
				if (vit != jseq->second.end()) {
					cout << "[" << j << "]" << now[j] << " - [" << startAt << "]" << now[startAt] << " found at sequence rule" << endl;
					// need to change
					int swap = now[startAt];
					now[startAt] = now[j];
					now[j] = swap;
					
					cout << "swapped!" << endl;
					for(int x=0; x<now.size(); x++) cout << now[x] << " ";
					cout << endl;
					return findShortest( seq, seqit, now, startAt);
				}
			}

		for(int x=0; x<now.size(); x++) cout << now[x] << " ";
		cout << endl;
		return findShortest(seq, seqit, now, startAt+1);
	}
}

int main(int argc, char** argv)
{
	clock_t begin = clock();

	/* starting code */
	std::map<int, std::vector<int>> sequence;
	string line;
	ifstream inf("p079_keylog.txt");

	while (std::getline(inf, line)) {
		int first = line[0] - '0';
		int second = line[1] - '0';
		int third = line[2] - '0';
		//cout << first << second << third << endl;

		std::map<int, std::vector<int>>::iterator it = sequence.find(first);
		if (it == sequence.end()) {
			std::vector<int> v;
			v.push_back(second);
			sequence.insert(std::map<int, std::vector<int>>::value_type(first, v));
		} else {
			std::vector<int>::iterator vit = find(it->second.begin(), it->second.end(), second);
			if (vit == it->second.end()) {
				it->second.push_back(second);
			}
		}

		// same do with second & third
		it = sequence.find(second);
		if (it == sequence.end()) {
			std::vector<int> v;
			v.push_back(third);
			sequence.insert(std::map<int, std::vector<int>>::value_type(second, v));
		}
		else {
			std::vector<int>::iterator vit = find(it->second.begin(), it->second.end(), third);
			if (vit == it->second.end()) {
				it->second.push_back(third);
			}
		}
	}
	inf.close();

	for (std::map<int, std::vector<int>>::iterator it = sequence.begin(); it != sequence.end(); ++it)
	{
		cout << it->first << endl;
		for (std::vector<int>::iterator sit = it->second.begin(); sit != it->second.end(); ++sit)
		{
			cout << "\t" << *sit << endl;
		}
	}

	cout << endl;

	std::map<int, std::vector<int>>::iterator seqit = sequence.begin();
	std::vector<int> start;
	std::vector<int> sol = findShortest(sequence, seqit, start, 0);

	cout << "shortest solution=";
	for (std::vector<int>::iterator it = sol.begin(); it != sol.end(); ++it) cout << *it;
	cout << endl;

	cout << "Press Any Key.." << endl;
	fgetc(stdin);

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
