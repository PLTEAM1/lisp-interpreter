
/**
 * This the example lexical analyzer code in pages 173 - 177 of the
 * textbook,
 *
 * Sebesta, R. W. (2012). Concepts of Programming Languages.
 * Pearson, 10th edition.
 *
 */

/* front.c - a lexical analyzer system for simple arithmetic expressions */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <vector>
#include <utility>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

/* Global Variable */
int nextToken;
int charClass;
char lexeme [100];
char nextChar;
int lexLen;
int token;
//int nextToken;

FILE *in_fp;
FILE *out_fp;
FILE *test_fp;

vector<pair<int,string>> ret;

/* Local Function declarations */
void addChar();
void getChar();
void getNonBlank();
int lex();

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
/* Reserved Words */

vector<pair<int,string>> get_Token(){
    
    /* Open the input data file and process its contents */
    out_fp = fopen("code.out", "w");
    
//    if ((in_fp = fopen("test.in", "r")) == NULL) {
//        printf("ERROR - cannot open code.in \n");
//    } else {
//        getChar();
//        do {
//            lex();
//        } while (nextToken != EOF);
//    }
     
    getchar();
    do{
        lex();
    } while (nextToken != EOF);
     
    return ret;
}

/******************************************
 * lookup - a function to lookup operators
 * and parentheses and return the token
 ******************************************/
int lookup(char ch) {
    switch (ch) {
        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            break;
        case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            break;
        case ';':
           addChar();
           nextToken = SEMI;
           break;
        case '+':
           addChar();
           nextToken = FUNCTION;
           break;
        case '-':
           addChar();
           nextToken = FUNCTION;
           break;
        case '*':
           addChar();
           nextToken = FUNCTION;
           break;
        case '/':
           addChar();
           nextToken = FUNCTION;
           break;
        case '\'':
            addChar();
            nextToken = FUNCTION;
            break;
        default:
            addChar();
            nextToken = EOF;
            break;
    }
    return nextToken;
}

/**
 * 사칙연산     : + , - , *, /
 * 기본 함수    : SETQ, LIST, CAR, CDR, NTH, CONS, REVERSE, APPEND, LENGTH, MEMBER, ASSOC, REMOVE, SUBST
 *          ATOM, NULL, NUMBERP, ZEROP, MINUSP, EQUAL, <, >, <= >=, STRINGP, IF, COND
 */

int is_Function(){
   if(!strcmp(lexeme, "SETQ") || !strcmp(lexeme, "LIST") ||!strcmp(lexeme, "CAR") ||!strcmp(lexeme, "CDR") ||!strcmp(lexeme, "NTH") ||!strcmp(lexeme, "CONS") ||!strcmp(lexeme, "REVERSE") ||!strcmp(lexeme, "APPEND") ||!strcmp(lexeme, "LENGTH") ||!strcmp(lexeme, "MEMBER") ||!strcmp(lexeme, "ASSOC") ||!strcmp(lexeme, "REMOVE") ||!strcmp(lexeme, "SUBST") ||!strcmp(lexeme, "ATOM") ||!strcmp(lexeme, "NULL") ||!strcmp(lexeme, "NUMBERP") ||!strcmp(lexeme, "ZEROP") ||!strcmp(lexeme, "MINUSP") ||!strcmp(lexeme, "EQUAL") ||!strcmp(lexeme, "<=") ||!strcmp(lexeme, ">=")||!strcmp(lexeme, ">")||!strcmp(lexeme, "<") ||!strcmp(lexeme, "STRINGP") ||!strcmp(lexeme, "IF") ||!strcmp(lexeme, "COND")){
      return FUNCTION;
   }
   else if(!strcmp(lexeme,"\'")){
       printf("quote");
       return FUNCTION;
   }
   else return IDENT;
}

/**************************************************/
/* addChar - a function to add nextChar to lexeme */
/**************************************************/
void addChar() {
    if (lexLen <= 98) {  // max length of Lexime is 99
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0; // '\0'
    } else {
        printf("Error - lexeme is too long \n");
    }
}

/*****************************************************/
/* getChar - a function to get the next character
          of input and determine its character class */
/*****************************************************/
void getChar() {
    if ((nextChar = getc(stdin)) != EOF) {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else if(nextChar == '>' || nextChar == '<' || nextChar == '=')
            charClass = OPERATOR;
        else
         charClass = UNKNOWN;
    } else {
        charClass = EOF;
    }
}

/*****************************************************/
/* getNonBlank - a function to call getChar until it
           returns a non-whitespace character        */
/*****************************************************/
void getNonBlank() {
    while (isspace(nextChar))
      getChar();
}

void writeFile(int token, char *lexeme, FILE *fp) {
   
   char buffer1[100] = "Next token is : ";
   char buffer2[100] = ", Next lexeme is ";
   char c_token[10];
   
   sprintf(c_token, "%d", token);
   
   strcat(buffer1, c_token);
   strcat(buffer2, lexeme);
   strcat(buffer1, buffer2);
   buffer1[strlen(buffer1)] = '\n';
   
   fputs(buffer1, fp);
}


/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic
         expressions                                 */
/*****************************************************/
int lex() {
    lexLen = 0;
    getNonBlank();

    switch (charClass) {
        /* Parse identifiers */
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = is_Function();
            break;
            
        case OPERATOR:
            addChar();
            getChar();
            while(charClass == OPERATOR){
                addChar();
                getChar();
            }
            nextToken = is_Function();
            break;

        /* Parse integer literals */
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = INT_LIT;
            break;

        /* Parentheses and operators */
        case UNKNOWN:
            lookup(nextChar);
            getChar();
            break;

        /* EOF */
        case EOF:
            nextToken = EOF;
            lexeme[0] = 'E';
            lexeme[1] = 'O';
            lexeme[2] = 'F';
            lexeme[3] = 0;
            break;
    } /* End of switch */

    printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
    string str(lexeme);
    ret.push_back(make_pair(nextToken, lexeme));
    //writeFile(nextToken, lexeme, out_fp);
    return nextToken;
} /* End of function lex */

/******************************************/
/* main driver             */
/******************************************/

string input(){
    string s;
    cin >> s;
    return s;
}

int main()
{
    /* Open the input data file and process its contents */
    
    /*
    out_fp = fopen("code.out", "w");
    if ((in_fp = fopen("code.in", "r")) == NULL) {
        printf("ERROR - cannot open code.in \n");
    } else {
        getChar();
        do {
            lex();
        } while (nextToken != EOF);
    }
   */
    /*
    test_fp = fopen("test.in", "w");
    string input_string = input();
    char input_char[1024];
    strcpy(input_char, input_string.c_str());
    //fputs(input_char, test_fp);
    cout << input_char;
    */
    /*
    string filePath = "test.in";
    
    ofstream writeFile(filePath.data());
    if(writeFile.is_open()){
        writeFile << input();
    }
    */
    
    vector<pair<int,string>> vec = get_Token();
           
    return 0;
}
