#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<list>
#include<cmath>
#include<queue>
#include< tgmath.h >


using namespace std;
class NodeClass
{

public:
	int cost;
	int level;
	 vector <vector <int>> puzzle;
	  //Node P= Node();
	  //NodeClass *P;
	  /*Node(vector<vector<int>> puzzle, int cost, int level)
	  {
		  Node N = NULL;
		  this->puzzle = puzzle;
		  this->cost = cost;
		  this->level = 0;
	  }*/
	  NodeClass()
	  {
		  this->puzzle = puzzle;
		  this->cost = cost;
		  this->level = level;
	  }

	  NodeClass(NodeClass N, vector<vector<int>> puzzle, int cost, int level)
	  {

		  this->puzzle = puzzle;
		  this->cost = cost;
		  this->level = level;
	  }
};

