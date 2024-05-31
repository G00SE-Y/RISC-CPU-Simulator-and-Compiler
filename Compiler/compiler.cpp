#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>

#include "RISCV32I_ISA.h"
#include "Tokenizer.h"
#include "Parser.h"

std::string bin_to_hex(std::string bin);

using std::cout, std::endl;

int main(int argc, char** argv) {

    if(argc != 3) {
        if(argc < 3) cout << "Not enough arguments!\n";
        else cout << "Too many arguments!\n";
        return -1;
    }

    std::string line;
    std::vector<std::string> lines;

    std::ifstream ifp(argv[1]);
    std::ofstream ofp(argv[2]);

    if(ifp.is_open() && ofp.is_open()) {
        while(getline(ifp, line)) {
            cout << line << endl;
            lines.push_back(line);
        }
        cout << endl;
        ifp.close();
        cout << "------------" << endl <<"Now tokenizing..." << endl;
        auto t = Tokenizer::tokenize(lines);
        cout << "------------" << endl <<"Now parsing and generating code..." << endl;
        auto code = Parser::parse(t);

        if(code.error.size()) { // compilation error, do not write to file
            cout << "Error: " << endl;
            cout << code.error;
        }
        else { // no error, generate addresses and write generated code to file 
            cout << "Successfully generated code!" << endl;

            int address = 0;
            for(auto& line: code.output) {

                cout << std::bitset<32>(address).to_string() << "\t" << line << "\n";
                ofp << "0x" << bin_to_hex(std::bitset<32>(address).to_string()) << "\t" << "0x" << bin_to_hex(line) << "\n";
                address+=4;
            }

        }
        ofp.close();

    }
    else {
        cout << "Unable to open file..." << endl;
    }

    cout << "\n\nSee ya!" << endl;

    return 0;
}



/*
Converts a given binary string to a hex string without checking for chars //todo
*/
std::string bin_to_hex(std::string bin) {
    
    const char hex_digits[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    if(bin.size() % 4 != 0) return "";

    std::string hex = "";
    int digit;

    for(std::size_t i = 0; i < bin.size(); i += 4) {
        
        digit = std::stoi(bin.substr(i, 4), 0, 2);
        // cout << bin.substr(i, 4) <<" -> " << hex_digits[digit] << "\n";

        hex += hex_digits[digit];
    }

    return hex;
}