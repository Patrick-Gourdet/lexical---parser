//
// Created by pgourdet on 4/6/2018.
//

#ifndef SUBC_LEXICAL_H
#define SUBC_LEXICAL_H


#include <iostream>
#include <fstream>
#include <errno.h>
#include <map>
#include <vector>
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
    std::string legalChars;
    std::map<int,std::string> keywords;

public:
    lexical();
    ~lexical() = default;
    bool openFile(std::string,std::string) override;
    void closeFile(std::ifstream&,std::ofstream&) override;
    void readFile();
    void writeFIle();
    void parsing() override;
    void lex();
    bool isKeyword(std::string);
    bool isIdentifier(char);
    bool isInteger(char);
    bool isDigit(std::string);
    bool isReal(std::string);
    bool isChar(std::string);
    bool isAlpha(char);
};


#endif //SUBC_LEXICAL_H
