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

int vecLargest(vector<int> P)
{
    int largestNum = 0;
    for (int i = 0; i < P.size(); i++)
    {
        if (P[i] > P[largestNum])
            largestNum = i;
    }
    return largestNum;
}

vector<int> myScheduleHelper(vector<int> P, vector<int> D){
  /*
    NOTE: YOU WILL NOT BE TESTED ON THIS FUNCTION. This is an optional helper function that may help with your implementation

    Input:
    vector<int> P, vector<int> D
        vector<int> P: A vector of processing time of job J_1, ... J_n - vector<int>
        vector<int> D: A vector of due dates of each job, J_1, ... J_n - vector<int>

    Return:
      vector<int> sol: A vector containing the schedule after applying Moore's algorithm. Ie. from the write up: [2,3,4,1]
      {4,2,1,3}
      {5,2,3,4}
  */
    int smallestNum = 0;
    vector<int> sol = {};
    int siz = D.size();
    int large = D[vecLargest(D)];
    while (siz != 0)
    {
        for (int i = 0; i < D.size(); i++)
        {
            if (D[i] < D[smallestNum])
                smallestNum = i;
        }
        sol.push_back(smallestNum);
        D[smallestNum] = large + 1;
        siz--;
        smallestNum = 0;
    }
    return sol;
}


vector<tuple<int,int>> myMoore(vector<int> P, vector<int> D){
  /*
    TODO:
    
    Implement Moore's algorithm and return the optimal schedule, along with the end times of the corresponding jobs.

    Input:
    vector<int> P, vector<int> D
        vector<int> P: A vector of processing time of job J_1, ... J_n - vector<int>
        vector<int> D: A vector of due dates of each job, J_1, ... J_n - vector<int>
 
    Return:
      vector<tuple<int,int>> sol: Vector containing optimal schedule of jobs, where in each tuple, 
        the first int refers to the job, and the second int corresponds to the end time of said job.
      Thus each tuple contains the following:
        1. The current job in the optimal order
        2. The end time of this job
      
      Remember, jobs start at 1 (ie. J_1 ... J_N)
      Remember, you start processing your jobs at time 0.
      Hint: Call myScheduleHelper from this function if you need to
 
  */
     vector<int> sched = myScheduleHelper(P, D);

    // Store original processing time and due dates
    vector<int> temp = D;
    vector<int> temp2 = P;
    for (int i = 0; i < D.size(); i++)
    {
        D[i] = temp[sched[i]];
        P[i] = temp2[sched[i]];
    }

    // list of scheduled jobs
    vector<int> S = {};

    // current processing time
    int t = 0;

    // list of delayed jobs
    int j;
    vector<int> extra;


    // process all jobs in queue
    for (int i = 0; i < P.size(); i++)
    {
        S.push_back(i); // add current job into the schedule
        t += P[i];  // add processing time to current processing time
        //cout << t << " - " << i << ";" << D[i] << ":" << P[i] << " sched: " << sched[i] << endl;
        if (t > D[i]) // check if job will be over due date
        {
            vector<int> SP; // vector contains processing time of all jobs in S
            for (int l = 0; l < S.size(); l++)
                SP.push_back(P[S[l]]);
            j = vecLargest(SP); // get job with largest processing time
            //cout << "J:" << j << endl;

            // remove job with largest processing time from S and add to extra
            extra.push_back(S[j]);
            t -= P[j];
            S.erase(S.begin() + j);
        }
    }

    // add all delayed jobs into schedule
    for (int i = 0; i < extra.size(); i++)
        S.push_back(extra[i]);

    vector<tuple<int, int>> sol; // solution vector <job, proc_time>
    tuple<int, int> job;
    t = 0; // reset processing time to 0
    for (int i=0; i < S.size(); i++) {
        t += P[S[i]];
        job = make_tuple(sched[S[i]]+1, t);
        sol.push_back(job);
    }

    return sol;
}

vector<int> myMooreLate(vector<int> P, vector<int> D){
  /*
    TODO:
    
    Apply Moore's algorithm, and then return the late jobs in order

    Input:
    vector<int> P, vector<int> D
        vector<int> P: A vector of processing time of job J_1, ... J_n - vector<int>
        vector<int> D: A vector of due dates of each job, J_1, ... J_n - vector<int>

    Return:
    vector<int>sol: a list of the late jobs in order, after performing Moore's algorithm

    Remember, jobs start at 1 (ie. J_1 ... J_N)
    Hint: Call myScheduleHelper from this function if you need to


  */
    vector<tuple<int,int>> myMooreSchedule;
    myMooreSchedule = myMoore(P, D);
    
    vector<int> sol;
    for (int i = 0; i < myMooreSchedule.size(); i++) {
        int job = get<0>(myMooreSchedule[i])-1;
        int finishTime = get<1>(myMooreSchedule[i]);
        if (D[job] - finishTime < 0) {
            sol.push_back(job+1);
        }
    }

    return sol;
}

/*
int main()
{
    vector<int> P = { 4,3,8,1,7 };
    vector<int> D = { 6,10,3,3,14 };

    //vector<int> P = { 2,2,2 };
    //vector<int> D = { 3,2,1 };

    vector<tuple<int,int>> A;
    A = myMoore(P, D);
    cout << "[";
    for (int i = 0; i < A.size(); i++)
    {
        cout << "(" << get<0>(A[i])-1 << ", " << get<1>(A[i]) << "), ";
    }
    cout << "]" << endl;
}
*/

/*
int main()
{

    //vector<int> P = { 4,3,8,1,7 };
    //vector<int> D = { 6,10,3,3,14 };

    vector<int> P = { 4,1,1,1,1 };
    vector<int> D = { 6,10,3,3,14 };

    vector<int> sol = myMooreLate(P, D);
    for (int i = 0; i < sol.size(); i++)
        cout << sol[i] << endl;
}
*/

/////////////////////////////////////////////////////////
//////////////       QUESTION 2 HERE   //////////////////
/////////////////////////////////////////////////////////
int vecMinimum(vector<int> P)
{
    int min = 0;
    for (int i = 0; i < P.size(); i++)
        if (P[i] < P[min])
            min = i;
    return min;
}

vector<vector<pair<int, int>>> myListScheduling(vector<int> P, int m)
{
    /*
    TODO:

    Implement ListScheduling function under here and return the optimal schedule.

    Input:
    vector<int> P: A vector of processing time of jobs J_1 ,...., J_n - vector<int> 
    int m: number of parallel and identical processors - int 

    return:
    vector<vector<pair<int, int>>> sol: The optimal schedule for each job on each processor.
        The i-th index of the outermost vector must contain the schedule of jobs for the (i+1)-th processor,
        in the form of vector<pair<int, int>>. (Since processors start from 1 and vector indices start from 0).
        Each pair inside this schedule must contain the following:
            1. index of job (job index starts at 1 NOT 0!) - int
            2. completion time of the job on that respective processor - int

            Note:  the start time of job J_j is the completion time of job J_{j−1} on processor Pi.  
                  The start time for the first job on each processor is always 0. 
  
  */
    vector<vector<pair<int, int>>> A(m);
    vector<int> totals;
    int index;
    for (int i = 0; i < m; i++)
        totals.push_back(0);
    for (int i = 0; i < P.size(); i++)
    {
        index = vecMinimum(totals);
        totals[index] += P[i];
        A[index].push_back(make_pair(i + 1, totals[index]));
    }
    return A;
}

bool greaterThan(int i, int j) { return (i > j); }
vector<vector<pair<int, int>>> myLPT(vector<int> P, int m)
{
    /*
    TODO:

    Implement LPT function under here and return the optimal schedule.

    Input:
    vector<int> P: A vector of processing time of jobs J_1 ,...., J_n - vector<int> 
    int m: number of parallel and identical processors - int 

    return:
    vector<vector<pair<int, int>>> sol: The optimal schedule for each job on each processor.
        The i-th index of the outermost vector must contain the schedule of jobs for the (i+1)-th processor,
        in the form of vector<pair<int, int>>. (Since processors start from 1 and vector indices start from 0).
        Each pair inside this schedule must contain the following:
            1. index of job (job index starts at 1 NOT 0!) - int
            2. completion time of the job on that respective processor - int
            
            Note:  the start time of job J_j is the completion time of job J_{j−1} on processor Pi.  
                  The start time for the first job on each processor is always 0. 
  
  */

    vector<int> temp = P;
    vector<int> index;
    sort(P.begin(), P.end(), greaterThan);
    vector<int> used;
    for (int i = 0; i < P.size(); i++)
    {
        for (int j = 0; j < temp.size(); j++)
        {
            if (P[i] == temp[j] && find(used.begin(), used.end(), j) == used.end())
            {
                index.push_back(j);
                used.push_back(j);
            }
        }
    }
    vector<vector<pair<int, int>>> A = myListScheduling(P, m);
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < A[i].size(); j++)
        {
            A[i][j] = make_pair(index[get<0>(A[i][j]) - 1] + 1, get<1>(A[i][j]));
        }
    }
    return A;
}

vector<vector<pair<int, int>>> mySPT(vector<int> P, int m)
{
   /*
    TODO:

    Implement SPT function under here and return the optimal schedule.

    Input:
    vector<int> P: A vector of processing time of jobs J_1 ,...., J_n - vector<int> 
    int m: number of parallel and identical processors - int 

    return:
    vector<vector<pair<int, int>>> sol: The optimal schedule for each job on each processor.
        The i-th index of the outermost vector must contain the schedule of jobs for the (i+1)-th processor,
        in the form of vector<pair<int, int>>. (Since processors start from 1 and vector indices start from 0).
        Each pair inside this schedule must contain the following:
            1. index of job (job index starts at 1 NOT 0!) - int
            2. completion time of the job on that respective processor - int
            
            Note:  the start time of job J_j is the completion time of job J_{j−1} on processor Pi.  
                  The start time for the first job on each processor is always 0. 
  
  */
    vector<int> temp = P;
    vector<int> index;
    sort(P.begin(), P.end());
    vector<int> used;
    for (int i = 0; i < P.size(); i++)
    {
        for (int j = 0; j < temp.size(); j++)
        {
            if (P[i] == temp[j] && find(used.begin(), used.end(), j) == used.end())
            {
                index.push_back(j);
                used.push_back(j);
            }
        }
    }
    vector<vector<pair<int, int>>> A = myListScheduling(P, m);
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < A[i].size(); j++)
        {
            A[i][j] = make_pair(index[get<0>(A[i][j])-1] + 1, get<1>(A[i][j]));
        }
    }
    return A;
}
/*
int main()
{
    vector<int> P = { 3,4,7,3,5,3,9,2 };
    vector<vector<pair<int, int>>> A = mySPT(P, 3);
    cout << "[ ";
    for (int i = 0; i < A.size(); i++)
    {
        cout << "[ ";
        for (int j = 0; j < A[i].size(); j++)
        {
            cout << "(" << get<0>(A[i][j]) << ", " << get<1>(A[i][j]) << ")" << ", ";
        }
        cout << "], " << endl;
    }
    cout << "] ";
}*/
/*
int main()
{
    vector<int> P = { 3,4,7,3,5,3,9,2 };
    vector<vector<pair<int, int>>> A = mySPT(P, 3);
    cout << "[ ";
    for (int i = 0; i < A.size(); i++)
    {
        cout << "[ ";
        for (int j = 0; j < A[i].size(); j++)
        {
            cout << "(" << get<0>(A[i][j]) << ", " << get<1>(A[i][j]) << ")" << ", ";
        }
        cout << "], " << endl;
    }
    cout << "] ";
}*/
// 3,4,5,6pia