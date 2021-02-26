#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Orgraph
{

private:
	vector<vector<int>> adjMatrix;
	int vertCount;

	vector<int> tIn;
	vector<int> tOut;
	vector<int> sortOut;
	int time = 0;

	void dfs(int u)
	{
		time++;
		tIn[u] = time;
		for (int i = 1; i <= vertCount; i++)
		{
			if (!tIn[i])
				dfs(i);
		}
		time++;
		tOut[u] = time;
		sortOut.insert(sortOut.begin(), u);
	}

	vector<vector<int>> rvMatrix;

	void reverseMatrix()
	{
		rvMatrix.resize(vertCount + 1);
		for (int i = 1; i <= vertCount; i++)
			rvMatrix[i].resize(vertCount + 1);
		for (int i = 1; i <= vertCount; i++)
			for (int j = i; j <= vertCount; j++)
			{
				rvMatrix[i][j] = adjMatrix[j][i];
				rvMatrix[j][i] = adjMatrix[i][j];
			}
	}

	vector<bool> rVisited;

	void rDfs(int u)
	{
		rVisited[u] = true;
		for (int i = 1; i <= vertCount; i++)
			if (rvMatrix[u][i] && !rVisited[i])
				rDfs(i);
	}

public:
	void graphInput(ifstream &input)
	{
		input >> vertCount;
		tIn.resize(vertCount + 1);
		tOut.resize(vertCount + 1);
		adjMatrix.resize(vertCount + 1);
		rVisited.resize(vertCount + 1);
		for (int i = 1; i <= vertCount; i++)
		{
			adjMatrix[i].resize(vertCount + 1);
			for (int j = 1; j <= vertCount; j++)
				input >> adjMatrix[i][j];
		}
	}

	void printGraph()
	{
		for (int i = 1; i <= vertCount ; i++)
		{
			for (int j = 1; j <= vertCount; j++)
				cout << adjMatrix[i][j] << ' ';
			cout << '\n';
		}
	}

	bool isStronglyConnected()
	{
		for (int i = 1; i <= vertCount; i++)
			if (!tIn[i])
				dfs(i);
		reverseMatrix();
		rDfs(sortOut[0]);
		for (int i = 1; i <= vertCount; i++)
			if (!rVisited[i])
				return false;
		return true;
	}

};

int main()
{
	ifstream input("input.txt");
	Orgraph gr;
	gr.graphInput(input);
	cout << gr.isStronglyConnected();
	input.close();
	return 0;
}