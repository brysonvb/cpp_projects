#include <limits>
#include "CountMinSketch.h"
#include "HashFunctions.h"

/**
 * Implement increment() correctly
 */
void CountMinSketch::increment(const string & s) {
    unsigned int hashes[5];
    for (unsigned int i = 0; i < K; i++)
        hashes[i] = hash_functions[i](s) % M;

    for (unsigned int i = 0; i < K; i++)
        count[i][hashes[i]] += 1;
}

/**
 * Implement find() correctly
 */
unsigned int CountMinSketch::find(const string & s) {
    
    unsigned int hashes[5];
    for (unsigned int i = 0; i < K; i++)
        hashes[i] = hash_functions[i](s) % M;
        
    unsigned int smallestNum = count[0][hashes[0]];
    for (unsigned int i = 0; i < K; i++)
        if (smallestNum > count[i][hashes[i]])
            smallestNum = count[i][hashes[i]];

    return smallestNum;
}
