#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ofstream file = ofstream("zero", ios::binary);
    for(int i=0;i < 100; i++) {
        file.put(0);
    }
    file.close();
    return 0;
}
