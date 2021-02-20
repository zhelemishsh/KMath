#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

class Graph
{
	struct vertPointer
	{
		int enter = 0;
		int up = 0;
	};

private:
	vector<vector<int>> adjMatrix;
	int vertCount, edgeCount;

	vector<vertPointer> tinup;
	vector<int> resultAP;
	int time = 0;
	int rCount = 0;
	void dfsAP(int u, int from)
	{
		bool outWas = false;
		time++;
		tinup[u].enter = time;
		tinup[u].up = time;
		for (int i = 0; i < vertCount; i++)
		{
			if (adjMatrix[u][i])
			{
				if (!tinup[i].enter)
				{
					if (u == 0)
						rCount++;
					dfsAP(i, u);
					tinup[u].up = min(tinup[u].up, tinup[i].up);
					if (!outWas && u != 0 && tinup[i].up >= tinup[u].enter)
					{
						outWas = true;
						resultAP.push_back(u);
					}
				}
				else
					if (tinup[u].enter > tinup[i].enter && i != from)
					{
						tinup[u].up = min(tinup[u].up, tinup[i].enter);
					}
			}
		}
	}

public:
	void graphInput(ifstream &input)
	{
		input >> vertCount >> edgeCount;
		adjMatrix.resize(vertCount);
		for (int i = 0; i < edgeCount; i++)
		{
			int v1, v2;
			input >> v1 >> v2;
			adjMatrix[v1].resize(vertCount);
			adjMatrix[v2].resize(vertCount);
			adjMatrix[v1][v2] = 1;
			adjMatrix[v2][v1] = 1;
		}
	}

	void printGraph()
	{
		for (int i = 0; i < vertCount; i++)
		{
			for (int j = 0; j < vertCount; j++)
				cout << adjMatrix[i][j] << ' ';
			cout << '\n';
		}
	}

	vector<int> articularPoints()
	{
		resultAP.resize(0);
		tinup.resize(vertCount);
		dfsAP(0, 0);
		if (rCount > 1)
			resultAP.push_back(0);
		tinup.resize(0);
		return resultAP;
	}

};

int main()
{
	Graph gr;
	ifstream input("input.txt");
	gr.graphInput(input);
	vector<int> res = gr.articularPoints();
	for (int i = 0; i < res.size(); i++)
		cout << res[i] << ' ';
	input.close();
}
