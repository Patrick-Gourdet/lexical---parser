//
// Created by pgourdet on 4/6/2018.
//

#ifndef SUBC_LEXICAL_H
#define SUBC_LEXICAL_H


#include <iostream>
#include <fstream>
#include <cerrno>
#include <map>
#include <vector>
#include <cstring>
#include "analyze.h"
typedef enum {
    // Identifier: begin with a letter, and continue with any number
    // of letters. No ID is longer than MAX

    T_IDENTIFIER,

    // Keywords (start finish then if repeat var int float do
    // read print void return dummy program)

    T_PROGRAM,
    T_VAR, T_CONST, T_TYPE, T_FUNCTION, T_RETURN, T_BEGIN, T_END, T_OUTPUT, T_IF,
    T_THEN, T_ELSE, T_WHILE, T_DO, T_CASE, T_OF, T_DOTS, // ..
    T_OTHERWISE,T_REPEAT,
    T_FOR, T_UNTIL, T_LOOP, T_POOL, T_EXIT, T_AND, T_OR, T_NOT, T_READ, T_SUCC,
    T_PRED, T_CHAR, T_ORD, T_EOF,

    // Number: sequence of decimal digits, no sign, no longer than MAX digits

    T_INTEGER,
    T_NUMBER,
    T_STRING,

    T_EQUAL, // ==
    T_GREATER_THAN, // >
    T_GREATER_EQUAL,
    T_LESS_THAN, // <
    T_LESS_EQUAL,
    T_NOT_EQUAL, // <>
    T_NOT_GREATER, // <=
    T_NOT_LESS_THAN, // >=


    T_ASSIGN, // :=
    T_SWAP, //:=:
    T_COLON, // :
    T_DIV, // /
    T_MUL, // *
    T_ADD, // +
    T_SUBTRACT, // -
    T_MOD, // mod

    T_DELIM_DOT, // .
    T_DELIM_LEFT_PARRENTHESE, // (
    T_DELIM_RIGHT_PARRENTHESE, // )
    T_DELIM_COMMA, // ,
    T_DELIM_LEFT_BRACE, // {
    T_DELIM_RIHGT_BRACE, // }
    T_DELIM_LEFT_BRACKET, // [
    T_DELIM_RIGHT_BRACKET, // ]
    T_DELIM_SEMICOLON, // ;

    T_UNDEF,		// undefined
    EOFT		// end of token

} TokenType;


struct tokenTag {
    char str[MAX];
    TokenType tokenType;
    int lineNum;

    struct tokenTag *next;
};
typedef struct tokenTag Token1;



class lexical : public Analyze {
    int numToken;
    Token1 *tokens;
    char *in;
    std::ofstream ofile;
    std::ifstream infile;
    std::map<int,std::string> keyWords;
    std::map<int,std::string>::iterator iter;
    std::vector<std::string> fileRead;
    std::string leagalVarname;
    std::string leagalChar;


public:
    lexical();
    ~lexical() = default;
    bool openFile(std::string,std::string) override;
    void closeFile() override;
    void scanner(std::ifstream&);
    void writeFIle();
    Token1 analyze(std::ifstream&);
    void lex();
    char* tokenStr(Token1,char *);
    void tkPrint(Token1);
    TokenType tokenTypeOperator(char);
    TokenType tokenKeyword(char *);
    TokenType tokenDelimiter(char ch);

};


#endif //SUBC_LEXICAL_H
