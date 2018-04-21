//
// Created by pgourdet on 4/19/2018.
//
#include <string>
#ifndef SUBC_ANALYZE_H
#define SUBC_ANALYZE_H
class Analyze {
public:
    virtual void  parsing() = 0;
    virtual bool openFile(std::string, std::string) = 0;
    virtual void closeFile(std::ifstream& ,std::ofstream&) = 0;
};
#endif //SUBC_ANALYZE_H
