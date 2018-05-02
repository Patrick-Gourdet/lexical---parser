//
// Created by pgourdet on 4/19/2018.
//
#include <string>
#ifndef SUBC_ANALYZE_H
#define SUBC_ANALYZE_H
#define MAX 20 // max length of each word string, not including '\0'
#define LIMIT 300 // max number of word strings in an input file
class Analyze {
public:
    virtual bool openFile(std::string, std::string) = 0;
    virtual void closeFile() = 0;
};
#endif //SUBC_ANALYZE_H
