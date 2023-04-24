#include <iostream>
#include "HCTree.hpp"
#include "Helper.hpp"
using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cerr << "ERROR: Incorrect parameters" << endl;
        cerr << "USAGE: " << argv[0] << " <original_file>" << " <compressed file>" << endl;
        return 1;
    }

    
    FancyInputStream inputFile(argv[1]);
    FancyOutputStream outputFile(argv[2]);
    
    if (!inputFile.good())
    {
        cerr << "ERROR: " << "File not found: " << argv[1] << endl;
        return 1;
    }
    
    if (!outputFile.good())
    {
        cerr << "ERROR: " << "File not found: " << argv[2] << endl;
        return 1;
    }
    
    // initialize counters to 0
    vector<int> freqs = vector<int>(256, 0);
  
    unsigned char ch;
    
    // check empty file case
    int empty;

    empty = inputFile.filesize();
    unsigned int fs = 0;

    if (empty > 0) {
        // count frequency of each char in inputfile
        while (inputFile.good())
        {
            ch = inputFile.read_byte();
            if (inputFile.good())
            {
                freqs[ch] += 1;
                fs++;
            }
        }

        HCTree huffmanTree;

        // build huffmantree using frequency table
        huffmanTree.build(freqs);
            
        // write huffman frequency header into output file
        outputFile.write_int(fs); // write filesize
        for (auto sym : freqs) {
            unsigned int mask = 0x800000;
            unsigned int a = sym;
            unsigned int outBit;
            unsigned int test = 0;
            for (int i=24; i>0; i--) {
                outBit = (a & mask);
                if (outBit > 0)
                    outBit = 1;
                else 
                    outBit = 0;
                a = a << 1;
                test = (test | outBit);
                if (i>1)
                    test = test << 1;
                outputFile.write_bit(outBit);
            }
        }

        // encode content into output file
        inputFile.reset();

        ch = inputFile.read_byte();
        while (inputFile.good())
        {      
            huffmanTree.encode(ch, outputFile);
            ch = inputFile.read_byte();
        }
    }
    outputFile.flush();
    freqs.clear();
}
