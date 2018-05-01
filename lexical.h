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
class lexical : public Analyze {
    const int MAXCHAR = 1200;
    char *in;
    std::ofstream ofile;
    std::ifstream infile;
    std::map<int,std::string> keyWords;
    std::map<int,std::string>::iterator iter;
    std::vector<std::string> fileRead;
    std::string leagalVarname;
    std::string leagalChar;
    std::map<int,std::string> keywords;

public:
    lexical();
    ~lexical() = default;
    bool openFile(std::string,std::string) override;
    void closeFile() override;
    void scanner();
    void writeFIle();
    Token analyze() override;
    void lex();
    char* tokenStr(Token,char *);
    TokenType tokenTypeOperator(char);
    TokenType tokenKeyword(char *);
    TokenType tokenDelimiter(char ch);

};


#endif //SUBC_LEXICAL_H
