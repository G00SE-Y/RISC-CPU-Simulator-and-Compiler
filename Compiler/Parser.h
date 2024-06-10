#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <unordered_map>

#include "Tokenizer.h"


namespace Parser {

    // Enumration for describing the contents of a Definition
    enum definition_type {
        TERM = 0,
        DEF = 1
    };

    typedef struct Compiler_Return {
        std::string error = ""; // error message
        std::vector<std::string> output; // compiled code
    }compRet;

    /*
    This is the core structure for building the syntax rules of the language.
    Every block definition will be comprised of a series of Rule structures that will either represent a singular token or a recursive block definition as indicated by the `type` member's value
    */
    typedef struct Rule {
        Parser::definition_type type; // type of definition member (specific terminal or other definition) 
        Tokenizer::Token tok; // will be initialized if type is TERM
        std::vector<std::string> def; // will be initialized if type is DEF and refers to a set of other rules in the definitions map
        
        // this is only for slightly more convenient addition of definitions to the map
        Rule(Parser::definition_type t, Tokenizer::Token tk, std::vector<std::string> d) {
            type = t;
            tok = tk;
            def = d;
        }
        Rule(){};
    }rule;


    // The bible of this language that will contain all valid syntaxes
    // extern std::unordered_map<std::string, Parser::Rule> definitions;

    // Returns machine code from unparsed tokens if a valid syntax is given
    Parser::Compiler_Return parse(std::vector<std::vector<Tokenizer::Token>> tokens);
    void init_definitions(); // initializes the base values in the definitions map

}

#endif