#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "RISCV32I_ISA.h"
#include "Tokenizer.h"

using namespace std;

int main(int argc, char** argv) {

    if(argc != 2) {
        cout << "Fuck off!" << endl;
        return -1;
    }

    string line;
    std::vector<string> lines;

    ifstream fp(argv[1]);
    if(fp.is_open()) {
        while(getline(fp, line)) {
            cout << line << endl;
            lines.push_back(line);
        }
        cout << endl;
        fp.close();
    }

    auto t = Tokenizer::tokenize(lines);

    cout << "------------" << endl <<"End of file! Bye-bye!" << endl;

    return 0;
}