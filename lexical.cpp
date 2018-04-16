//
// Created by pgourdet on 4/6/2018.
//

#include "lexical.h"

lexical::lexical() {
    tokens ={{1,"\r"},{2,"program"},{3,"var"},{4,"const"},{5,"type"},{6,"function"}
    ,{7,"return"},{8,"begin"},{9,"end"},{10,":=:"},{11,":="},{12,"output"},{13,"if"}
    ,{14,"then"},{15,"else"},{16,"while"},{17,"do"},{18,"case"},{19,"of"},{20,".."}
    ,{21,"otherwise"},{22,"repeat"},{23,"for"},{24,"until"},{25,"loop"},{26,"pool"}
    ,{27,"exit"},{28,"<="},{29,"<>"},{30,"<"},{31,">="},{32,">"},{33,"="},{34,"mod"}
    ,{35,"and"},{36,"or"},{37,"not"},{38,"read"},{39,"succ"},{40,"pred"},{41,"chr"}
    ,{42,"ord"},{43,"eof"},{44,"{"},{45,":"},{46,";"},{47,"."},{48,","},{49,"("}
    ,{50,")"},{51,"+"},{52,"-"},{53,"*"},{54,"/"},{54,"integer"},{55,"string"}};
    leagalVarname = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890_";
    leagalVarname = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890_@!%></?{}[]()+-*\"\'";

//            .insert(std::pair<int,std::string>(1,"\r"));//set this to are needs to be changed \n later
}
void lexical::parse(std::fstream, std::ofstream) {

}
bool lexical::openFile(const std::string pathInputFile,const std::string pathOutputFile) {
    infile.open(pathInputFile);
    ofile.open(pathOutputFile);
     if(!infile){
         std::cout << "Error opening file";
        return false;
     }
    return true;
}
void lexical::readFile() {
    in =  new char[MAXCHAR];
    while( !infile.eof()){

        infile.getline(in,MAXCHAR,'\r');
        for(int l = 0;l< MAXCHAR;l++){
            if(in[l] == ' ')

            if(in[l] == '\r')
                break;
        }

        fileRead.append(in);
    }
    writeFIle();
}

void lexical::writeFIle() {
    ofile << fileRead;
}
