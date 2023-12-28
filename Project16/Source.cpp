#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<list>
#include<cmath>
#include<queue>
#include< tgmath.h >
#include< tgmath.h >
#include< tgmath.h >
//#include "NodeClass.h"

using namespace std;

#define NULL 0
class NodeClass
{

public:
	int cost;
	int level;
	vector <vector <int>> puzzle;
	//Node P= Node();
	NodeClass* Parent;

	NodeClass()
	{
		this->puzzle = puzzle;
		this->cost = cost;
		this->level = level;
		this->Parent = Parent;
	}

	NodeClass(NodeClass N, vector<vector<int>> puzzle, int cost, int level)
	{

		this->puzzle = puzzle;
		this->cost = cost;
		this->level = level;
		this->Parent = &N;
	}
	NodeClass(vector<vector<int>> puzzle, int cost, int level)
	{

		this->puzzle = puzzle;
		this->cost = cost;
		this->level = level;
	}
};

NodeClass globalParent;
priority_queue<NodeClass> golbalQ;
vector<vector<int>>globalPuzle;

vector<NodeClass>globalList;


bool operator<(const NodeClass& p1, const NodeClass& p2)
{
	//return (p1.cost ) > (p2.cost );
	return (p1.cost + p1.level) > (p2.cost + p2.level);
}
static void printingnPuzzle(vector<vector<int>> vecObj)
{
	for (int i = 0; i < vecObj.size(); i++) {
		for (int j = 0; j < vecObj[i].size(); j++) {
			cout << vecObj[i][j] << " ";
		}
		cout << endl;
	}
}
//
//void displayPath()
//{
//	try
//	{
//		while (globalParent.level != 0)
//		{
//			globalList.push_back(globalParent);
//			globalParent = globalParent.Parent;
//		}
//	}
//	catch (const std::exception&)
//	{
//
//	}
//	
//	for (int i = globalList.size()-1; i >= 0; i--)
//	{
//		printingnPuzzle(globalList.at(i).puzzle);	
//	}
//}

string getPuzzleAsString(vector<vector<int>> puzzle)
{
	string str = "";
	for (int i = 0; i < puzzle.size(); i++) {
		for (int j = 0; j < puzzle[i].size(); j++) {
			str += to_string(puzzle[i][j]) + "/";
		}
	}
	return str;
}
vector <string> puzzlesHistory;
bool havingSamePuzzle(vector<vector<int>> newPuzzle)
{
	string puzzleStr = getPuzzleAsString(newPuzzle);
	for (int i = 0; i < puzzlesHistory.size(); i++)
	{
		if (puzzlesHistory.at(i) == puzzleStr)
			return true;
	}
	return false;
}

//void printPath(NodeClass n)
//{
//	
//	while (globalParent.level!=0)
//	{
//		globalList.push_back(globalParent);
//		globalParent = globalParent.Parent();
//
//	}
//	printingnPuzzle(n.puzzle);
//}


vector<vector<int>> readPuzzleFromFile(string fileName)
{
	//15 Puzzle - Case 2
		//	15 Puzzle - Case 3
		//	15 Puzzle 1 - Unsolvable 
	//ifstream file{ "8 Puzzle (3).txt" };
	ifstream file{ fileName };
	//if (!file.is_open())
	//	return vecObj;

	int nSize;
	file >> nSize;

	vector<vector<int>> vecObj(nSize);
	//vector<vector<int>> vecObj2(size1);
	vector<vector<vector<int>>> vecObj3;

	cout << "Matrix >> N * N " << nSize << endl;

	//========================== put values in the array from file ======================//
	for (int i{}; i != nSize; ++i) {
		for (int j{}; j != nSize; ++j) {
			int tmp;
			file >> tmp;
			vecObj[i].push_back(tmp);
		}
	}

	return vecObj;
}

int Manhattan(vector<vector<int>> vecObj, int n)
{
	int sum = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int sumx = 0;
			int sumy = 0;
			if (vecObj[i][j] > 0) {
				sumy = abs(i - (ceil((vecObj[i][j] + 0.0) / n) - 1));
				if ((vecObj[i][j] % n) == 0) {
					sumx = abs(j - (n - 1));
				}
				else
				{
					sumx = abs(j - ((vecObj[i][j] % n) - 1));
				}
				sum = sum + (sumx + sumy);
			}
		}
	}
	return sum;
}
int Hamming(vector<vector<int>> vecObj, int n)
{
	int sum = 0;
	int counter = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int sumx = 0;
			int sumy = 0;
			if (vecObj[i][j] > 0)
			{
				sumx = abs(i - (ceil(vecObj[i][j] + 0.0) / n) - 1);
				if ((vecObj[i][j] % n) == 0)
				{
					sumy = abs(j - (n - 1));
				}
				else
				{
					sumy = abs(j - ((vecObj[i][j] % n) - 1));
				}
				sum = (sumx + sumy);
				if (sum != 0)
					counter++;
			}
		}
	}
	return counter;
}


static void SwapDirections1(vector<vector<int>> vecObj, int x, int y)
{

	string nextPuzzleStr = "";
	vector<vector<int>> orgVec = vecObj;

	// RIGHT
	int largeCost = 9999999;
	priority_queue<NodeClass> TmpQ;
	if (vecObj[y][x] == 0 && x != vecObj.size() - 1)
	{

		swap(vecObj[y][x], vecObj[y][x + 1]);
		if (!havingSamePuzzle(vecObj))
		{
			int level = globalParent.level + 1;
			int cost = Manhattan(vecObj, vecObj.size());
			NodeClass perante = globalParent;
			NodeClass object = NodeClass(perante, vecObj, cost, level);
			TmpQ.push(object);
			//cout << "cost is : " << object.cost << "\t level is : " << object.level << endl;


		}
	}
	vecObj = orgVec;
	// LEFT
	if (vecObj[y][x] == 0 && x != 0)
	{
		swap(vecObj[y][x], vecObj[y][x - 1]);
		if (!havingSamePuzzle(vecObj)) {
			int level = globalParent.level + 1;
			int cost = Manhattan(vecObj, vecObj.size());
			NodeClass perante = globalParent;
			NodeClass object = NodeClass(perante, vecObj, cost, level);
			TmpQ.push(object);
			//cout << "cost is : " << object.cost << "\t level is : " << object.level << endl;

		}
	}
	vecObj = orgVec;
	// UP
	if (vecObj[y][x] == 0 && y != 0)
	{
		swap(vecObj[y][x], vecObj[y - 1][x]);
		if (!havingSamePuzzle(vecObj)) {
			int level = globalParent.level + 1;
			int cost = Manhattan(vecObj, vecObj.size());
			NodeClass perante = globalParent;
			NodeClass object = NodeClass(perante, vecObj, cost, level);
			TmpQ.push(object);
			//cout << "cost is : " << object.cost << "\t level is : " << object.level << endl;

		}
	}
	vecObj = orgVec;
	// DOWN
	if (vecObj[y][x] == 0 && y != vecObj.size() - 1)
	{
		swap(vecObj[y][x], vecObj[y + 1][x]);
		if (!havingSamePuzzle(vecObj)) {
			int level = globalParent.level + 1;
			int cost = Manhattan(vecObj, vecObj.size());
			NodeClass perante = globalParent;
			NodeClass object = NodeClass(perante, vecObj, cost, level);
			TmpQ.push(object);
			//cout << "cost is : " << object.cost << "\t level is : " << object.level << endl;

		}
	}
	while (TmpQ.size() > 0 )//  && largeCost >= (TmpQ.top().cost)
	{
		largeCost = TmpQ.top().cost;
		if (!havingSamePuzzle(TmpQ.top().puzzle)) {
			golbalQ.push(TmpQ.top());
			//cout << "cost is : " << TmpQ.top().cost << "\t level is : " << TmpQ.top().level << endl;
			TmpQ.pop();
		}

	}
}
static void SwapDirectionsH(vector<vector<int>> vecObj, int x, int y)
{

	string nextPuzzleStr = "";
	vector<vector<int>> orgVec = vecObj;

	// RIGHT
	int largeCost = 9999999;
	priority_queue<NodeClass> TmpQ;
	if (vecObj[y][x] == 0 && x != vecObj.size() - 1)
	{

		swap(vecObj[y][x], vecObj[y][x + 1]);
		if (!havingSamePuzzle(vecObj))
		{
			int level = globalParent.level + 1;
			int cost = Hamming(vecObj, vecObj.size());
			NodeClass perante = globalParent;
			NodeClass object = NodeClass(perante, vecObj, cost, level);
			TmpQ.push(object);
			//cout << "cost is : " << object.cost << "\t level is : " << object.level << endl;


		}
	}
	vecObj = orgVec;
	// LEFT
	if (vecObj[y][x] == 0 && x != 0)
	{
		swap(vecObj[y][x], vecObj[y][x - 1]);
		if (!havingSamePuzzle(vecObj)) {
			int level = globalParent.level + 1;
			int cost = Hamming(vecObj, vecObj.size());
			NodeClass perante = globalParent;
			NodeClass object = NodeClass(perante, vecObj, cost, level);
			TmpQ.push(object);
			//cout << "cost is : " << object.cost << "\t level is : " << object.level << endl;

		}
	}
	vecObj = orgVec;
	// UP
	if (vecObj[y][x] == 0 && y != 0)
	{
		swap(vecObj[y][x], vecObj[y - 1][x]);
		if (!havingSamePuzzle(vecObj)) {
			int level = globalParent.level + 1;
			int cost = Hamming(vecObj, vecObj.size());
			NodeClass perante = globalParent;
			NodeClass object = NodeClass(perante, vecObj, cost, level);
			TmpQ.push(object);
			//cout << "cost is : " << object.cost << "\t level is : " << object.level << endl;

		}
	}
	vecObj = orgVec;
	// DOWN
	if (vecObj[y][x] == 0 && y != vecObj.size() - 1)
	{
		swap(vecObj[y][x], vecObj[y + 1][x]);
		if (!havingSamePuzzle(vecObj)) {
			int level = globalParent.level + 1;
			int cost = Hamming(vecObj, vecObj.size());
			NodeClass perante = globalParent;
			NodeClass object = NodeClass(perante, vecObj, cost, level);
			TmpQ.push(object);
			//cout << "cost is : " << object.cost << "\t level is : " << object.level << endl;

		}
	}
	while (TmpQ.size() > 0)//  && largeCost >= (TmpQ.top().cost)
	{
		largeCost = TmpQ.top().cost;
		if (!havingSamePuzzle(TmpQ.top().puzzle)) {
			golbalQ.push(TmpQ.top());
			//cout << "cost is : " << TmpQ.top().cost << "\t level is : " << TmpQ.top().level << endl;
			TmpQ.pop();
		}

	}
}
/************************************************************************************************************/

static int getInvCount(vector<vector<int>> vecObj, int currentVal, int Itr1, int Itr2, int size)
{
	int InvCount = 0;
	for (int i = Itr1; i < size; i++)
	{
		for (int j = Itr2; j < size; j++)
		{
			if (currentVal > vecObj[i][j] && vecObj[i][j] > 0)
			{
				InvCount++;
			}
		}
		Itr2 = 0;
	}
	return InvCount;
}
static int getInvCount(vector<vector<int>> vecObj, int n)
{
	int invCount = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (vecObj[i][j] > 0)
				invCount += getInvCount(vecObj, vecObj[i][j], i, j, n);

	return invCount;
}

int findXPosition(vector<vector<int>> vecObj, int n)
{
	for (int i = n - 1; i >= 0; i--)
		for (int j = n - 1; j >= 0; j--)
			if (vecObj[i][j] == 0)
				return (n - i);
}

static void AStartAlgorithm(vector<vector<int>> vecObj)
{
	int cost = Manhattan(vecObj, vecObj.size());
	int level = 0;


	NodeClass Nodeclasss = NodeClass(vecObj, cost, level);
	globalPuzle = Nodeclasss.puzzle;
	globalParent = Nodeclasss;
	puzzlesHistory.push_back(getPuzzleAsString(globalPuzle));
	while (globalParent.cost != 0)
	{
		bool flag = true;
		int posX = 0, posY = 0;
		for (int i = 0; (i < globalPuzle.size() && flag); i++) {
			for (int j = 0; j < globalPuzle.size(); j++) {
				if (globalPuzle[i][j] == 0) {
					posX += j;
					posY += i;
					flag = false;
					break;
				}
			}
		}
	
		SwapDirections1(globalPuzle, posX, posY);
		

		globalParent = golbalQ.top();
		//cout << "system take cost is : " << globalParent.cost << "\t level is : " << globalParent.level << endl;
		golbalQ.pop();
		globalPuzle = globalParent.puzzle;
		//cout << getPuzzleAsString(globalPuzle) << endl;


		if (!havingSamePuzzle(globalPuzle)) {
			puzzlesHistory.push_back(getPuzzleAsString(globalPuzle));
		}
	}
	cout << globalParent.level << endl;
	cout << "size =" << puzzlesHistory.size() << endl;
}
static void AStartAlgorithmH(vector<vector<int>> vecObj)
{
	int cost = Hamming(vecObj, vecObj.size());
	int level = 0;


	NodeClass Nodeclasss = NodeClass(vecObj, cost, level);
	globalPuzle = Nodeclasss.puzzle;
	globalParent = Nodeclasss;
	puzzlesHistory.push_back(getPuzzleAsString(globalPuzle));
	while (globalParent.cost != 0)
	{
		bool flag = true;
		int posX = 0, posY = 0;
		for (int i = 0; (i < globalPuzle.size() && flag); i++) {
			for (int j = 0; j < globalPuzle.size(); j++) {
				if (globalPuzle[i][j] == 0) {
					posX += j;
					posY += i;
					flag = false;
					break;
				}
			}
		}

		SwapDirections1(globalPuzle, posX, posY);


		globalParent = golbalQ.top();
		//cout << "system take cost is : " << globalParent.cost << "\t level is : " << globalParent.level << endl;
		golbalQ.pop();
		globalPuzle = globalParent.puzzle;
		//cout << getPuzzleAsString(globalPuzle) << endl;


		if (!havingSamePuzzle(globalPuzle)) {
			puzzlesHistory.push_back(getPuzzleAsString(globalPuzle));
		}
	}
	cout << globalParent.level << endl;
	cout << "size =" << puzzlesHistory.size() << endl;
}

bool solvabal(vector<vector<int>> vecObj, int n)
{
	int x = findXPosition(vecObj, n);

	int invCount = getInvCount(vecObj, n);

	if (invCount % 2 == 0 && n % 2 != 0)
		return true;
	else if (n % 2 == 0 && invCount % 2 == 0 && x % 2 != 0)
	{
		return true;
	}
	else if (n % 2 == 0 && invCount % 2 != 0 && x % 2 == 0)
	{
		return true;

	}
	else
	{
		return false;
	}

}

int main()
{
	int index = 0;
	clock_t t1, t2;



	//Your code here



	//Time taken for running your code segment
	//vector<vector<int>> m1 = readPuzzleFromFile("C:\\Users\\Khaled\\source\\repos\\Project16\\Project16\\Testcases\\Complete\\Complete Test\\Solvable puzzles\\Manhattan Only\\15 Puzzle 1.txt");
	
	//vector<vector<int>> m1 = readPuzzleFromFile("C:\\Users\\Khaled\\source\\repos\\Project16\\Project16\\Testcases\\Complete\\Complete Test\\Solvable puzzles\\Manhattan & Hamming\\50 Puzzle.txt");
	
	/*8 Puzzle(1)
		8 Puzzle(2)
		8 Puzzle(3)
		15 Puzzle - 1
		24 Puzzle 1
		24 Puzzle 2*/



		////////////test case manhattan & hamming//////////////
	/*50 Puzzle.txt
		99 Puzzle - 1.txt
		99 Puzzle - 2.txt
		9999 Puzzle.txt*/



	//8 Puzzle - Case 1
	//	8 Puzzle(2) - Case 1
	//	8 Puzzle(3) - Case 1
	//	15 Puzzle - Case 2
	//	15 Puzzle - Case 3
	//	15 Puzzle 1 - Unsolvable
	//	99 Puzzle - Unsolvable Case 1
	//	99 Puzzle - Unsolvable Case 2
	//	9999 Puzzle




////////////test case manhattan & hamming//////////////
	/*50 Puzzle.txt
		99 Puzzle - 1.txt
		99 Puzzle - 2.txt
		9999 Puzzle.txt*/

	vector<vector<int>> m1 = readPuzzleFromFile("9999 Puzzle.txt");
	t1 = clock();
	if (solvabal(m1, m1.size())) {

		cout << "solvable" << endl;
		AStartAlgorithm(m1);
		//AStartAlgorithmH(m1);
		//puzzlesHistory.erase(unique(puzzlesHistory.begin(), puzzlesHistory.end()), puzzlesHistory.end());

		//cout << "puzzle size after clear =" << puzzlesHistory.size() << endl;
		//displayPath();
		
	}
	else
	{
		cout << "not solvable" << endl;
	}
	t2 = clock();


	double time_dif = ((double)(t2 - t1) / CLOCKS_PER_SEC)*1000;
	cout << "time_dif " << time_dif << " ms";

}


