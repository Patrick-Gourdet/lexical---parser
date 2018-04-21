#include <iostream>
#include <cstring>
//#include <cstdlib>
//#include <stdio.h>
//#include <string>
#include <functional>
#include <map>
#include <vector>
#include <fstream>
#include <regex>
#include "lexical.h"


int main(int argc, char* argv[]) {
    lexical lex;
    std::string sourceIn = "C:\\Users\\pgourdet\\CLionProjects\\lexical---parser\\tiny_01_1.txt";
    std::string sourceOut = "C:\\Users\\pgourdet\\CLionProjects\\lexical---parser\\tiny";
    //std::ifstream infile(argv[1]);
    //For testing
    int exception = -1;
    try{
      bool fileOpen =  lex.openFile(sourceIn,sourceOut);
        if(!fileOpen){
            throw exception;
        }
    }
    catch(int exception){
        std::cout << "Error in file! ";
    }
    lex.readFile();
    lex.parsing();
    return 0;
}




