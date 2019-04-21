/*
 	Problem 107 - Minimal network
*/
	
#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

class Edge
{
  public :
  Edge(int _cost, int _a, int _b)
  {
    cost = _cost;
    a = _a;
    b = _b;
    reducible = false;
  }

  int getCost() const { return cost; }
  int getA() { return a; }
  int getB() { return b; }
  bool getReducible() const { return reducible; }
  void setReducible(bool b) { reducible = b; }

  private :
  int cost;
  int a;
  int b;
  bool reducible;
};

class Vertex
{
  private :
  int id;

  public :
  map<int, int> m; // otherId, weight
 
  Vertex(int _id)
  {
    id = _id;
  }

  void connect(int otherId, int weight)
  {
    m.insert(map<int,int>::value_type(otherId, weight));
  }

  void unconnect(int otherId)
  {
    m.erase(otherId);
  }

  bool isConnected(int otherId)
  {
    auto iter = m.find(otherId);
    if (iter != m.end()) { return true; }
    return false;
  }

  int getCost(int otherId)
  {
    if (id == otherId) return 0;
    
    auto iter = m.find(otherId);
    if (iter == m.end()) return -1;
    return iter->second;
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
  
bool sortEdges( const Edge &lhs, const Edge &rhs)
{
  return (lhs.getCost() > rhs.getCost());
}

class Network
{
  public :
  Network()
  {
    reducedNetwork = false;
  }
  
  void init(string fname)
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
          int cost = stoi(token);
          v.connect( otherId, cost);

          if (linecnt < otherId)
          {
            Edge e(cost, linecnt, otherId);
            edges.push_back(e);
          }
        }
      }

      vertices.insert(map<int,Vertex>::value_type(linecnt, v));
    }

    inf.close();

    sort(edges.begin(), edges.end(), sortEdges);
    for(int i=0; i<edges.size(); i++) { cout << "[" << i << "] cost=" << edges[i].getCost() << endl; }
  }

  int weightSum()
  {
    int sum = 0;
    for(int i=0; i<edges.size(); i++)
    {
      if (edges[i].getReducible() == false)
      {
        sum += edges[i].getCost();
      }
    }
    return sum;
  }
  
  bool isConnectable(int id, int otherId, vector<int> notSearch)
  {
    cout << "\tisConnectable check : id=" << id << " other=" << otherId << endl;
    auto va = vertices.find(id);
    if (va == vertices.end()) {
      cout << "\tnot have " << id << endl;
      return false;
    }

    if(id == otherId) 
    {
      cout << "\t connected. id=" << id << " otherId=" << otherId << " (cost=" << va->second.getCost(otherId) << ")" << " notSearch.size=" << notSearch.size() << endl;
      for(int i=0; i<notSearch.size(); i++){ cout << "[" << notSearch[i] << "]-";}
      cout << "[" << id << "]-[" << otherId << "]" << endl;
      return true;
    }

    if (va->second.isConnected(otherId))
    {
      cout << "\t connected. id=" << id << " otherId=" << otherId << " (cost=" << va->second.getCost(otherId) << ")" << " notSearch.size=" << notSearch.size() << endl;
      for(int i=0; i<notSearch.size(); i++){ cout << "[" << notSearch[i] << "]-";}
      cout << "[" << id << "]-[" << otherId << "]" << endl;
      return true;
    }

    notSearch.push_back(id);
    
    //for(; va != vertices.end(); va++)
    for(auto vam = va->second.m.begin(); vam != va->second.m.end(); vam++)
    {
      int nextId = vam->first;
      //if(find(notSearch.begin(), notSearch.end(), thisId) != notSearch.end())
      if(find(notSearch.begin(), notSearch.end(), nextId) != notSearch.end())
      {
        cout << "\t continue;" << endl;
        continue;
      }

      cout << "call sub isConnectable nextId =" << nextId << endl;
      bool is = isConnectable(nextId, otherId, notSearch);
      if (is) return true;
    }

    return false;
  }

  void reduceWeight()
  {
    // 가장 weight 가 높은 edge 부터 하나씩 지워 나간다.
    bool done = false;
    while(!done)
    {
      bool reduced = false;
      for(int i=0; i<edges.size(); i++)
      {
        if (reducedNetwork) break;

        int a = edges[i].getA();
        int b = edges[i].getB();
        
        cout << " edges check : [" << a <<"]-/-[" << b << "]" << endl;
        auto va = vertices.find(a);
        if (va != vertices.end())
        {
          vector<int> notSearch;
          // remove edge from vertices
          int aCost = va->second.getCost(b);
          va->second.unconnect(b);

          auto vb = vertices.find(b);
          int bCost = va->second.getCost(a);
          vb->second.unconnect(a);
      
          notSearch.push_back(b);
          if (isConnectable(a, b, notSearch))
          {
            cout << "Remove " << a << ", " << b << " cost(" << edges[i].getCost() << ")" << endl;
            // remove edge from vertex
            va->second.unconnect(b);
            auto vb = vertices.find(a);
            if (vb != vertices.end())
            {
              vb->second.unconnect(a);
            }

            // update edge
            edges[i].setReducible(true);
            reduced = true;
          }
          else
          {
            // restore edge to vertices
            va->second.connect(b, aCost);
            vb->second.connect(a, bCost);
            done = true;
          }
        }
      }

      if (!reduced) { done = true; }
    }

  }

  private :
    map<int, Vertex> vertices;
    vector<Edge> edges;
    bool reducedNetwork;
};

int main(int argc, char** argv)
{
	clock_t begin = clock();

	/* starting code */
  Network n;
  //n.init("p107_network.small.txt");
  n.init("p107_network.txt");

  int sum = n.weightSum();
  cout << "sum=" << sum << endl;

  n.reduceWeight();
  int reducedSum = n.weightSum();
  cout << "reduced sum=" << reducedSum << " (saving " << sum - reducedSum << ")" << endl;

	/* end of code */
	clock_t end = clock();
	std::cout << "elapsed time=" << double(end - begin) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
