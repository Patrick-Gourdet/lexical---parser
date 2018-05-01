//
// Created by pgourdet on 4/19/2018.
//
#include <string>
#ifndef SUBC_ANALYZE_H
#define SUBC_ANALYZE_H
#include "varDef.h"
#define MAX 10
class Analyze {
public:
    virtual Token  analyze() = 0;
    virtual bool openFile(std::string, std::string) = 0;
    virtual void closeFile() = 0;
};
#endif //SUBC_ANALYZE_H
