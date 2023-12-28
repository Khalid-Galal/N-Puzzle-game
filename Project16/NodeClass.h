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
	  NodeClass(NodeClass, vector<vector<int>>, int, int);
	  NodeClass();
};

