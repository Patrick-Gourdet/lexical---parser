//
// Created by pgourdet on 4/6/2018.
//
#include "lexical.h"


int lineNum = 1;


const char *keywords[36] = {"program","var","const","type","function"
        ,"return","begin","end","output","if"
        ,"then","else","while","do","case","of",".."
        ,"otherwise","repeat","for","until","loop","pool"
        ,"exit","and","or","not","read","succ","pred","chr"
        ,"ord","eof","integer","string","mod"};

const char *relationalOperators[] = {"==", "<", ">", "<>", "=>", "=<",":=:",":="};

// char *otherOperators[] = {":", "+", "-", "*", "/", "%"};
const char otherOperators[6] = {':', '+', '-', '*', '/'};

// char *delimiters[9] = {".", "(", ")", ",", "{", "}", ";", "[", "]"};
const char delimiters[9] = {'.', '(', ')', ',', '{', '}', ';', '[', ']'};

char word[MAX];
int wordIndex = 0; // index of word string

char numStr[MAX];
int numberIndex = 0;


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
    leagalChar = "_@!%></?{}[]()+-*\"\':;=.,";

//    int arr[] = {2,3,4,5,6,7,8,9,12,13,14,15,16,17,18,19,21,22,23,24,};
//            .insert(std::pair<int,std::string>(1,"\r"));//set this to are needs to be changed \n later
}
void lexical::lex() {
    infile;

    char get;
    int numLine = 1;

    int charCount = 0;
    char tempStr[MAX]; // ! Remember: C doesn't do array out-of-bound checking!
    int i;

    int isValid = 1; // true
    while (!(infile.get(get)).eof()) {
        if (get == '\n')
            numLine++;

        // Exclude comment line starting with '//'
        if (get == '{') {
            (infile.get(get));
            while (get != '}') {
                (infile.get(get));
                if(get  == '\n'){
                    numLine++;
                }

            }
            (infile.get(get));
        }
        if (get == '#') {
            (infile.get(get));
            while (get != '\n') {
                (infile.get(get));

            }
            lineNum++;(infile.get(get));
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
    infile.clear();
    infile.seekg(0);
    if (isValid == 0) {
        printf("Something wrong with the input file. \n");
        exit(1);
    }
    printf("%10s \t Line number \t %s\n\n", "Token instance", "Token type");
    numToken = 0; // extern var
    //Token *tokens = (Token *) malloc(numToken * sizeof(Token));
    tokens = (Token1 *) malloc(numToken * sizeof(Token1)); // extern var
    do {
        numToken++;
        tokens = (Token1 *)realloc(tokens, numToken * sizeof(Token1));
        tokens[numToken - 1] = analyze(infile);

        tkPrint(tokens[numToken - 1]);

    } while (tokens[numToken - 1].tokenType != T_EOF);
}

Token1 lexical::analyze(std::ifstream &fptr) {

    Token1 token;
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
        if (get == '#') {
            (infile.get(get));
            while (get != '\n') {
                (infile.get(get));

            }
            lineNum++; (infile.get(get));
        }



        if (isalpha(get) ) {
            word[wordIndex++] = get;
            (fptr.get(get));
            while (isalpha(get)) {
                word[wordIndex++] = get;
                (fptr.get(get));

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


//              fptr.unget();
//            fseek(filePtr, -1, SEEK_CUR);
            //printToken(token);
            return token;
        }

        else if (isdigit(get)) {
            numStr[numberIndex++] = get;
            (fptr.get(get));
            while (isdigit(get)) {
                numStr[numberIndex++] = get;
                (fptr.get(get));

            }
            numStr[numberIndex] = '\0';
            numberIndex = 0;

            strcpy(token.str, numStr);
            token.tokenType = T_NUMBER;
            token.lineNum = lineNum;

            fptr.unget();
//            fseek(filePtr, -1, SEEK_CUR);
            //printToken(token);
            return token;

        }

        else if (ispunct(get) ) {
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
                            token.tokenType = T_GREATER_EQUAL;

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

    token.tokenType = T_EOF;
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

    if (strcasecmp(word, "program") == 0) return T_PROGRAM;
    if (strcasecmp(word, "begin") == 0) return T_BEGIN;
    if (strcasecmp(word, "end") == 0) return T_END;
    if (strcasecmp(word, "if") == 0) return T_IF;
    if (strcasecmp(word, "else") == 0) return T_ELSE;
    if (strcasecmp(word, "then") == 0) return T_THEN;
    if (strcasecmp(word, "not") == 0) return T_NOT;
    if (strcasecmp(word, "repeat") == 0) return T_REPEAT;
    if (strcasecmp(word, "while") == 0) return T_WHILE;
    if (strcasecmp(word, "for") == 0) return T_FOR;
    if (strcasecmp(word, "loop") == 0) return T_LOOP;
    if (strcasecmp(word, "until") == 0) return T_UNTIL;
    if (strcasecmp(word, "Ord") == 0) return T_ORD;
    if (strcasecmp(word, "return")==0) return T_RETURN;
    if (strcasecmp(word, "eof") == 0) return T_EOF;
    if (strcasecmp(word, "var") == 0) return T_VAR;
    if (strcasecmp(word, "string") == 0) return T_STRING;
    if (strcasecmp(word, "integer") == 0) return T_INTEGER;
    if (strcasecmp(word, "read") == 0) return T_READ;
    if (strcasecmp(word, "function") == 0) return T_FUNCTION;
    if (strcasecmp(word, "output") == 0) return T_OUTPUT;
    if (strcasecmp(word, "end") == 0) return T_END;
    if (strcasecmp(word, "program") == 0) return T_POOL;
    if (strcasecmp(word, "..") == 0) return T_DOTS;
    if (strcasecmp(word, "mod") == 0) return T_MOD;
}

TokenType lexical::tokenDelimiter(char ch) {
    if (ch == '.') return T_DELIM_DOT;
    if (ch == '(') return T_DELIM_LEFT_PARRENTHESE;
    if (ch == ')') return T_DELIM_RIGHT_PARRENTHESE;
    if (ch == ',') return T_DELIM_COMMA;
    if (ch == '{') return T_DELIM_LEFT_BRACE;
    if (ch == '}') return T_DELIM_RIHGT_BRACE;
    if (ch == ';') return T_DELIM_SEMICOLON;
    if (ch == '[') return T_DELIM_LEFT_BRACKET;
    if (ch == ']') return T_DELIM_RIGHT_BRACKET;
}

TokenType lexical::tokenTypeOperator(char ch) {
    if (ch == '=') return T_ASSIGN;
    if (ch == ':') return T_COLON;
    if (ch == '+') return T_ADD;
    if (ch == '-') return T_SUBTRACT;
    if (ch == '*') return T_MUL;
    if (ch == '/') return T_DIV;
//    if (ch == 'm') return T_MOD;
}

char *lexical::tokenStr(Token1 token, char *str) {
    switch (token.tokenType) {
        case T_IDENTIFIER:  strcpy(str, "<IDENTIFER>"); break;
        case T_NUMBER:      strcpy(str, "<NUMBER>"); break;
        case T_ELSE: 	    strcpy(str, "<KEYWORD>"); break;
        case T_FUNCTION:    strcpy(str, "<KEYWORD>"); break;
        case T_BEGIN: 	    strcpy(str, "<KEYWORD>"); break;
        case T_PROGRAM: 	strcpy(str, "<KEYWORD>"); break;
        case T_THEN: 	    strcpy(str, "<KEYWORD>"); break;
        case T_IF: 		    strcpy(str, "<KEYWORD>"); break;
        case T_NOT:         strcpy(str, "<KEYWORD>"); break;
        case T_REPEAT:  	strcpy(str, "<KEYWORD>"); break;
        case T_FOR:         strcpy(str, "<KEYWORD>"); break;
        case T_LOOP:        strcpy(str, "<KEYWORD>"); break;
        case T_WHILE:       strcpy(str, "<KEYWORD>"); break;
        case T_UNTIL:        strcpy(str, "<KEYWORD>"); break;
        case T_VAR: 	    strcpy(str, "<KEYWORD>"); break;
        case T_INTEGER:    	strcpy(str, "<KEYWORD>"); break;
        case T_DO: 		    strcpy(str, "<KEYWORD>"); break;
        case T_READ: 	    strcpy(str, "<KEYWORD>"); break;
        case T_OUTPUT:  	strcpy(str, "<KEYWORD>"); break;
        case T_END: 	    strcpy(str, "<KEYWORD>"); break;
        case T_ORD:         strcpy(str, "<KEYWORD>"); break;
        case T_RETURN:       strcpy(str, "<KEYWORD>"); break;
        case T_DELIM_DOT: 	strcpy(str, "<DELIMITER>"); break;
        case T_DELIM_LEFT_PARRENTHESE: 	strcpy(str, "<DELIMITER>"); break;
        case T_DELIM_RIGHT_PARRENTHESE: strcpy(str, "<DELIMITER>"); break;
        case T_DELIM_COMMA: 	strcpy(str, "<DELIMITER>"); break;
        case T_DELIM_LEFT_BRACE: 		strcpy(str, "<DELIMITER>"); break;
        case T_DELIM_RIHGT_BRACE: 		strcpy(str, "<DELIMITER>"); break;
        case T_DELIM_LEFT_BRACKET:		strcpy(str, "<DELIMITER>"); break;
        case T_DELIM_RIGHT_BRACKET:	 strcpy(str, "<DELIMITER>"); break;
        case T_DELIM_SEMICOLON: 	 strcpy(str, "<DELIMITER>"); break;
        case T_EOF:                  strcpy(str, "<KEYWORD>"); break;
        case T_ASSIGN:		         strcpy(str, "<OPERATOR>"); break;
        case T_COLON:		strcpy(str, "<OPERATOR>"); break;
        case T_ADD:			strcpy(str, "<OPERATOR>"); break;
        case T_SUBTRACT:	strcpy(str, "<OPERATOR>"); break;
        case T_MUL: 		strcpy(str, "<OPERATOR>"); break;
        case T_DIV: 		strcpy(str, "<OPERATOR>"); break;
        case T_DOTS:        strcpy(str, "<OPERATOR>"); break;
        case T_MOD:	        strcpy(str, "<OPERATOR>"); break;

        case T_EQUAL: 		strcpy(str, "equal [RELATIONAL OPERATOR]"); break;
        case T_GREATER_THAN:		strcpy(str, "greater [RELATIONAL OPERATOR]"); break;
        case T_LESS_THAN:		strcpy(str, "less than [RELATIONAL OPERATOR]"); break;
        case T_GREATER_EQUAL:	strcpy(str, "greater or equal [RELATIONAL OPERATOR]"); break;
        case T_LESS_EQUAL: 		strcpy(str, "less than or equal [RELATIONAL OPERATOR]"); break;


        default: strcpy(str, "UNKNOWN");
    }
    return str;
}

void lexical::tkPrint(Token1 token) {
    if (token.tokenType == T_EOF) {
        printf("DONE \n\n");
        return;
    }

    char tokenTypestr[2 * MAX];
    printf("%10s \t line #%d \t %s \n",
           token.str, token.lineNum, tokenStr(token, tokenTypestr));
}