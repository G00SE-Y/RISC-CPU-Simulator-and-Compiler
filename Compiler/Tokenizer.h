#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <fstream>
#include <string>
#include <vector>

typedef struct Operation {
    int op;
    int rs1;
    int rs2;
    int rd;
}op;

enum tokens {NO_TOK = 0, OP = 1, REG = 2, IMM = 3};

class Tokenizer {

    public:
        std::vector<op> Tokenize(std::string line);
        std::vector<op> Tokenize(std::vector<std::string> code);

    private:
        // something, something
};

#endif