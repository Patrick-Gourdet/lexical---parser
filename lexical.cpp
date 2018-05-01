//
// Created by pgourdet on 4/6/2018.
//

#include "lexical.h"

/*----------Check a char----------*/
int isKeyword(char *str) {
    int i;
    int result = 0; // false
    //Compare the word to see if it is a Key word
    for (i = 0; i < 35; i++) {
        if (!strcasecmp(keywords[i], str))
            result = 1;
    }
    return result;

}

int isDelimiter(char c) {
    int i;
    int result = 0; // false
    for (i = 0; i < 9; i++) {
        if (delimiters[i] == c)
            result = 1;
    }
    return result;
}

int isOtherOperators(char c) {
    int i;
    int result = 0; // false
    for (i = 0; i < 6; i++) {
        if (otherOperators[i] == c)
            result = 1;
    }
    return result;
}
int isStartRelationalOperator(char c) {
    int i;
    int result = 0; // false
    if (c == '=' || c == '<' || c == '>') {
        result = 1;
    }
    return result;
}
lexical::lexical() {
//    keyWords ={{1,"\r"},{2,"program"},{3,"var"},{4,"const"},{5,"type"},{6,"function"}
//    ,{7,"return"},{8,"begin"},{9,"end"},{10,":=:"},{11,":="},{12,"output"},{13,"if"}
//    ,{14,"then"},{15,"else"},{16,"while"},{17,"do"},{18,"case"},{19,"of"},{20,".."}
//    ,{21,"otherwise"},{22,"repeat"},{23,"for"},{24,"until"},{25,"loop"},{26,"pool"}
//    ,{27,"exit"},{28,"<="},{29,"<>"},{30,"<"},{31,">="},{32,">"},{33,"="},{34,"mod"}
//    ,{35,"and"},{36,"or"},{37,"not"},{38,"read"},{39,"succ"},{40,"pred"},{41,"chr"}
//    ,{42,"ord"},{43,"eof"},{44,"{"},{45,":"},{46,";"},{47,"."},{48,","},{49,"("}
//    ,{50,")"},{51,"+"},{52,"-"},{53,"*"},{54,"/"},{54,"integer"},{55,"string"}};
//    leagalVarname = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
    leagalChar = "_@!%></?{}[]()+-*\"\':;=.";
//    int arr[] = {2,3,4,5,6,7,8,9,12,13,14,15,16,17,18,19,21,22,23,24,};
//            .insert(std::pair<int,std::string>(1,"\r"));//set this to are needs to be changed \n later
}
void lexical::lex() {
    std::ifstream &fptr = infile;

    char get;
    int numLine = 1;

    int charCount = 0;
    char tempStr[MAX]; // ! Remember: C doesn't do array out-of-bound checking!
    int i;

    int isValid = 1; // true
    while (!(fptr.get(get)).eof()) {
        if (get == '\n')
            numLine++;

        // Exclude comment line starting with '//'
        if (get == '{') {
            (fptr.get(get));
            while (get != '}') {
                (fptr.get(get));
                if(get  == '\n'){
                    numLine++;
                }

            }
            (fptr.get(get));
        }

        // printf("%c", c);

        if (isalnum(get)) {
            //printf("%c is letter or a number \n", c);
            tempStr[charCount] = get; // array out-of-bound checking not happen here
            charCount++;
            if (charCount > MAX) {
                printf("Word '%s' on line number %d is too long. \n", tempStr, numLine);
                exit(1);
            }
        } else if (isspace(get) || leagalChar.find(get) != std::string::npos) {
            //printf("%c is space is extra acceptable character \n", c);
            charCount = 0;
        } else {
            printf("Invalid character '%c' at line %d. \n", get, numLine);
            isValid = 0; // false
        }

    }

    if (isValid == 0) {
        printf("Something wrong with the input file. \n");
        exit(1);
    }
}
void lexical::scanner(){
    printf("%10s \t Line number \t %s\n\n", "Token instance", "Token type");
    numToken = 0; // extern var
    //Token *tokens = (Token *) malloc(numToken * sizeof(Token));
    tokens = (Token *) malloc(numToken * sizeof(Token)); // extern var
    do {
        numToken++;
        tokens = (Token *)realloc(tokens, numToken * sizeof(Token));
        tokens[numToken - 1] = analyze();

        printToken(tokens[numToken - 1]);

    } while (tokens[numToken - 1].tokenType != EOFtk);
}
Token lexical::analyze() {
    int lineNum = 1;
    std::ifstream &fptr = infile;
    Token token;
    char get;

    while (!fptr.get(get).eof()) {
        if (get == '\n')
            lineNum++;

        // Ignore comment starting with // to the end of line
        if (get == '{') {
            (fptr.get(get));
            while (get != '}') {
                (fptr.get(get));
                if(get == '\n'){
                    lineNum++;
                }

            }
            (fptr.get(get));
        }
        // mod was giving me issues
        if(get == 'm'){
            int g = 6;
        }
        if (isalpha(get) && get != 'm') {
            word[wordIndex++] = get;
            (fptr.get(get));
            while (isalpha(get)) {
                word[wordIndex++] = get;
            }
            word[wordIndex] = '\0';
            wordIndex = 0;

            strcpy(token.str, word);
            if (isKeyword(word)) {
                token.tokenType = tokenKeyword(word);
            } else {
                token.tokenType = T_IDENTIFIER;
            }
            token.lineNum = lineNum;


              fptr.unget();
//            fseek(filePtr, -1, SEEK_CUR);
            //printToken(token);
            return token;
        }

        else if (isdigit(get)) {
            numStr[numberIndex++] = get;
            (fptr.get(get));
            while (isdigit(get)) {
                numStr[numberIndex++] = get;
            }
            numStr[numberIndex] = '\0';
            numberIndex = 0;

            strcpy(token.str, numStr);
            token.tokenType = T_INTEGER;
            token.lineNum = lineNum;

              fptr.unget();
//            fseek(filePtr, -1, SEEK_CUR);
            //printToken(token);
            return token;

        }

        else if (ispunct(get) || get == 'm') {
            if (isDelimiter(get)) {
                token.tokenType = tokenDelimiter(get);
                token.lineNum = lineNum;

                char str[2];
                str[0] = get;
                str[1] = '\0';
                strcpy(token.str, str);

                //printToken(token);
                return token;
            }
            else if (isOtherOperators(get)) {
                token.tokenType = tokenTypeOperator(get);
                token.lineNum = lineNum;
                if(get == 'm'){
                    (fptr.get(get));
                    (fptr.get(get));
//                    ch = '%';
                }

                char str[2];
                str[0] = get;
                str[1] = '\0';
                strcpy(token.str, str);

                //printToken(token);
                return token;
            }
            else if (isStartRelationalOperator(get)) {
                if (get == '<' || get == '>') {
                    token.lineNum = lineNum;
                    if (get == '<') {
                        token.tokenType = T_LESS_THAN;
                        strcpy(token.str, "<");
                    } else {
                        token.tokenType = T_GREATER_THAN;
                        strcpy(token.str, ">");
                    }
                    //printToken(token);
                    return token;
                }
                else if (get == '=') {
                    (fptr.get(get));
                    if (get == '=' || get == '>' || get == '<') {
                        token.lineNum = lineNum;
                        if (get == '=') {
                            token.tokenType = T_EQUAL;
                            strcpy(token.str, "==");
                        } else if (get == '>') {
                            token.tokenType = T_GRESTER_EQUAL;

                            strcpy(token.str, ">=");
                        } else {
                            token.tokenType = T_LESS_EQUAL;
                            strcpy(token.str, "<=");
                        }

                        //printToken(token);
                        return token;

                    } else if (get == '<') {
                        (fptr.get(get));
                        if (get == '>') {
                            token.lineNum = lineNum;
                            token.tokenType = T_NOT_EQUAL;
                            strcpy(token.str, "<>");

                            //printToken(token);
                            return token;
                        } else
                            fptr.unget();
                    } else
                        fptr.unget();
                }
            }
        } // end if ispunct

    } // end while

    // rewind(filePtr);

    //printf("\n*** in scanner.c ***\n");

    token.tokenType = EOFtk;
    return token;
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

//Output the tree to file
void lexical::writeFIle() {
 //   ofile << fileRead[1];

}

void lexical::closeFile() {
    infile.close();
    ofile.close();
}
TokenType lexical::tokenKeyword(char *word) {

    if (strcasecmp(word, "program") == 0) return STARTtk;
    if (strcasecmp(word, "begin") == 0) return T_BEGIN;
    if (strcasecmp(word, "end") == 0) return FINISHtk;
    if (strcasecmp(word, "if") == 0) return IFtk;
    if (strcasecmp(word, "else") == 0) return T_ELSE;
    if (strcasecmp(word, "then") == 0) return THENtk;
    if (strcasecmp(word, "repeat") == 0) return REPEATtk;

    if (strcasecmp(word, "for") == 0) return T_FOR;
    if (strcasecmp(word, "loop") == 0) return T_LOOP;
    if (strcasecmp(word, "until") == 0) return T_UNTIL;
    if (strcasecmp(word, "Ord") == 0) return T_ORD;
    if (strcasecmp(word, "return")==0) return T_RETURN;
    if (strcasecmp(word, "eof") == 0) return T_EOF;
    if (strcasecmp(word, "var") == 0) return VARtk;
    if (strcasecmp(word, "string") == 0) return STRING;
    if (strcasecmp(word, "integer") == 0) return INTtk;
    if (strcasecmp(word, "float") == 0) return FLOATtk;
//	if (strcasecmp(word, "program") == 0) { return T_PROGRAM; }
    if (strcasecmp(word, "read") == 0) return READtk;
    if (strcasecmp(word, "function") == 0) return T_FUNCTION;
    if (strcasecmp(word, "read") == 0) return READtk;
    if (strcasecmp(word, "print") == 0) return PRINTtk;
    if (strcasecmp(word, "void") == 0) return VOIDtk;
    if (strcasecmp(word, "end") == 0) return T_END;
    if (strcasecmp(word, "dummy") ==0) return DUMMYtk;
    if (strcasecmp(word, "program") == 0) return PROGRAMtk;
}

TokenType lexical::tokenDelimiter(char ch) {
    if (ch == '.') return DOTtk;
    if (ch == '(') return LEFTPAtk;
    if (ch == ')') return RIGHTPAtk;
    if (ch == ',') return COMMAtk;
    if (ch == '{') return LEFTBRACEtk;
    if (ch == '}') return RIGHTBRACEtk;
    if (ch == ';') return SEMICOLONtk;
    if (ch == '[') return LEFTBRACKETtk;
    if (ch == ']') return RIGHTBRACKETtk;
}

TokenType lexical::tokenTypeOperator(char ch) {
    if (ch == '=') return ASSIGNtk;
    if (ch == ':') return COLONtk;
    if (ch == '+') return ADDtk;
    if (ch == '-') return SUBTRACTtk;
    if (ch == '*') return MULtk;
    if (ch == '/') return DIVtk;
    if (ch == 'm') return REMAINDERtk;
}

char *lexical::tokenStr(Token token, char *str) {
    switch (token.tokenType) {
        case IDtk: strcpy(str, "IDENTIFER"); break;
        case NUMBERtk: strcpy(str, "NUMBER"); break;
        case T_ELSE: 	strcpy(str, "else [KEYWORD]"); break;
        case T_FUNCTION:strcpy(str, "function [KEYWORD]"); break;
        case T_BEGIN: 	strcpy(str, "begin [KEYWORD]"); break;
        case STARTtk: 	strcpy(str, "program [KEYWORD]"); break;
        case FINISHtk: 	strcpy(str, "finish [KEYWORD]"); break;
        case THENtk: 	strcpy(str, "then [KEYWORD]"); break;
        case IFtk: 		strcpy(str, "if [KEYWORD]"); break;
        case REPEATtk: 	strcpy(str, "repeat [KEYWORD]"); break;
        case T_FOR:     strcpy(str, "for [KEYWORD]"); break;
        case T_LOOP:    strcpy(str, "loop [KEYWORD]"); break;
        case T_UNTIL:   strcpy(str, "until [KEYWORD]"); break;
        case VARtk: 	strcpy(str, "var [KEYWORD]"); break;
        case INTtk: 	strcpy(str, "integer [KEYWORD]"); break;
        case FLOATtk: 	strcpy(str, "float [KEYWORD]"); break;
        case DOtk: 		strcpy(str, "do [KEYWORD]"); break;
        case READtk: 	strcpy(str, "read [KEYWORD]"); break;
        case PRINTtk: 	strcpy(str, "print [KEYWORD]"); break;
        case VOIDtk: 	strcpy(str, "void [KEYWORD]"); break;
        case T_END: 	strcpy(str, "end [KEYWORD]"); break;
        case DUMMYtk: 	strcpy(str, "dummy [KEYWORD]"); break;
        case T_ORD:     strcpy(str, "Ord [KEYWORD]"); break;
        case T_RETURN:   strcpy(str, "return [KEYWORD]"); break;
        case DOTtk: 	strcpy(str, "dot [DELIMITER]"); break;
        case LEFTPAtk: 	strcpy(str, "left-parenthesis [DELIMITER]"); break;
        case RIGHTPAtk: strcpy(str, "right-parenthesis [DELIMITER]"); break;
        case COMMAtk: 	strcpy(str, "comma [DELIMITER]"); break;
        case LEFTBRACEtk: 		strcpy(str, "left-brace [DELIMITER]"); break;
        case RIGHTBRACEtk: 		strcpy(str, "right-brace [DELIMITER]"); break;
        case LEFTBRACKETtk:		strcpy(str, "left-bracket [DELIMITER]"); break;
        case RIGHTBRACKETtk:	strcpy(str, "right-bracket [DELIMITER]"); break;
        case SEMICOLONtk: 		strcpy(str, "semi-colon [DELIMITER]"); break;
        case T_EOF:         strcpy(str, "eof [KEYWORD"); break;
        case ASSIGNtk:		strcpy(str, "assign [OTHER OPERATOR]"); break;
        case COLONtk:		strcpy(str, "colon [OTHER OPERATOR]"); break;
        case ADDtk:			strcpy(str, "add [OTHER OPERATOR]"); break;
        case SUBTRACTtk:	strcpy(str, "subtractk [OTHER OPERATOR]"); break;
        case MULtk: 		strcpy(str, "multiply [OTHER OPERATOR]"); break;
        case DIVtk: 		strcpy(str, "division [OTHER OPERATOR]"); break;
        case REMAINDERtk:	strcpy(str, "mod [OTHER OPERATOR]"); break;

        case EQUALtk: 		strcpy(str, "equal [RELATIONAL OPERATOR]"); break;
        case GREATERtk:		strcpy(str, "greater [RELATIONAL OPERATOR]"); break;
        case LESStk:		strcpy(str, "less than [RELATIONAL OPERATOR]"); break;
        case DIFFtk:		strcpy(str, "different [RELATIONAL OPERATOR]"); break;
        case GREATEREQtk:	strcpy(str, "greater or equal [RELATIONAL OPERATOR]"); break;
        case LESSEQtk: 		strcpy(str, "less than or equal [RELATIONAL OPERATOR]"); break;


        default: strcpy(str, "UNKNOWN");
    }
    return str;
}