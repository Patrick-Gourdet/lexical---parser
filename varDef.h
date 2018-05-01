//
// Created by pgourdet on 5/1/2018.
//

#ifndef SUBC_VARDEF_H
#define SUBC_VARDEF_H
#define MAX 20 // max length of each word string, not including '\0'
#define LIMIT 300 // max number of word strings in an input file

extern int lineNum;

typedef enum {
    // Identifier: begin with a letter, and continue with any number
    // of letters. No ID is longer than MAX

    T_IDENTIFIER,

    // Keywords (start finish then if repeat var int float do
    // read print void return dummy program)

    T_PROGRAM,
    T_VAR, T_CONST, T_TYPE, T_FUNCTION, T_RETURN, T_BEGIN, T_END, T_OUTPUT, T_IF,
    T_THEN, T_ELSE, T_WHILE, T_DO, T_CASE, T_OF, T_DOTS, // ..
    T_OTHERWISE,T_REPEAT,
    T_FOR, T_UNTIL, T_LOOP, T_POOL, T_EXIT, T_AND, T_OR, T_NOT, T_READ, T_SUCC,
    T_PRED, T_CHAR, T_ORD, T_EOF,

    // Number: sequence of decimal digits, no sign, no longer than MAX digits

    T_INTEGER,
    T_STRING,

    T_EQUAL, // ==
    T_GREATER_THAN, // >
    T_GRESTER_EQUAL,
    T_LESS_THAN, // <
    T_LESS_EQUAL,
    T_NOT_EQUAL, // <>
    T_NOT_GREATER, // <=
    T_NOT_LESS_THAN, // >=


    T_ASSIGN, // :=
    T_SWAP, //:=:
    T_COLON, // :
    T_DIV, // /
    T_MUL, // *
    T_ADD, // +
    T_SUBTRACT, // -
    T_MOD, // mod

    T_DELIM_DOT, // .
    T_DELIM_LEFT_PARRENTHESE, // (
    T_DELIM_RIGHT_PARRENTHESE, // )
    T_DELIM_COMMA, // ,
    T_DELIM_LEFT_BRACE, // {
    T_DELIM_RIHGT_BRACE, // }
    T_DELIM_LEFT_BRACKET, // [
    T_DELIM_RIGHT_BRACKET, // ]
    T_DELIM_SEMICOLON, // ;

    T_UNDEF,		// undefined
    EOFT		// end of token

} TokenType;


struct tokenTag {
    char str[MAX];
    TokenType tokenType;
    int lineNum;

    struct tokenTag *next;
};
typedef struct tokenTag Token;
const char *keywords[35] = {"program","var","const","type","function"
        ,"return","begin","end","output","if"
        ,"then","else","while","do","case","of",".."
        ,"otherwise","repeat","for","until","loop","pool"
        ,"exit","and","or","not","read","succ","pred","chr"
        ,"ord","eof","integer","string"};

const char *relationalOperators[] = {"==", "<", ">", "<>", "=>", "=<",":=:",":="};

// char *otherOperators[] = {":", "+", "-", "*", "/", "%"};
const char otherOperators[6] = {':', '+', '-', '*', '/', 'm'};

// char *delimiters[9] = {".", "(", ")", ",", "{", "}", ";", "[", "]"};
const char delimiters[9] = {'.', '(', ')', ',', '{', '}', ';', '[', ']'};

char word[MAX];
int wordIndex = 0; // index of word string

char numStr[MAX];
int numberIndex = 0;




extern int numToken;
extern Token *tokens;
#endif //SUBC_VARDEF_H
