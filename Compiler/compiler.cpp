#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "RISCV32I_ISA.h"
#include "Tokenizer.h"
#include "Parser.h"

using namespace std;

int main(int argc, char** argv) {

    if(argc != 2) {
        cout << "Fuck off!" << endl;
        return -1;
    }

    string line;
    vector<string> lines;

    ifstream fp(argv[1]);
    if(fp.is_open()) {
        while(getline(fp, line)) {
            cout << line << endl;
            lines.push_back(line);
        }
        cout << endl;
        fp.close();
        cout << "------------" << endl <<"Now tokenizing..." << endl;
        auto t = Tokenizer::tokenize(lines);
        cout << "------------" << endl <<"Now parsing and generating code..." << endl;
        auto code = Parser::parse(t);

        if(code.is_error) {
            cout << "Error: " << endl;
            cout << code.error;
        }
        else {
            cout << "Successfully generated code!" << endl;
            cout << code.output << endl;

        }

    }
    else {
        cout << "Unable to open file..." << endl;
    }

    cout << "\n\nSee ya!" << endl;

    return 0;
}