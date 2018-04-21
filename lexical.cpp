//
// Created by pgourdet on 4/6/2018.
//

#include "lexical.h"

lexical::lexical() {
    keyWords ={{1,"\r"},{2,"program"},{3,"var"},{4,"const"},{5,"type"},{6,"function"}
    ,{7,"return"},{8,"begin"},{9,"end"},{10,":=:"},{11,":="},{12,"output"},{13,"if"}
    ,{14,"then"},{15,"else"},{16,"while"},{17,"do"},{18,"case"},{19,"of"},{20,".."}
    ,{21,"otherwise"},{22,"repeat"},{23,"for"},{24,"until"},{25,"loop"},{26,"pool"}
    ,{27,"exit"},{28,"<="},{29,"<>"},{30,"<"},{31,">="},{32,">"},{33,"="},{34,"mod"}
    ,{35,"and"},{36,"or"},{37,"not"},{38,"read"},{39,"succ"},{40,"pred"},{41,"chr"}
    ,{42,"ord"},{43,"eof"},{44,"{"},{45,":"},{46,";"},{47,"."},{48,","},{49,"("}
    ,{50,")"},{51,"+"},{52,"-"},{53,"*"},{54,"/"},{54,"integer"},{55,"string"}};
    leagalVarname = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
    leagalVarname = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890_@!%></?{}[]()+-*\"\'";
    int arr[] = {2,3,4,5,6,7,8,9,12,13,14,15,16,17,18,19,21,22,23,24,};
//            .insert(std::pair<int,std::string>(1,"\r"));//set this to are needs to be changed \n later
}
void lexical::lex() {

}
void lexical::parsing() {
    std::cout << fileRead[1];
    return;
}
//Open the file to be read
bool lexical::openFile(const std::string pathInputFile,const std::string pathOutputFile) {
    infile.open(pathInputFile);
    ofile.open(pathOutputFile);
     if(!infile){
         std::cout << "Error opening file";
        return false;
     }
    return true;
}
//Read file into the infile private variable
void lexical::readFile() {
    in =  new char[MAXCHAR];
    std::string fileRead1;
    while(infile>>fileRead1){
// !infile.eof()
//        infile.getline(in,MAXCHAR,'\r');
//        for(int l = 0;l< MAXCHAR;l++){
//            if(in[l] == ' ')
//
//            if(in[l] == '\r')
//                break;
//        }
//
        fileRead.push_back(fileRead1);
        writeFIle();   }
    closeFile(infile,ofile);


}
//Output the tree to file
void lexical::writeFIle() {
 //   ofile << fileRead[1];

}

void lexical::closeFile(std::ifstream& in, std::ofstream& out) {
    in.close();
    out.close();
}
bool lexical::isKeyword(std::string ch){
    iter= keyWords.find(3);
    if(iter != keywords.end()) {
//        classes["keyword"]++;
        return true;
    }
    else
    {
        return false;
    }
}
bool lexical::isIdentifier(char ch){

        return false;

}
bool lexical::isDigit(std::string ch){
return true;
}
bool lexical::isInteger(char ch){

        return false;
}
bool lexical::isReal(std::string ch){
//    bool isreal=false;
//    if (ch.find(".") != std::string::npos)
//    {
//
//        for (int j=0; j < ch.length(); j++)
//        {
//            if (ch[j]  != '.')
//            {  string search ;
//                search = ch[j];
//                iter=find(ints.begin(),ints.end(),search);
//                if(iter != ints.end()) {
//                    isreal = true;}
//                else
//                {isreal=false;}
//            }
//            else
//            {;}
//
//        }
//    }
//    else
//    {;}
//
//    if (isreal == true)
//    {
//        classes["real"]++;
//        return true;}
//    else
    {return false;}


}
bool lexical::isAlpha(char ch){
        return false;
}
bool lexical::isChar(std::string ch){
    bool ischar=false;

    for(int i=0;  i< ch.length(); i++ )
    {
        if( isalpha(ch[i]) )
            ischar = true;
        else
            ischar = false;
    }

    if(ch.length() > 1 && ischar == true ) {
//        classes["character"]++;
        return true;
    }
    else
    {
        return false;
    }
}