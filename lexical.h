//
// Created by pgourdet on 4/6/2018.
//

#ifndef SUBC_LEXICAL_H
#define SUBC_LEXICAL_H


#include <iostream>
#include <fstream>
#include <errno.h>
#include <map>

class lexical {
    const int MAXCHAR = 1200;
    char *in;
    std::ofstream ofile;
    std::ifstream infile;
    std::map<int,std::string> tokens;
    std::string fileRead;
    std::string leagalVarname;
    std::string legalChars;

public:
    lexical();
    ~lexical(){};
    bool openFile(std::string,std::string);
    void readFile();
    void writeFIle();
    void parse(std::fstream,std::ofstream);
};


#endif //SUBC_LEXICAL_H
