#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <utility>
#include <climits>
#include <cmath>
#include <numeric>
using namespace std;
#define inf 9999

// Name:
// PID:

///////////////////////////////////////////////////////
//////////////       QUESTION 1 HERE   ////////////////
///////////////////////////////////////////////////////
vector<vector<int>> mySavings(vector<vector<int>>S){
    /*
      TODO:

      Write an algorithm that calculates the Savings Heuristic Matrix from the shortest path graph.

      Input:
        vector<vector<int>> S: the shortest path matrix

      Return:
        vector<vector<int>>: the Savings Heuristic Matrix

    */
    vector<vector<int>> savings = S;
    for (int i = 0; i < savings.size(); i++)
    {
        for (int j = 0; j < savings.size(); j++)
        {
            if ((i == j) || (i > j))
                savings[i][j] = 0;
            else
                savings[i][j] = S[0][i] + S[0][j] - S[i][j];
        }
    }
    return savings;
}


tuple<int, int> largestSavings(vector<vector<int>> matrix)
{
    int large = matrix[0][0];
    tuple<int, int> a;
    for (int i = 0; i < matrix.size(); i++)
        for (int j = 0; j < matrix.size(); j++)
            if (matrix[i][j] > large)
            {
                large = matrix[i][j];
                a = make_tuple(i,j);
            }
    return a;
}


int getSavings(vector<vector<int>> S, tuple<int, int> coord)
{
    int x = get<0>(coord);
    int y = get<1>(coord);
    return S[x][y];
}


int getPathCost(vector<vector<int>> S, int start, int end)
{
    return S[start][end];
}


int findNode(vector<int> nodes, int target)
// return -1 if node is not active (not found)
// return location of node if found
{
    int found = -1;
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i] == target)
            return i;
    }
    return found;
}


int getActivePathCost(vector<int> S)
{
    int cost = 0;
    for (auto a: S) cost += a;
    return cost;
}

int getLowestCost(vector<int> S, vector<int> Q)
{
    int lowest = 1000;
    for (int i = 0; i < S.size(); i++)
    {
      if (S[i] == 0)
      {
        int temp = Q[i];
        if (temp < lowest)
            lowest = temp;
      }
    }
    return lowest;
}

vector<int> getFinalPath(vector<int> S)
{
    vector<int> finalPath;
    for (int i = 0; i < S.size(); i++)
        if (S[i] > 0)
            finalPath.push_back(i);
    return finalPath;
}

void printMatrix(vector<vector<int>> S)
{
    for (int i = 0; i < S.size(); i++)
    {
        for (int j = 0; j < S.size(); j++) {
            printf("%2d ", S[i][j]);
            //cout << savings[i][j] << " ";
        }
        cout << endl;
    }
    return;
}


int processNodes(vector<int> S)
{
    int active = 0;
    for (auto a: S)
        if (a == -1)
            continue;
        else
            active++;
    return active;
}


vector<tuple<vector<int>, int, int>> myCVRP(vector<vector<int>> S, vector<int> Q) {
    /*
      TODO:

      Write an algorithm that runs the CVRP algorithm from the shortest path graph.

      Input:
        vector<vector<int>> S: the shortest path matrix
        vector<int> Q: Q[0] is the total capacity and for j >= 1, Q[j] is the demand of vertex j
          (i.e.  A -> 1, B -> 2, C -> 3, and so on).

      Return:
        vector<tuple<vector<int>, int, int>>: a vector containing information of each CVRP tour. The tuple
          contains a vector of the path, the total capacity for this path, and the total length of this path.
          Thus, if there are 3 paths:
            O - A - E - O (capacity 70, length 8)
            O - C - D - O (capacity 30, length 10)
            O - B - O  (capacity 10, length 4)
          Within the first tuple, it will contain
              1. a vector [1,5]
            2. the capacity 70
            3. the length 8
          This continues for the 2 other paths, and all of these tuples are stored in the outer vector.

     NOTE: Recall, vertices start at 1, not 0. Ie. A -> 1, B -> 2, C -> 3, and so on.
     NOTE: The order of the tours in this vector does not matter and you will receive full points as long
        as all the tours are present in this vector.

     Hint: You may want to call mySavings from this function.
    */


    int Capacity = Q[0];   // Transport Capacity

    vector<tuple<vector<int>, int, int>> result;

    vector<int> activeNodes;
    vector<int> activePath;

    // initialize all nodes that need to be visited
    for (auto vertex : Q)
        activeNodes.push_back(vertex);


    activeNodes[0] = -1;

    vector<vector<int>> Savings = mySavings(S); // savings matrix

//    cout << "Shortest Paths" << endl;
//    printMatrix(S);
//    cout << "Test" << endl;
//    printMatrix(Savings);

    while(processNodes(activeNodes) > 0)
    //while(getSavings(Savings, largestSavings(Savings)) > 0)
    {
        // if this is the last node, get roundtrip cost and path cost, add to result
//        cout << "pnode: " << processNodes(activeNodes) << endl;
        if (processNodes(activeNodes) == 1)
        {
            // only 1 node left, round trip
            int lastNode = 0;
            for (lastNode = 0; lastNode < activeNodes.size(); lastNode++)
                if (activeNodes[lastNode] != -1) {
                    break;
                }
            vector<int> v = {lastNode};
            int weight = Q[lastNode];
            int cost = getPathCost(S, 0, lastNode)*2;
            result.push_back(make_tuple(v, weight, cost));
            activeNodes[lastNode] = -1;
            return result;
        }

        // reset path
        activePath.clear();
        for (auto vertex : Q)
            activePath.push_back(0);

        // more than 1 node remaining, need to get tours
        int trasportCapacity = 0; // allocate for new transport

        // while tour capacity is less than Capacity
        //while ((trasportCapacity < Capacity) && (processNodes(activeNodes) > 1))
        while ((trasportCapacity < Capacity) &&
                //((Capacity - trasportCapacity) > getLowestCost(activePath, Q)) &&
                (getSavings(Savings, largestSavings(Savings)) > 0) &&
                (trasportCapacity != Capacity))
        {
//            cout << "lowest: " << getLowestCost(activePath, Q) << endl;
            // get node with largest savings
            tuple<int, int> largestNode = largestSavings(Savings);

            // get cost of each node
            int node1 = get<0>(largestNode);
            int node2 = get<1>(largestNode);
            int nodesCost = Q[node1] + Q[node2];
//            cout << "n1: " << node1 << ", n2: " << node2 << " cost: " << nodesCost;
//            cout << " active: " << getActivePathCost(activePath) << "transport: " << trasportCapacity << endl ;
            bool node1Active = false;
            bool node2Active = false;
            // try to add the cost to the current tour to see if possible to add
            if (activePath[node1] == 0)
                activePath[node1] = Q[node1];
            else
                node1Active = true;
            if (activePath[node2] == 0)
                activePath[node2] = Q[node2];
            else
                node2Active = true;
            trasportCapacity = getActivePathCost(activePath);
            if (trasportCapacity > Capacity)
            {
                // backout node addition
                if (!node1Active)
                    activePath[node1] = 0;
                if (!node2Active)
                    activePath[node2] = 0;
                if (node1Active || node2Active)
                {
                    trasportCapacity = getActivePathCost(activePath);
                    Savings[node1][node2] = 0;
                }
                if (trasportCapacity == nodesCost || trasportCapacity == 0)
                    Savings[node1][node2] = 0;
            }
            else
            {
                Savings[node1][node2] = 0;
            }
        }
        // readout the path and add to result
        if (getActivePathCost(activePath) > 0 && getActivePathCost(activePath) <= Capacity)
        {
            vector<int> v = getFinalPath(activePath);
            // remove from active nodes
            for (auto a: v)
                activeNodes[a] = -1;
            int weight = getActivePathCost(activePath);
            int cost = getPathCost(S, 0, v[0]);
            int i;
            for(i = 0; i < v.size()-1; i++)
                cost += getPathCost(S, v[i], v[i+1]);
            cost += getPathCost(S, 0, v[i]);
            //cout << "weight: " << weight << " cost:" << cost;
            result.push_back(make_tuple(v, weight, cost));

            // clear used nodes
            for(i = 0; i < v.size(); i++)
                for(int j = 0; j < Savings[i].size(); j++)
                {
                    Savings[v[i]][j] = 0;
                    Savings[j][v[i]] = 0;
                }
            //printMatrix(Savings);
        }
    }
    return result;
}


int myRoundTripLength (vector<vector<int>> S, vector<int>Q) {
    /*
      TODO:

      Write an algorithm that calculates the length of the Round Trip

      Input:
        vector<vector<int>> S: the shortest path matrix
        vector<int> Q: Q[0] is the total capacity and for j >= 1, Q[j] is the demand of vertex j
          (i.e.  A -> 1, B -> 2, C -> 3, and so on).

      Return:
        int roundTripLength: sum of the lengths of all roundtrips before CVRP

      Hint: You may want to call myCVRP from this function
    */
    int sumLength = 0;
    for (int i = 0; i < S.size(); i++)
    {
        sumLength += S[0][i] * 2;
    }
    return sumLength;
}


int mySavingsLength (vector<vector<int>> S, vector<int>Q) {
    /*
      TODO:

      Write an algorithm that calculates the length of the Savings Heuristic

      Input:
        vector<vector<int>> S: the shortest path matrix
        vector<int> Q: Q[0] is the total capacity and for j >= 1, Q[j] is the demand of vertex j
          (i.e.  A -> 1, B -> 2, C -> 3, and so on).

      Return:
        int savingsLength: sum of the lengths of all tours after CVRP

      Hint: You may want to call myCVRP from this function
    */
    vector<tuple<vector<int>, int, int>> CVRP = myCVRP(S,Q);
    int totalLength = 0;
    for (int i=0; i < CVRP.size(); i++) {
        totalLength += get<2>(CVRP[i]);
    }
    int roundTripLength = myRoundTripLength(S, Q);

    return totalLength;
}


//int main()
//{
//    vector<vector<int>> shortest = {
//            { 0, 2, 7, 12,  5, 8, 10},
//            { 2, 0, 5, 10,  3, 6,  8},
//            { 7, 5, 0,  6,  8, 2,  4},
//            {12,10, 6,  0, 12, 4,  5},
//            { 5, 3, 8, 12,  0, 8, 10},
//            { 8, 6, 2,  4,  8, 0, 2},
//            {10, 8, 4,  5, 10, 2, 0}
//    };
//    //                      A  B  C  D  E  F
//    vector<int> cost = {10, 3, 4, 2, 5, 6, 3};

//    vector<vector<int>> shortest = {
//        {0,7,9,10,8,5,6,7,9},
//        {7,0,4,6,4,3,2,5,5},
//        {9,4,0,6,5,4,3,6,6},
//        {10,6,6,0,5,5,4,7,6},
//        {8,4,5,5,0,3,2,5,1},
//        {5,3,4,5,3,0,1,2,4},
//        {6,2,3,4,2,1,0,3,3},
//        {7,5,6,7,5,2,3,0,5},
//        {9,5,6,6,1,4,3,5,0} };
//
//    vector<int> cost = {100, 5, 15, 10, 40, 60, 45, 55, 30};



//     vector<vector<int>> shortest = {
//        {0,3,2,4,2,3},
//        {3,0,5,7,5,2},
//        {2,5,0,6,4,5},
//        {4,7,6,0,4,7},
//        {2,5,4,4,0,4},
//        {3,2,5,7,4,0}};
//
//    vector<int> cost = {90, 30, 10, 20, 10, 40};

    /*
    vector<vector<int>> savings = mySavings(shortest);
    printMatrix(savings);

    tuple<int, int> temp;
    temp = largestSavings(savings);
    cout << "Savings: " << get<0>(temp) << ", " << get<1>(temp) << endl;
    */
//
//    vector<tuple<vector<int>, int, int>> result = myCVRP(shortest, cost);
//
//    cout << "Processing" << endl;
//    for (int i = 0; i < result.size(); i++) {
//        vector<int> y = get<0>(result[i]);
//        cout << "[";
//        for (auto a: y) cout << a << ", ";
//        cout << "], ";
//        cout << get<1>(result[i]) << ", " << get<2>(result[i]) << endl;
//    }
//
//    cout << "Savings Length: " << mySavingsLength(shortest, cost) << endl;
//}


/////////////////////////////////////////////////////////
//////////////       QUESTION 2 HERE   //////////////////
/////////////////////////////////////////////////////////

bool findValue(vector<int> S, int target)
{
    for (auto a : S)
        if (a == target)
            return true;
    return false;
}

tuple<vector<int>, vector<int>, int> mySimplexLP(vector<vector<int>> A, vector<int> B, vector<int> C) {
/*
    TODO:

    Implement the Simplex algorithm.

    Input:
        vector<vector<int>> A: an m x n array of integers
        vector<int> B: an m-item list of integers
        vector<int> C: an n-item list of integers

    return:
        vector<int> optimal: array of length n with optimal values for x1, ..., xn
        vector<int> slack: array of length m with slack variable values for s1, ..., sm
        int value: objective value of the optimal solution
  */
    /*
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < A.size(); j++)
            cout << A[i][j] << " ";
        cout << "| " << B[i] << endl;
    }
    for (int i = 0; i < C.size(); i++)
        cout << -C[i] << " ";
        */
    vector<vector<float>> slackA(A.size()+1, vector<float>(A[0].size()+A.size()));

    vector<int> origB = B;


    for (int i = 0; i < A.size(); i++)
        for (int j = 0; j < A[0].size(); j++)
            slackA[i][j] = A[i][j];


    for (int i = 0; i < A.size(); i++)
    {
        for (int j = A[0].size(); j < A[0].size() + A.size(); j++)
        {
            if (i == (j - A[0].size()))
                slackA[i][j] = 1;
            else
                slackA[i][j] = 0;
        }
    }

    for (int i = 0; i < C.size(); i++)
        slackA[A.size()][i] = (C[i] > 0) ? -C[i] : C[i];

    bool negative = true;
    B.push_back(0);

    while (negative)
    {
        int largestC = 0;
        int largestB = 0;

        for (int i = 0; i < slackA[0].size(); i++)
            if (slackA[A.size()][i] < slackA[A.size()][largestC])
                largestC = i;

        while ((B[largestB] < 0 && slackA[largestB][largestC] > 0) ||
               (B[largestB] > 0 && slackA[largestB][largestC] < 0) ||
               (slackA[largestB][largestC] == 0))
            largestB++;

        for (int i = 0; i < B.size()-1; i++)
            if (slackA[i][largestC] != 0)
                if (((B[i] / slackA[i][largestC]) < (B[largestB] / slackA[largestB][largestC])) &&
                   ((B[i] / slackA[i][largestC]) > 0))
                    largestB = i;

        for (int i = 0; i < slackA.size(); i++)
        {
            if (i != largestB)
            {
                float num = -slackA[i][largestC] / slackA[largestB][largestC];
                for (int j = 0; j < slackA[i].size(); j++)
                    slackA[i][j] += (slackA[largestB][j] * num);
                B[i] += (num * B[largestB]);
            }
        }

        negative = false;
        for (int i = 0; i < slackA[0].size(); i++)
            if (slackA[A.size()][i] < 0)
                negative = true;
    }

    vector<int> soln(A[0].size());
    for (int i = 0; i < soln.size(); i++)
        soln[i] = -1;

    vector<int> mark;
    int check;
    for (int i = 0; i < A[0].size(); i++)
    {
        check = -1;
        for (int j = 0; j < slackA.size(); j++)
        {
            if (slackA[j][i] != 0)
            {
                if (check == -1)
                    check = j;
                else
                    break;
            }
            if ((j == A[0].size() - 1) && (check != -1))
            {
                soln[i] = B[check] / slackA[check][i];
            }
        }
    }

    vector<int> Btemp = origB;
    vector<vector<int>> Atemp = A;
    vector<int> Ctemp = C;
    for (int i = 0; i < Ctemp.size(); i++)
        Ctemp[i] = -Ctemp[i];
    Atemp.push_back(Ctemp);
    Btemp.push_back(0);
    vector<float> temp;

    int currRow;
    vector<int> colUsed;
    int numIterations = 0;
    vector<int> usedRows;

    while (findValue(soln, -1) && (numIterations < soln.size()*2))
    //while (findValue(soln, -1))
    {
        numIterations++;
        for (int index = 0; index < Atemp[0].size(); index++)
        {
            if (!findValue(colUsed, index))
            {
                if (soln[index] != -1)
                    colUsed.push_back(index);
                else
                    continue;
                for (int i = 0; i < Atemp.size(); i++)
                {
                    if (soln[index] != -1)
                    {
                        if (Atemp[i][index] != 0)
                        {
                            Btemp[i] += -Atemp[i][index] * soln[index];
                            Atemp[i][index] = 0;
                        }
                    } else
                        break;
                }
            }
        }

        int repeat;
        int ind;
        for (int i = 0; i < A.size(); i++)
        {
            if (!findValue(usedRows,i))
            {
                repeat = -1;
                for (int j = 0; j < Atemp[0].size(); j++)
                {
                    if (Atemp[i][j] != 0)
                        if (repeat == -1)
                        {
                            repeat = Atemp[i][j];
                            ind = j;
                        }
                        else
                            break;
                    if ((j == (A[0].size() - 1)) && repeat != -1)
                        soln[ind] = Btemp[i] / repeat;
                }
                if (repeat == -1)
                    usedRows.push_back(i);
                if (findValue(soln, -1))
                    break;
            }
            if (findValue(soln, -1))
                break;
        }
    }


    int numb;
    vector<int> slack;
    for (int i = 0; i < A.size(); i++)
    {
        numb = origB[i];
        for (int j = 0; j < A[0].size(); j++)
            numb -= A[i][j] * soln[j];
        slack.push_back(numb);
    }
    int total = B[B.size() - 1];

    return make_tuple(soln, slack, total);
}

/*
int main()
{
    vector<vector<int>> A = { {2,1},{1,1},{1,0} };
    vector<int> B = { 100,80,40 };
    vector<int> C = { 3,2 };
    auto a = mySimplexLP(A, B, C);
}
*/




/*
int main()
{
    vector<vector<int>> A = { {1,1},{2,1} };
    vector<int> B = { 4,5 };
    vector<int> C = { 3,4 };
    auto a = mySimplexLP(A, B, C);
}
*/

/*
int main()
{
    vector<vector<int>> A = { {2,1},{2,3},{3,1} };
    vector<int> B = { 18,42,24 };
    vector<int> C = { 3,2 };
    auto a = mySimplexLP(A, B, C);
}
*/

/*
int main()
{
    vector<vector<int>> A = { {1,1},{2,1} };
    vector<int> B = { 4,5 };
    vector<int> C = { 3,4 };
    auto a = mySimplexLP(A, B, C);
}
*/
/*
int main()
{
    vector<vector<int>> A = { {2,1,0},{0,2,1},{1,0,2} };
    vector<int> B = { 10,20,30 };
    vector<int> C = { 3,4,5 };
    auto a = mySimplexLP(A, B, C);
}
*/