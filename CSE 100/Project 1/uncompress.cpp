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

    FancyInputStream inputComp(argv[1]);
    FancyOutputStream origFile(argv[2]);
    
    if (!inputComp.good())
    {
        cerr << "ERROR: " << "File not found: " << argv[1] << endl;
        return 1;
    }
    
    if (!origFile.good())
    {
        cerr << "ERROR: " << "File not found: " << argv[2] << endl;
        return 1;
    }
      
    int empty;
    empty = inputComp.filesize();

    unsigned int fs = 0;

    if (empty > 0) {
        // initialize counters to 0
        vector<int> freqs = vector<int>(256, 0);
  
        HCTree huffmanTree;
        
        // read header from compresed file
        fs = inputComp.read_int();
        for (int i=0; i < 256; i++)
        {
            unsigned int a = 0;
            unsigned int inBit = 0;
            for (int j=24; j>0; j--) {
                inBit = inputComp.read_bit();
                a = a << 1;
                a = a | inBit;
            }
            freqs[i] = a;
        }
            
        // build encoding tree
        huffmanTree.build(freqs);

        // decode the file
        int readByte;
        while (inputComp.good()) {
            readByte = huffmanTree.decode(inputComp);
            if (readByte != -1 && fs > 0)
            {
                origFile.write_byte((unsigned char)readByte);
                fs--;
            }
        }
    }
    origFile.flush();
}
