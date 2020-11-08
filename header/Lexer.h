#ifndef LEXER_H
#define LEXER_H 

#include <utility>
#include <vector>
#include <string>

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define OPERATOR 2
#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11

/* Arithmetic Operations */
#define LEFT_PAREN 20
#define RIGHT_PAREN 21
#define SEMI 22
#define FUNCTION 23
#define QUOATE 24

using namespace std;

class Lexer { 
    private:
        /* Global Variable */
        int nextToken;
        int charClass;
        char lexeme [100];
        char nextChar;
        int lexLen;
        int token;
        string input;
        int inputIndex;

        vector<pair<int, string> > ret;

        /* Local Function declarations */
        void addChar();
        void getChar();
        void getNonBlank();
        int lex();

        int lookup(char ch);
        int is_Function();

    public: 
        vector<pair<int, string> > get_Token();
}; 

#endif