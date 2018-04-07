#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include <functional>
#include <map>
#include <vector>
#include <fstream>

int main(int argc, char* argv[]) {
    int max = 1200;
    char in[max];
    std::string source;
    //std::ifstream infile(argv[1]);
    //For testing
    int whitespace = 0;
    std::ifstream infile;
    infile.open("tiny_01_1.txt");
    std::ofstream ofile("tiny");
   while( !infile.eof()){

       infile.getline(in,max,'\r');
       for(int l = 0;l< max;l++){
           if(in[l] == ' ')
               whitespace++;
           if(in[l] == '\r')
               break;
       }

       ofile << in;
   }
    std::cout << whitespace;
    infile.close();
    ofile.close();
    return 0;
}




