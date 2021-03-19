#include <iostream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

class Graph
{
private:
	vector<vector<int>> adjMatrix;
	vector<int> colors;
	int vertCount;
	int edgCount;

	bool isFullGraph(int vCount, int eCount)
	{
		return eCount == (vCount * vCount - vCount) / 2;
	}

	int findNeighbour2(vector<vector<int>>& matrix,  int vert)
	{
		for (int i = 0; i < vertCount; i++)
		{
			if (matrix[vert][i] != 0)
			{
				for (int j = 0; j < vertCount; j++)
				{
					if (matrix[i][j] != 0 && matrix[vert][j] == 0 && j != vert)
					{
						return j;
					}
				}
			}
		}
		return 0;
	}

	void glue(vector<vector<int>>& matrix, int& vCount, int& eCount, int vert1, int vert2)
	{
		vCount--;
		for (int i = 0; i < vertCount; i++)
		{
			if (matrix[vert2][i] != 0)
			{
				if (matrix[vert1][i] != 0)
				{
					eCount--;
				}
				matrix[vert1][i] = matrix[vert2][i];
				matrix[i][vert1] = matrix[i][vert2];
				matrix[vert2][i] = 0;
				matrix[i][vert2] = 0;
			}
		}
	}

public:
	void graphInput(ifstream &input)
	{
		input >> vertCount;
		colors.resize(vertCount);
		adjMatrix.resize(vertCount);
		for (int i = 0; i < vertCount; i++)
		{
			adjMatrix[i].resize(vertCount);
			for (int j = 0; j < vertCount; j++)
			{
				input >> adjMatrix[i][j];
				if (adjMatrix[i][j])
				{
					edgCount++;
				}
			}
		}
		edgCount = edgCount / 2;
	}

	void printGraph()
	{
		for (int i = 0; i < vertCount; i++)
		{
			for (int j = 0; j < vertCount; j++)
				cout << adjMatrix[i][j] << ' ';
			cout << '\n';
		}
		cout << '\n';
	}

	void paintGraph()
	{
		int currColor = 1;
		int vert = 0;
		vector<vector<int>> matrix = adjMatrix;;
		int vCount = vertCount;
		int eCount = edgCount;

		while (!isFullGraph(vCount, eCount))
		{
			if (colors[vert] == 0)
			{
				int nbr2;
				colors[vert] = currColor;
				while (nbr2 = findNeighbour2(matrix, vert))
				{
					colors[nbr2] = currColor;
					glue(matrix, vCount, eCount, vert, nbr2);
				}
			}
			currColor++;
			vert++;
		}

		for (int i = 0; i < vertCount; i++)
		{
			if (colors[i] == 0)
			{
				colors[i] = currColor;
				currColor++;
			}
		}
	}

	void printColors()
	{
		for (int i = 0; i < vertCount; i++)
		{
			cout << i << ' ' << colors[i] << endl;
		}
	}

};

int main()
{
	Graph gr;
	ifstream input("input.txt");
	gr.graphInput(input);
	gr.printGraph();
	gr.paintGraph();
	gr.printColors();

	return 0;
}
