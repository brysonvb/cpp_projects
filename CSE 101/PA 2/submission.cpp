#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <utility>
#include <climits>
#include <cmath>
#include <math.h>
#include <float.h>
using namespace std;

// Name: Bryson Bisuna
// PID: A17241294

class Point
{
    public:
    int x, y;
}; // (x, y) represents a point in the Cartesian plane.


///////////////////////////////////////////////////////
//////////////       QUESTION 1 HERE   ////////////////
///////////////////////////////////////////////////////
vector<int> merges(vector<int> B, vector<int> C, int& b)
{
    int index1, index2;
    index1 = index2 = 0;
    vector<int> D;

    while (index1 < B.size() && index2 < C.size())
    {
        if (B[index1] <= C[index2])
        {
            D.push_back(B[index1]);
            index1++;
        }
        else
        {
            D.push_back(C[index2]);
            index2++;
            b += (B.size() - index1);
        }
    }
    while (index1 < B.size())
    {
        D.push_back(B[index1]);
        index1++;
    }
    while (index2 < C.size())
    {
        D.push_back(C[index2]);
        index2++;
    }
    return D;
} 

vector<int> mergeSort(vector<int> A, int& b)
{
    if (A.size() == 1)
        return A;
    int a = A.size() / 2 + (A.size() % 2);
    auto start = A.begin();
    auto end = A.begin() + a;
    vector<int> B(start,end);
    B = mergeSort(B,b);
    auto start2 = A.begin() + a;
    auto end2 = A.end();
    vector<int> C(start2, end2);
    C = mergeSort(C,b);
    vector<int>BC;
    BC = merges(B, C, b);
    return BC;
}

pair<int, vector<int>> myCount(vector<int> L)
{
  /*
    TODO:

    Write an algorithm that solves the counting inversion problem.

    Input:
        vector<int> L: a non-empty array of distinct integers
        
    return:
        pair<int, vector<int>: A pair of the following elements in the exact order:
        0: int: the number of inversions in L 
        1: vector<int>: an array containing the elements of L, but sorted
    
  */
    int b = 0;
    vector<int> sorted = mergeSort(L, b);
    return make_pair(b, sorted);
}

/////////////////////////////////////////////////////////
//////////////       QUESTION 2 HERE   //////////////////
/////////////////////////////////////////////////////////

float distance(Point p1, Point p2)
{
    return sqrt(pow((p1.x - p2.x),2) + pow((p1.y - p2.y),2));
}

float divideClosest(vector<Point> div, int size, float d)
{
    for (int i = 0; i < size; i++)
        for (int j = i + 1; j < size; j++)
            if ((div[j].y - div[i].y) < d)
            {
                if (distance(div[i], div[j]) < d)
                    d = distance(div[i], div[j]);
            }
            else
                break;
    return d;
}

float closestPointHelper(vector<Point> pointListX, vector<Point> pointListY, int siz)
{
    if (siz <= 3)
    {
        float mini = FLT_MAX;
        for (int i = 0; i < siz; i++)
            for (int j = i + 1; j < siz; j++)
                if (distance(pointListX[i], pointListX[j]) < mini)
                    mini = distance(pointListX[i], pointListX[j]);
        return mini;
    }
    int half = siz / 2;
    Point middleX = pointListX[half];
    vector<Point> pointListYSorted1;
    Point temp;
    temp.x = 0;
    temp.y = 0;
    for (int i = 0; i < half; i++)
    {
        pointListYSorted1.push_back(temp);
    }
    vector<Point> pointListYSorted2;
    for (int i = 0; i < siz - half; i++)
    {
        pointListYSorted2.push_back(temp);
    }

    int index1, index2;
    index1 = index2 = 0;
    for (int i = 0; i < siz; i++)
    {
        if ((pointListY[i].x < middleX.x || (pointListY[i].x == middleX.x && pointListY[i].y < middleX.y)) && index1 < half)
        {
            pointListYSorted1[index1] = pointListY[i];
            index1++;
        }
        else
        {
            pointListYSorted2[index2] = pointListY[i];
            index2++;
        }
    }

    float distance1 = closestPointHelper(pointListX, pointListYSorted1, half);
    vector<Point> temporaryVec;
    Point tempor;
    for (int i = half; i < siz; i++)
    {
        tempor.x = pointListX[i].x;
        tempor.y = pointListX[i].y;
        temporaryVec.push_back(tempor);
    }
    float distance2 = closestPointHelper(temporaryVec, pointListYSorted2, siz - half);
    float dist;
    if (distance1 < distance2)
        dist = distance1;
    else
        dist = distance2;

    vector<Point> closePoints;
    for (int i = 0; i < siz; i++)
        if (abs(pointListY[i].x - middleX.x) < dist)
            closePoints.push_back(pointListY[i]);

    return divideClosest(closePoints, closePoints.size(), dist);
}

int compareX(const void* a, const void* b)
{
    Point* p1 = (Point*)a, * p2 = (Point*)b;
    return (p1->x != p2->x) ? (p1->x - p2->x) : (p1->y - p2->y);
}

int compareY(const void* a, const void* b)
{
    Point* p1 = (Point*)a, * p2 = (Point*)b;
    return (p1->y != p2->y) ? (p1->y - p2->y) : (p1->x - p2->x);
}

float closestPoint(vector<Point> pointList, int siz)
{
    vector<Point> pointListX;
    vector<Point> pointListY;
    for (int i = 0; i < siz; i++)
    {
        pointListX.push_back(pointList[i]);
        pointListY.push_back(pointList[i]);
    }

    qsort(&pointListX[0], siz, sizeof(Point), compareX);
    qsort(&pointListY[0], siz, sizeof(Point), compareY);
    /*
    for (int i = 0; i < pointListX.size(); i++)
    {
        cout << "p1: (" << pointListX[i].x << ", " << pointListX[i].y << "), p2: (" << pointListY[i].x << ", " << pointListY[i].y << ")";
    }*/

    return closestPointHelper(pointListX, pointListY, siz);
}

int myMinDistance(vector<Point> P)
{
  /*
    TODO:

    Write an algorithm that solves the closest pair of points problem.

    Input:
        P: an array of Points. Points contain the fields x and y, with (x, y) 
        representing a point in the Cartesian plane.

    return:
        An int representing the square of the minimum distance between two of the given points.
        */
    
    float close = closestPoint(P, P.size());
    int closeSquare = round(close * close);
    return (closeSquare);
    
} 
/*
int main()
{
    vector<Point> P;
    Point temp;
    temp.x = 0;
    temp.y = 0;
    P.push_back(temp);
    temp.x = 1;
    temp.y = 1;
    P.push_back(temp);
    temp.x = 1;
    temp.y = 4;
    P.push_back(temp);
    temp.x = 2;
    temp.y = 2;
    P.push_back(temp);
    cout << myMinDistance(P);
}*/
/*
int main()
{
    vector<int> L = { 6,1,-4,10,2,7 };
    pair<int, vector<int>> myC = myCount(L);
    int b = myC.first;
    vector<int> sorted = myC.second;

    cout << "(" << b << ", [";
    for (int i = 0; i < sorted.size(); i++)
    {
        cout << sorted[i] << ", ";
    }
    cout << "])";
    cout << endl;
}

*/