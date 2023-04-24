#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include "SuffixArray.h"
using namespace std;

/**
 * Implement suffix_array() correctly
 */
vector<unsigned int> suffix_array(const string & s) {
    string suffArray[s.length()];
    for (int i = 0; i < s.length(); i++)
        suffArray[i] = s.substr(i,s.length());
    string newSuffArray[s.length()];
    for (int i = 0; i < s.length(); i++)
        newSuffArray[i] = suffArray[i];
    std::sort(newSuffArray, newSuffArray+s.length());
    vector<unsigned int> nums;
    for (unsigned int i = 0; i < s.length(); i++)
    {
        for (unsigned int j = 0; j < s.length(); j++)
        {
            if (newSuffArray[i] == suffArray[j])
            {
                nums.push_back(j);
                break;
            }
        }
    }
    return nums;
}
