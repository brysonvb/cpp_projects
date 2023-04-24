#include "BloomFilter.h"
#include "HashFunctions.h"

/**
 * Implement insert() correctly
 */
void BloomFilter::insert(const string & s) {
    unsigned int hashes[5];
    for (unsigned int i = 0; i < K; i++)
        hashes[i] = hash_functions[i](s) % M;

    for (unsigned int i = 0; i < K; i++)
        bits[hashes[i]] = true;
}

/**
 * Implement find() correctly
 */
bool BloomFilter::find(const string & s) {
    unsigned int hashes[5];
    for (unsigned int i = 0; i < K; i++)
        hashes[i] = hash_functions[i](s) % M;
    
    for (unsigned int i = 0; i < K; i++)
        if (bits[hashes[i]] == false)
            return false;
    return true;
}
