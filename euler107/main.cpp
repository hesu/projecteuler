/*
 	Problem 107 - Minimal network
*/
	
#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
using namespace std;

// vertex : int id, map<int vertex, int weight>

class Vertex
{
  private :
  int id;
  map<int, int> m; // otherId, weight

  public :
  Vertex(int _id)
  {
    id = _id;
  }

  void connect(int otherId, int weight)
  {
    m.insert(map<int,int>::value_type(otherId, weight));
  }

  int weightSum()
  {
    int sum = 0;
    for(auto it = m.begin(); it != m.end(); it++)
    {
      sum += it->second;
    }
    return sum;
  }
};

class Network
{
  public :
  
  Network(string fname)
  {
    ifstream inf(fname);
    string line;
    int linecnt = 0;
    
    while (getline(inf,line))
    {
      linecnt++;

      Vertex v(linecnt);
      
      istringstream iss(line);
      string token;

      int otherId = 0;
      while (getline(iss, token, ','))
      {
        otherId++;
        if (token != "-")
        {
          v.connect( otherId, stoi(token));
        }
      }

      vertices.push_back(v);
    }

    inf.close();
  }

  int weightSum()
  {
    int sum = 0;
    for(int i=0; i<vertices.size(); i++)
    {
      sum += vertices[i].weightSum();
    }
    return (sum/2);
  }

  void reduceWeight()
  {
    /////////
    // TODO
    /////////
  }

  private :
    vector<Vertex> vertices;
};

int main(int argc, char** argv)
{
	clock_t begin = clock();

	/* starting code */
  Network n("p107_network.small.txt");
  int sum = n.weightSum();
  cout << "sum=" << sum << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
