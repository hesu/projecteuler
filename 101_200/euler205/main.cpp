/*
  Problem 205 - Dice Game
*/

#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <vector>
#include <map>

using namespace std;

vector<unsigned int> get_next_case(const vector<unsigned int>& before_case, const vector<unsigned int>& dice)
{
  vector<unsigned int> v;

  for(int i=0; i < before_case.size(); i++)
  {
    for(int j=0; j < dice.size(); j++)
    {
      v.push_back(before_case[i] + dice[j]);
    }
  }

  return v;
}

int main(int argc, char** argv)
{
  clock_t begin = clock();

  unsigned long long int whole = pow(4,9) * pow(6,6);
  cout << "whole=" << whole << endl;

  vector<unsigned int> pydice = {1,2,3,4};
  vector<unsigned int> cudice = {1,2,3,4,5,6};

  vector<unsigned int> p2 = get_next_case(pydice, pydice);
  vector<unsigned int> p3 = get_next_case(p2, pydice);
  vector<unsigned int> p4 = get_next_case(p3, pydice);
  vector<unsigned int> p5 = get_next_case(p4, pydice);
  vector<unsigned int> p6 = get_next_case(p5, pydice);
  vector<unsigned int> p7 = get_next_case(p6, pydice);
  vector<unsigned int> p8 = get_next_case(p7, pydice);
  vector<unsigned int> p9 = get_next_case(p8, pydice);

  vector<unsigned int> c2 = get_next_case(cudice, cudice);
  vector<unsigned int> c3 = get_next_case(c2, cudice);
  vector<unsigned int> c4 = get_next_case(c3, cudice);
  vector<unsigned int> c5 = get_next_case(c4, cudice);
  vector<unsigned int> c6 = get_next_case(c5, cudice);

/*
  for(int i=0; i < pydice_case.size(); i++)
    cout << pydice_case[i] << ",";
  cout << endl;
*/

cout << "p9.size=" << p9.size() << " c6.size=" << c6.size() << endl;

  map<unsigned int, unsigned int> map_p9;
  map<unsigned int, unsigned int> map_c6;

  for(int i=0; i < p9.size(); i++)
  {
    unsigned int dice_sum = p9[i];
    auto iter = map_p9.find(dice_sum);
    if (iter == map_p9.end())
    {
      map_p9[dice_sum] = 1;
    }
    else
    {
      iter->second++;
    }
  }

/*
  for(auto iter = map_p9.begin(); iter != map_p9.end(); iter++)
    cout << "(" << iter->first << "," << iter->second << ")";
  cout << endl;
  */
  
  for(int i=0; i < c6.size(); i++)
  {
    unsigned int dice_sum = c6[i];
    auto iter = map_c6.find(dice_sum);
    if (iter == map_c6.end())
    {
      map_c6[dice_sum] = 1;
    }
    else
    {
      iter->second++;
    }
  }


  unsigned long long int win = 0;
  for(auto piter = map_p9.begin(); piter != map_p9.end(); piter++)
  {
    for(auto citer = map_c6.begin(); citer != map_c6.end(); citer++)
    {
      if (piter->first > citer->first)
      {
        win += piter->second * citer->second;
      }
    }
  }

  cout << "wincount=" << win << endl;


  cout << (float)win/whole << endl;

  clock_t end = clock();
  std::cout << "elapsed time=" << double( end-begin) / CLOCKS_PER_SEC << endl;
}
