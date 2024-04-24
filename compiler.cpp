#include <iostream>
#include <fstream>
#include <string>

#include "RISCV32I_ISA.h"

using namespace std;

int main(int argc, char** argv) {

    if(argc != 2) {
        cout << "Fuck off!" << endl;
        return -1;
    }

    string line;

    ifstream fp(argv[1]);
    if(fp.is_open()) {
        while(getline(fp, line)) {
            cout << line << endl;
        }
        fp.close();
    }

    cout << "------------" << endl <<"End of file! Bye-bye!" << endl;

    return 0;
}