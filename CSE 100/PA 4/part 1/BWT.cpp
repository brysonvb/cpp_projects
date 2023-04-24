#include <string>
#include <algorithm>
#include "BWT.h"
using namespace std;

/**
 * Implement bwt() correctly
 */
string bwt(const string & s) {
    string strs[s.length()];
    int increment = 0;
    strs[0] = s;
    string temp;
    for (int i = 1; i < s.length(); i++)
    {
        temp = strs[i-1];
        rotate(temp.begin(),temp.begin()+1,temp.end());
        strs[i] = temp;
    }
    std::sort(strs, strs+s.length());
    string finalStr = "";
    for (int i = 0; i < s.length(); i++)
        finalStr += (strs[i])[s.length()-1];
    return finalStr;
}
