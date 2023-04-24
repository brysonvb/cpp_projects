#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <utility>
#include <climits>
#include <cmath>
using namespace std;

// Name:
// PID:

///////////////////////////////////////////////////////
//////////////       QUESTION 1 HERE   ////////////////
///////////////////////////////////////////////////////

vector<int> smallestVert(vector<vector<int>> graph, vector<int> usedVert)
{
    int minVert = INT_MAX;
    vector<int> rowCol;
    rowCol.push_back(0);
    rowCol.push_back(0);
    for (int index = 0; index < graph.size(); index++)
    {
        for (int j = 0; j < graph.size(); j++)
        {
            if (graph[index][j] != 0)
            {
                if (graph[index][j] < minVert)
                {
                    if (index != j)
                    {
                        if (!(find(usedVert.begin(), usedVert.end(), index) == usedVert.end() && find(usedVert.begin(), usedVert.end(), j) == usedVert.end()))
                        {
                            if (!(find(usedVert.begin(), usedVert.end(), index) != usedVert.end() && find(usedVert.begin(), usedVert.end(), j) != usedVert.end()))
                            {
                                minVert = graph[index][j];
                                rowCol[0] = index;
                                rowCol[1] = j;
                            }
                        }
                    }
                }
            }
        }
    }
    return rowCol;
}

vector<vector<int>> myPrim(vector<vector<int>> graph, int startV)
{
  /*
    TODO:

    Write an algorithm that runs Prim's algorithm on a graph

    Input:
        vector<vector<int>> graph: The adjacency matrix representing the graph
        int startV: the vertex that you will start Prim's algorithm at

    return:
        vector<vector<int>>: The adjacency matrix of the MST found by running Prim's algorithm

  */
    vector<int> usedVert;
    usedVert.push_back(startV);

    vector<vector<int>> MST(graph.size(), vector<int>(graph.size()));

    vector<int> vert;
    int row, col;
    int numEdges = 0;
    while (numEdges < graph.size() - 1)
    {
        vert = smallestVert(graph, usedVert);
        row = vert[0];
        col = vert[1];
        if (find(usedVert.begin(), usedVert.end(), row) == usedVert.end())
            usedVert.push_back(row);
        if (find(usedVert.begin(), usedVert.end(), col) == usedVert.end())
            usedVert.push_back(col);
        MST[row][col] = graph[row][col];
        MST[col][row] = graph[row][col];
        numEdges++;
    }

    return MST;
}

/*
int main()
{
    //vector<vector<int>> graph = { { 0,2,0,6,0}, {2,0,3,8,5}, {0,3,0,0,7},{6,8,0,0,9},{0,5,7,9,0} };
    vector<vector<int>> graph = { {0,4,5,2,0,0}, {4,0,0,4,3,0}, {5,0,0,4,0,6}, {2,4,4,0,3,5}, {0,3,0,3,0,4},{0,0,6,5,4,0} };
    vector<vector<int>> MST = myPrim(graph, 0);

    for (int i = 0; i < graph.size(); i++)
    {
        for (int j = 0; j < graph.size(); j++)
        {
            cout << MST[i][j] << " ";
        }
        cout << endl;
    }
}
*/

int smallestEdge(vector<int> phase, vector<int> usedVert, vector<int> vertices)
{
    int min = INT_MAX;
    int index;

    for (int i = 0; i < vertices.size(); i++)
        if (find(usedVert.begin(), usedVert.end(), i) == usedVert.end() && phase[i] <= min)
        {
            min = phase[i];
            index = i;
        }
    return index;
}


/////////////////////////////////////////////////////////
//////////////       QUESTION 2 HERE   //////////////////
/////////////////////////////////////////////////////////
tuple<vector<vector<int>>, vector<int>> myDijkstra(vector<int> vertices, vector<tuple<int, int, int>> edges)
{
  /*
    TODO:

    Write an algorithm that runs Dijkstra's Algorithm on a Directed Graph to solve the Single Source Shortest Path Problem.
    The source vertex is always vertex 0.

    Input:
        vector<int> vertices: Vector of the first n non-negative integers representing the n vertices of G.
        vector<tuple<int, int, int>> edges: A vector containing edges in G in the form of tuples where each tuple is of the form [i, j, c(i, j)],
            corresponding to the directed edge from vertex i to vertex j with weight c(i, j).


    return:
        tuple<vector<vector<int>>, vector<int>> sol: A tuple of the following elements in the exact order:
            0:  vector<vector<int>> shortestPath: Vector of vectors containing the shortest paths from source vertex to vertex i at index i.
            1:  vector<int> shortestPathLength: A vector that contains the shortest distance from source vertex to vertex i at index i.

    Some Helper functions that might help you modularize the code:
        - vector<int> myInitialize(int n, int s) : calculates Initialize (as explained in class) from a given source node (int s),
              given the number of nodes (int n).

        - vector<int> myRelax(vector<int> distance, vector<tuple<int, int, int>> edges, int u) : Gives an updated distance vector
              after `Relax`-ing (as explained in class) all edges going out from u.

    Note: These functions are recommended however we won't be grading your implementations of the
          above stated functions

  */

    vector<vector<int>> shortestPath;
    vector<int> empty = { };
    for (int i = 0; i < vertices.size(); i++)
        shortestPath.push_back(empty);

    shortestPath[0].push_back(0);

    vector<vector<int>> adjacency(vertices.size(), vector<int>(vertices.size()));
    int row, col;

    for (int i = 0; i < edges.size(); i++)
    {
        row = get<0>(edges[i]);
        col = get<1>(edges[i]);
        adjacency[row][col] = get<2>(edges[i]);
    }

    vector<int> phase;
    vector<int> usedVert;

    phase.push_back(0);
    for (int i = 0; i < vertices.size()-1; i++)
    {
        phase.push_back(INT_MAX);
    }

    int smallestIndex;
    for (int i = 0; i < phase.size() - 1; i++)
    {
        smallestIndex = smallestEdge(phase, usedVert, vertices);

        usedVert.push_back(smallestIndex);

        for (int j = 0; j < vertices.size(); j++)
        {
                if (find(usedVert.begin(), usedVert.end(), j) == usedVert.end() && adjacency[smallestIndex][j] != 0 && phase[smallestIndex] != INT_MAX && phase[smallestIndex] + adjacency[smallestIndex][j] < phase[j])
                {
                    phase[j] = phase[smallestIndex] + adjacency[smallestIndex][j];
                    shortestPath[j] = shortestPath[smallestIndex];
                    shortestPath[j].push_back(j);
                }
        }
    }


    return make_tuple(shortestPath, phase);
}

/*
int main()
{
    vector<int> vertices = { 0,1,2,3,4,5,6 };
    vector<tuple<int,int,int>> edges = { 
        {0,1,9},
        {0,2,3},
        {0,3,2},
        {2,1,2},
        {3,1,9},
        {3,4,8},
        {3,5,4},
        {3,6,5},
        {4,0,5},
        {4,2,8},
        {5,6,12},
        {6,2,8} };

    vector<vector<int>> shortestPath;
    vector<int> shortestPathLength;

    auto tup = myDijkstra(vertices, edges);
    shortestPath = get<0>(tup);
    shortestPathLength = get<1>(tup);

    for (int i = 0; i < shortestPathLength.size(); i++)
        cout << shortestPathLength[i] << " ";
    cout << endl;
}*/